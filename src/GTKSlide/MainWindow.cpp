/* Copyright 2018 John Jekel
 * This file is part of 15Slide.
 *
 * 15Slide is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * 15Slide is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with 15Slide.  If not, see <https://www.gnu.org/licenses/>
*/


#include "GTKSlide/MainWindow.h"

#include "ProgramStuff.h"//needed for about dialog and filesystem checks
#include "Grid15/Grid.h"
#include "Grid15/GridHelp.h"
#include "GTKSlide/GTKSlide.h"
#include "GTKSlide/SlideFileDialog.h"
#include "GTKSlide/SaveManager.h"

#include <gtkmm.h>

#include <iostream>
#include <memory>
#include <exception>

#if defined(ENABLE_CHECKS_WITH_STD_FILESYSTEM)
    #include <filesystem>
#endif


namespace GTKSlide
{
    /** \brief Creates and populates the GTKSlide main window
     *
     * \param application The Gtk::Application being used to run the window
     * \param newGridPtr The Grid15::Grid to use
     * \throw Gtk::BuilderError If something goes wrong during parse
     * \throw Glib::Markup error If something goes wrong during parse
     * \throw Glib::FileError If a file error occurs
     * \throw std::runtime_error If a menuBar cannot be created from the glade XML
     */
    MainWindow::MainWindow(Glib::RefPtr<Gtk::Application> &application, std::shared_ptr<Grid15::Grid> &newGridPtr)
        : mainGrid{}, saveManager{new SaveManager {}}, tileGrid{*this, newGridPtr, saveManager}, gridPtr{newGridPtr}, applicationPtr{application}//construct many member objects
    {
        try
        {
            Gtk::Window::set_icon(Gdk::Pixbuf::create_from_file(GTKSlide::Resources::LOGO));
        }
        catch (...)
        {
            g_warning("Could not open 15Slide logo");//not catostrophic if logo cannot be found
        }

        set_title("15Slide");
        //set_border_width(10);//fixme makes menu bar look weird

        set_resizable(false);
        set_position(Gtk::WIN_POS_CENTER);

        signal_delete_event().connect(sigc::mem_fun(*this, &MainWindow::exit));//add exit signal handler

        add(mainGrid);//add grid which holds menu and tile grid


        createMenuBarAndAddToMainGrid();//self explanatory

        mainGrid.attach_next_to(tileGrid, Gtk::POS_BOTTOM, 1, 1);//add tile grid

        show_all_children();//display the window
    }

    //not used
    //MainWindow::~MainWindow() {}

