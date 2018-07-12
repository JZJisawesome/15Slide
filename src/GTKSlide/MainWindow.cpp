//Copyright 2018 John Jekel
//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms
#include "GTKSlide/MainWindow.h"

#include "Grid15/Grid.h"
#include "Grid15/GridHelp.h"
#include "GTKSlide/AboutSlide.h"
#include "GTKSlide/SlideFileDialog.h"
#include "GTKSlide/SaveManager.h"
#include "CommandUI.h"

#include "ProgramStuff.h"

#include <gtkmm.h>
#include <iostream>

#include <memory>
#include <exception>

namespace GTKSlide
{
MainWindow::MainWindow(Glib::RefPtr<Gtk::Application> &application, std::shared_ptr<Grid15::Grid> &newGridPtr)
: saveManager{new SaveManager {}}, tileGrid{*this, newGridPtr, saveManager}, gridPtr{newGridPtr}, applicationPtr{application}
{
    set_title("15Slide");
    //set_border_width(10);//fixme makes menu bar look weird
    set_resizable(false);
    set_position(Gtk::WIN_POS_CENTER);
    signal_delete_event().connect(sigc::mem_fun(*this, &MainWindow::onExit));

    add(mainGrid);


    mainMenu = createMenuBar();//create a menu bar
    mainGrid.add(mainMenu);//adds a menu bar to the box

    mainGrid.attach_next_to(tileGrid, mainMenu, Gtk::POS_BOTTOM, 1, 1);

    show_all_children();
}

MainWindow::~MainWindow()
{
}

Gtk::MenuBar MainWindow::createMenuBar()
{
    Glib::RefPtr<Gio::SimpleActionGroup> actionGroup {Gio::SimpleActionGroup::create()};
    insert_action_group("actionGroup", actionGroup);

    actionGroup->add_action("newGame", sigc::mem_fun(*this, &MainWindow::on_menuBar_newGame));
    applicationPtr->set_accel_for_action("actionGroup.newGame", "<control>n");

    actionGroup->add_action("save", sigc::mem_fun(*this, &MainWindow::on_menuBar_save));
    applicationPtr->set_accel_for_action("actionGroup.save", "<control>s");

    actionGroup->add_action("saveAs", sigc::mem_fun(*this, &MainWindow::on_menuBar_saveAs));
    applicationPtr->set_accel_for_action("actionGroup.saveAs", "<control><shift>s");

    actionGroup->add_action("load", sigc::mem_fun(*this, &MainWindow::on_menuBar_load));
    applicationPtr->set_accel_for_action("actionGroup.load", "<control>l");

    actionGroup->add_action("exit", [this](){ onExit(nullptr); });//lambda calls onExit function (same one as x button)
    applicationPtr->set_accel_for_action("actionGroup.exit", "<control>q");


    //actionGroup->add_action("autoSave", sigc::mem_fun(*this, &MainWindow::on_menuBar_autoSave));
    //applicationPtr->set_accel_for_action("actionGroup.autoSave", "<control>a");


    //lambda opens browser with link to How to play 15Slide
    actionGroup->add_action("demo", [](){ gtk_show_uri_on_window(nullptr, "https://jzjisawesome.github.io/15Slide/How-to-play", GDK_CURRENT_TIME, nullptr); });
    applicationPtr->set_accel_for_action("actionGroup.demo", "F1");

    actionGroup->add_action("about", [this](){ (AboutSlide {*this}).display(); });//lambda creates temporary about dialog and displays it
    applicationPtr->set_accel_for_action("actionGroup.about", "a");


    const char* menuXML
    {
        "<interface>"
        "   <menu id='menuBar'>"
        "       <submenu>"
        "           <attribute name='label' translatable='yes'>_File</attribute>"//File menu
        "           <section>"
        "               <section>"
        "                   <item>"//New Game
        "                       <attribute name='label' translatable='yes'>_New Game</attribute>"
        "                       <attribute name='action'>actionGroup.newGame</attribute>"
        "                       <attribute name='accel'>&lt;control&gt;n</attribute>"
        "                   </item>"
        "                   <item>"//Save
        "                       <attribute name='label' translatable='yes'>_Save</attribute>"
        "                       <attribute name='action'>actionGroup.save</attribute>"
        "                       <attribute name='accel'>&lt;control&gt;s</attribute>"
        "                   </item>"
        "                   <item>"//Save As
        "                       <attribute name='label' translatable='yes'>_Save As</attribute>"
        "                       <attribute name='action'>actionGroup.saveAs</attribute>"
        "                       <attribute name='accel'>&lt;control&gt;&lt;shift&gt;s</attribute>"
        "                   </item>"
        "                   <item>"//Load
        "                       <attribute name='label' translatable='yes'>_Load</attribute>"
        "                       <attribute name='action'>actionGroup.load</attribute>"
        "                       <attribute name='accel'>&lt;control&gt;l</attribute>"
        "                   </item>"
        "               </section>"
        "               <section>"
        "                   <item>"//Exit
        "                       <attribute name='label' translatable='yes'>_Exit</attribute>"
        "                       <attribute name='action'>actionGroup.exit</attribute>"
        "                       <attribute name='accel'>&lt;control&gt;q</attribute>"
        "                   </item>"
        "               </section>"
        "           </section>"
        "       </submenu>"
        //might make into settings dialog
        //"       <submenu>"
        //"           <attribute name='label' translatable='yes'>_Options</attribute>"//Options menu
        //"           <section>"
        //"                   <item>"//Auto Save
        //"                       <attribute name='label' translatable='yes'>_Auto Save</attribute>"
        //"                       <attribute name='action'>actionGroup.autoSave</attribute>"
        //"                       <attribute name='accel'>&lt;control&gt;a</attribute>"
        //"                   </item>"
        //"           </section>"
        //"       </submenu>"
        "       <submenu>"
        "           <attribute name='label' translatable='yes'>_Help</attribute>"//Help menu
        "           <section>"
        "                   <item>"//How to play
        "                       <attribute name='label' translatable='yes'>_How to play</attribute>"
        "                       <attribute name='action'>actionGroup.demo</attribute>"
        "                       <attribute name='accel'>F1</attribute>"
        "                   </item>"
        "                   <item>"//About
        "                       <attribute name='label' translatable='yes'>_About 15Slide</attribute>"
        "                       <attribute name='action'>actionGroup.about</attribute>"
        "                       <attribute name='accel'>a</attribute>"
        "                   </item>"
        "           </section>"
        "       </submenu>"
        "   </menu>"
        "</interface>"
    };

    Glib::RefPtr<Gtk::Builder> menuBuilder {Gtk::Builder::create()};

    //build the menu
    menuBuilder->add_from_string(menuXML);
    //menuBuilder->add_from_resource("data/toolbars/mainMenu.glade");

    //return it
    Glib::RefPtr<Glib::Object> menuObject = menuBuilder->get_object("menuBar");
    Glib::RefPtr<Gio::Menu> newMenuBar = Glib::RefPtr<Gio::Menu>::cast_dynamic(menuObject);
    if (!newMenuBar)
        throw std::runtime_error {"Could not create a menu bar"};
    else
        return Gtk::MenuBar {newMenuBar};
}

void MainWindow::on_menuBar_newGame()
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::clog << "(debug)not done" << std::endl;