    /** \brief Creates a menu bar for the window and adds it to GtkSlide::MainWindow::mainGrid (it is manage()ed)
     *
     * Partly based on some Gtkmm examples: https://developer.gnome.org/gtkmm-tutorial/stable/sec-menus-examples.html.en
     *
     * \throw Gtk::BuilderError If something goes wrong during parse
     * \throw Glib::MarkupError If something goes wrong during parse
     * \throw Glib::FileError If a file error occurs
     * \throw std::runtime_error If a something cannot be created from the glade XML
     */
    void MainWindow::createMenuBarAndAddToMainGrid()
    {
        //create and add an action group to window
        Glib::RefPtr<Gio::SimpleActionGroup> actionGroup {Gio::SimpleActionGroup::create()};
        insert_action_group("actionGroup", actionGroup);

        //start filling the group with signal handelers

        actionGroup->add_action("newGame", sigc::mem_fun(*this, &MainWindow::onMenuBarNewGame));
        applicationPtr->set_accel_for_action("actionGroup.newGame", "<Primary>n");

        actionGroup->add_action("save", [this]
        {
            //lambda calls save and does not care about return value
            save();
        });
        applicationPtr->set_accel_for_action("actionGroup.save", "<Primary>s");

        actionGroup->add_action("saveAs", [this]
        {
            //lambda calls save and does not care about return value
            saveAs();
        });
        applicationPtr->set_accel_for_action("actionGroup.saveAs", "<Primary><Shift>s");

        actionGroup->add_action("load", sigc::mem_fun(*this, &MainWindow::onMenuBarLoad));
        applicationPtr->set_accel_for_action("actionGroup.load", "<Primary>l");

        actionGroup->add_action("exit", [this]
        {
            //lambda calls exit function (same one as x button)
            exit(nullptr);
        });
        applicationPtr->set_accel_for_action("actionGroup.exit", "<Primary>q");

        //actionGroup->add_action("autoSave", sigc::mem_fun(*this, &MainWindow::on_menuBar_autoSave));
        //applicationPtr->set_accel_for_action("actionGroup.autoSave", "<control>a");

        actionGroup->add_action("demo", []
        {
            //lambda opens 15Slide website in browser
            gtk_show_uri_on_window(nullptr, "https://jzjisawesome.github.io/15Slide/How-to-play", GDK_CURRENT_TIME, nullptr);
        });
        applicationPtr->set_accel_for_action("actionGroup.demo", "F1");

        actionGroup->add_action("feedback", []
        {
            //lambda opens new 15Slide issue in browser
            gtk_show_uri_on_window(nullptr, "https://github.com/JZJisawesome/15Slide/issues/new", GDK_CURRENT_TIME, nullptr);
        });
        applicationPtr->set_accel_for_action("actionGroup.feedback", "F1");

        actionGroup->add_action("about", sigc::mem_fun(*this, &MainWindow::onMenuBarAbout));
        //applicationPtr->set_accel_for_action("actionGroup.about", "a");


        //build the menu from the glade file
        Glib::RefPtr<Gtk::Builder> menuBuilder {Gtk::Builder::create_from_file(GTKSlide::Resources::MENUBAR_XML)};
        Gtk::MenuBar * newMenuBar = nullptr;


        menuBuilder->get_widget("menuBar", newMenuBar);
        if (!newMenuBar)
            throw std::runtime_error {"Could not create a menu bar"};

        //add menubar to window
        Gtk::manage(newMenuBar);
        mainGrid.add(*newMenuBar);
    }

    ///Resets the grid and handles the old one if it is not saved
    void MainWindow::onMenuBarNewGame()
    {
        if (!saveManager->isSaved)
        {
            switch (createNotSavedDialogAndRun())
            {
                case Gtk::RESPONSE_OK:
                {
                    if (!save())
                        break;//do not genereate new grid if user cancles saving/saving fails
                }
                [[fallthrough]]
                case Gtk::RESPONSE_REJECT:
                {
                    //reset previous save file
                    saveManager->saveFile = {""};
                    saveManager->isSaved = {false};

                    (*gridPtr) = {Grid15::GridHelp::generateRandomGrid()};

                    tileGrid.updateTiles();
                    break;
                }
                case Gtk::RESPONSE_CANCEL:
                case Gtk::RESPONSE_DELETE_EVENT://x button
                default:
                    break;
            }
        }
        else
        {
            //reset previous save file
            saveManager->saveFile = {""};
            saveManager->isSaved = {false};

            (*gridPtr) = {Grid15::GridHelp::generateRandomGrid()};

            tileGrid.updateTiles();
        }
    }

    /** \brief Saves the grid
     *
     * \return True if the save works, or if it does not, the user choses a valid file and not cancel
     */
    bool MainWindow::save()
    {
        if (saveManager->saveFile != "")
        {
            try
            {
                Grid15::GridHelp::save(saveManager->saveFile, *gridPtr);//FIXME error handeling needed
                return true;
            }
            catch (std::ios_base::failure &e)
            {
                saveManager->saveFile = {""};
                saveManager->isSaved = {false};

                int temp {createErrorDialogAndRun("Some this went wrong while saving", "Click \"Ok\" to choose a new save location")};

                if (temp == Gtk::RESPONSE_OK)
                {
                    return saveAs();
                }
                else
                    return false;
            }
        }
        else
            return saveAs();
    }