    if (!saveManager->isSaved)
    {
        Gtk::MessageDialog notSavedDialog("Wait!");//fixme clicking x on dialog exits 155Slide
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

        switch (notSavedDialog.run())
        {
        case Gtk::RESPONSE_OK://fixme if user presses cancel in next dialog program closes without saving
            on_menuBar_save();//no break statement here on purpose
        case Gtk::RESPONSE_REJECT:
        {
            saveManager->saveFile = {""};
            saveManager->isSaved = {false};

            (*gridPtr) = {Grid15::GridHelp::generateRandomGrid()};

            tileGrid.lableTiles();
            break;
        }
        case Gtk::RESPONSE_CANCEL:
        case Gtk::RESPONSE_DELETE_EVENT:
        default:
            break;
        }
    }
    else
    {
        saveManager->saveFile = {""};
        saveManager->isSaved = {false};

        (*gridPtr) = {Grid15::GridHelp::generateRandomGrid()};

        tileGrid.lableTiles();
    }
}

void MainWindow::on_menuBar_save()
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::clog << "(debug)not done" << std::endl;

    if (saveManager->saveFile != "")
        Grid15::GridHelp::save(saveManager->saveFile, *gridPtr);//error handlign needed
    else
        on_menuBar_saveAs();
}

void MainWindow::on_menuBar_saveAs()
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::clog << "(debug)final touches" << std::endl;

    SlideFileDialog saveDialog(*this, "Choose a file to save to", Gtk::FILE_CHOOSER_ACTION_SAVE);

    if (saveDialog.run() == Gtk::RESPONSE_OK)
    {
        try
        {
            Grid15::GridHelp::save(saveDialog.get_filename(), *gridPtr);

            //we only get here if the file works
            saveManager->saveFile = {saveDialog.get_filename()};
            saveManager->isSaved = {true};

            tileGrid.lableTiles();
        }
        catch (std::ios_base::failure &e)
        {
            saveDialog.hide();

            Gtk::MessageDialog errorDialog("Some this went wrong while saving");
            errorDialog.set_title("Oh no!");

            errorDialog.set_secondary_text("Try a diffrent file/location, or change permissions to allow writing");

            errorDialog.set_transient_for(*this);
            errorDialog.show_all();
            errorDialog.present();
            errorDialog.run();
        }
    }
}