    /** \brief Saves the grid to a new file and updates MainWindow::saveManager
     *
     * \return True if the user choses a valid file and did not choose cancel
     */
    bool MainWindow::saveAs()
    {
        SlideFileDialog saveDialog(*this, "Choose a file to save to", Gtk::FILE_CHOOSER_ACTION_SAVE);

        const int result {saveDialog.run()};

        if (result == Gtk::RESPONSE_OK)
        {
            auto saveTo
            {
                [&saveDialog, this](const std::string &fileName) -> bool
                {
                    try
                    {
                        Grid15::GridHelp::save(fileName, *gridPtr);

                        //we only get here if the file works
                        saveManager->saveFile = {fileName};
                        saveManager->isSaved = {true};

                        tileGrid.updateTiles();

                        return true;
                    }
                    catch (std::ios_base::failure &e)
                    {
                        saveDialog.hide();//hide the file dialog first

                        createErrorDialogAndRun("Some this went wrong while saving", "Try a diffrent file/location, or change permissions to allow writing");

                        return false;
                    }
                }
            };

            #if defined(ENABLE_CHECKS_WITH_STD_FILESYSTEM)
            if (std::filesystem::exists(saveDialog.getFilenameWithExtention()))
            {
                Gtk::MessageDialog warningDialog("The file " + saveDialog.getFilenameWithExtention() + "exists already");
                warningDialog.set_title("Wait!");

                warningDialog.set_secondary_text("Is it ok to overwrite it?");

                warningDialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);

                warningDialog.set_transient_for(*this);
                warningDialog.show_all();
                warningDialog.present();

                switch (warningDialog.run())
                {
                    case Gtk::RESPONSE_OK:
                        return saveTo(saveDialog.getFilenameWithExtention());
                    case Gtk::RESPONSE_CANCEL:
                    case Gtk::RESPONSE_DELETE_EVENT://x button
                    default:
                    {
                        return false;
                        break;
                    }
                }
            }
            else
                return saveTo(saveDialog.getFilenameWithExtention());
            #else
            return saveTo(saveDialog.getFilenameWithExtention());
            #endif
        }
        else
            return false;
    }

    /// \brief Loads the grid from a file and updates MainWindow::saveManager
    void MainWindow::onMenuBarLoad()
    {
        if (!saveManager->isSaved)
        {
            switch (createNotSavedDialogAndRun())
            {
                case Gtk::RESPONSE_OK:
                    save();
                    [[fallthrough]]
                case Gtk::RESPONSE_REJECT://if user choooses not to save but leaves load dialog, don't do anything-
                    break;
                case Gtk::RESPONSE_CANCEL:
                case Gtk::RESPONSE_DELETE_EVENT://x button
                default:
                {
                    return;//instead of continuing to the load dialog, return from the function
                    break;
                }
            }
        }

        //now that the old grid is saved or not, we load a new one
        SlideFileDialog loadDialog(*this, "Choose a file to load from", Gtk::FILE_CHOOSER_ACTION_OPEN);

        if (loadDialog.run() == Gtk::RESPONSE_OK)
        {
            try
            {
                Grid15::GridHelp::load(loadDialog.get_filename(), *gridPtr);

                //we only get here if the file works
                saveManager->saveFile = {loadDialog.get_filename()};
                saveManager->isSaved = {true};

                tileGrid.updateTiles();
            }
            catch (std::ios_base::failure &e)
            {
                loadDialog.hide();//hide the file dialog first

                createErrorDialogAndRun("Some this went wrong while loading", "Try a diffrent file/location, change permissions to allow reading, and make sure it is a valid 15Slide save file");
            }
            catch (std::invalid_argument &e)
            {
                loadDialog.hide();//hide the file dialog first

                createErrorDialogAndRun("Some this went wrong while importing the grid", "The file was read sucessfully, but the grid may be corrupted");
            }
        }
    }

    /*
    void MainWindow::onMenuBarAutoSave()
    {
    }
    */

    /** \brief Exits 15Slide after checking if the grid is saved and handeling it
     *
     * \param event Unused; allows connecting to Gtk::Window::signal_delete_event() which requires it
     * \return Unused; allows connecting to Gtk::Window::signal_delete_event() which requires it
     */
    bool MainWindow::exit(GdkEventAny* /*event*/)
    {
        if (!saveManager->isSaved)
        {
            switch (createNotSavedDialogAndRun())
            {
                case Gtk::RESPONSE_REJECT:
                {
                    hide();
                    break;
                }
                case Gtk::RESPONSE_OK://fixme if user presses cancel in next dialog program closes without saving
                {
                    if (save())
                        hide();//only close the program if the user pressed ok and the file was valid
                    break;
                }
                case Gtk::RESPONSE_CANCEL:
                case Gtk::RESPONSE_DELETE_EVENT://x button
                default:
                    break;
            }
        }
        else
            hide();

        return true;//not important really
    }

    void MainWindow::onMenuBarAbout()
    {
        //read about dialog from glade file
        Glib::RefPtr<Gtk::Builder> menuBuilder {Gtk::Builder::create_from_file(GTKSlide::Resources::ABOUTSLIDE_XML)};
        Gtk::AboutDialog *newAboutSlide {};
        menuBuilder->get_widget("aboutSlide", newAboutSlide);

        if (!newAboutSlide)
            throw std::runtime_error {"Could not create an about dialog"};

        //version and logo are set here instead of in glade file
        try
        {
            newAboutSlide->set_logo(Gdk::Pixbuf::create_from_file(GTKSlide::Resources::LOGO, 25, 25));
        }
        catch (...)
        {
            g_warning("Could not open the 15Slide logo");//not catostrophic if logo cannot be found
        }

        newAboutSlide->set_version(ProgramStuff::Build::SLIDE_VERSION_STRING);

        newAboutSlide->set_transient_for(*this);
        newAboutSlide->run();
        newAboutSlide->hide();//this is odly needed to close dialog if user presses close with glade (not like this with GTKSlide::AboutSlide)

        delete newAboutSlide;//it is a window so manage() does not work
    }

    /** \brief A helper function which creates and runs a Gtk::MessageDialog asking the user what to do with the current unsaved grid
     *
     * \return The responce from the user (result of Gtk::MessageDialog::run)
     */
    int MainWindow::createNotSavedDialogAndRun()
    {
        Gtk::MessageDialog notSavedDialog("Wait!");
        notSavedDialog.set_title("Wait!");

        notSavedDialog.set_secondary_text("What do you want to do with this unsaved grid?");

        //super jankey looking and discouraged way to remove ok button
        notSavedDialog.get_action_area()->remove
        (
            *(notSavedDialog.get_action_area()->get_children()[0])//1st and only element is ok (gone now)
        );

        notSavedDialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        notSavedDialog.add_button("_Discard grid", Gtk::RESPONSE_REJECT);
        notSavedDialog.add_button("_Save grid", Gtk::RESPONSE_OK);

        notSavedDialog.set_default_response(Gtk::RESPONSE_CANCEL);

        notSavedDialog.set_transient_for(*this);
        notSavedDialog.show_all();
        notSavedDialog.present();

        return notSavedDialog.run();
    }

    /** \brief A helper function which creates and runs a Gtk::MessageDialog informing the user of an error that has occured
     *
     * \param errorMessage The error message to display
     * \param details Extra details to put (Gtk::MessageDialog::set_secondary_text)
     * \return The responce from the user (result of Gtk::MessageDialog::run)
     * \bug Parameters are not string refrences or string views (const std::string & OR std::string_view)
     */
    int MainWindow::createErrorDialogAndRun(std::string errorMessage, std::string details)
    {
        Gtk::MessageDialog errorDialog(errorMessage);
        errorDialog.set_title("Oh no!");

        errorDialog.set_secondary_text(details);

        errorDialog.set_transient_for(*this);
        errorDialog.show_all();
        errorDialog.present();

        return errorDialog.run();
    }
}