void MainWindow::on_menuBar_load()
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::clog << "(debug)final touches" << std::endl;

    if (!saveManager->isSaved)
    {
        Gtk::MessageDialog notSavedDialog("Wait!");//fixme clicking x on dialog exits 155Slide
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

        switch (notSavedDialog.run())
        {
        case Gtk::RESPONSE_OK://fixme if user presses cancel in next dialog program closes without saving
            on_menuBar_save();//no break statement here on purpose
        case Gtk::RESPONSE_REJECT:
        {
            saveManager->saveFile = {""};
            saveManager->isSaved = {false};

            (*gridPtr) = {Grid15::GridHelp::generateRandomGrid()};

            tileGrid.lableTiles();
            break;
        }
        case Gtk::RESPONSE_CANCEL:
        case Gtk::RESPONSE_DELETE_EVENT:
        default:
        {
            return;//instead of continuing to the load dialog, reutrn from the function
            break;
        }
        }
    }

    SlideFileDialog loadDialog(*this, "Choose a file to load from", Gtk::FILE_CHOOSER_ACTION_OPEN);

    if (loadDialog.run() == Gtk::RESPONSE_OK)
    {
        try
        {
            Grid15::GridHelp::load(loadDialog.get_filename(), *gridPtr);

            //we only get here if the file works
            saveManager->saveFile = {loadDialog.get_filename()};
            saveManager->isSaved = {true};

            tileGrid.lableTiles();
        }
        catch (std::ios_base::failure &e)
        {
            loadDialog.hide();

            Gtk::MessageDialog errorDialog("Some this went wrong while loading");
            errorDialog.set_title("Oh no!");

            errorDialog.set_secondary_text("Try a diffrent file/location, change permissions to allow reading, and make sure it is a valid 15Slide save file");

            errorDialog.set_transient_for(*this);
            errorDialog.show_all();
            errorDialog.present();
            errorDialog.run();
        }
        catch (std::invalid_argument &e)
        {
            loadDialog.hide();

            Gtk::MessageDialog errorDialog("Some this went wrong while importing the grid");
            errorDialog.set_title("Oh no!");

            errorDialog.set_secondary_text("The file was read sucessfully, but the grid may be corrupted");

            errorDialog.set_transient_for(*this);
            errorDialog.show_all();
            errorDialog.present();
            errorDialog.run();
        }
    }
}

void MainWindow::on_menuBar_autoSave()
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::clog << "(debug)to do" << std::endl;
}

bool MainWindow::onExit(GdkEventAny* event)
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::clog << "(debug)not done" << std::endl;

    if (!saveManager->isSaved)
    {
        Gtk::MessageDialog notSavedDialog("Wait!");//fixme clicking x on dialog exits 155Slide
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

        switch (notSavedDialog.run())
        {
        case Gtk::RESPONSE_REJECT:
        {
            hide();
            break;
        }
        case Gtk::RESPONSE_OK://fixme if user presses cancel in next dialog program closes without saving
        {
            on_menuBar_save();
            hide();
            break;
        }
        case Gtk::RESPONSE_CANCEL:
        case Gtk::RESPONSE_DELETE_EVENT:
        default:
            break;
        }
    }
    else
        hide();

    return true;
}
}
