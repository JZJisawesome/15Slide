//Copyright 2018 John Jekel
//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms
#include "GTKSlide/MainWindow.h"

#include "Grid15/Grid.h"
#include "Grid15/GridHelp.h"
#include "GTKSlide/AboutSlide.h"
#include "GTKSlide/SlideFileDialog.h"
#include "CommandUI.h"

#include "ProgramStuff.h"

#include <gtkmm.h>
#include <iostream>

#include <memory>

namespace GTKSlide
{
MainWindow::MainWindow(Glib::RefPtr<Gtk::Application> &application, std::shared_ptr<Grid15::Grid> &newGridPtr): tileGrid(*this, newGridPtr), gridPtr(newGridPtr), applicationPtr(application)
{
    set_title("15Slide");
    //set_border_width(10);//fixme makes menu bar look weird
    set_resizable(false);

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
    applicationPtr->set_accel_for_action("actionGroup.newGame", "<Primary>n");

    actionGroup->add_action("save", sigc::mem_fun(*this, &MainWindow::on_menuBar_save));
    applicationPtr->set_accel_for_action("actionGroup.save", "<Primary>s");

    actionGroup->add_action("saveAs", sigc::mem_fun(*this, &MainWindow::on_menuBar_saveAs));

    actionGroup->add_action("load", sigc::mem_fun(*this, &MainWindow::on_menuBar_load));
    applicationPtr->set_accel_for_action("actionGroup.load", "<Primary>l");

    actionGroup->add_action("exit", sigc::mem_fun(*this, &MainWindow::on_menuBar_exit));
    applicationPtr->set_accel_for_action("actionGroup.exit", "<Primary>q");


    actionGroup->add_action("autoSave", sigc::mem_fun(*this, &MainWindow::on_menuBar_autoSave));
    applicationPtr->set_accel_for_action("actionGroup.autoSave", "<Primary>a");


    actionGroup->add_action("demo", sigc::mem_fun(*this, &MainWindow::on_menuBar_demo));
    applicationPtr->set_accel_for_action("actionGroup.demo", "<Primary>h");

    actionGroup->add_action("about", sigc::mem_fun(*this, &MainWindow::on_menuBar_about));


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
        "                       <attribute name='accel'>&lt;Primary&gt;n</attribute>"
        "                   </item>"
        "                   <item>"//Save
        "                       <attribute name='label' translatable='yes'>_Save</attribute>"
        "                       <attribute name='action'>actionGroup.save</attribute>"
        "                       <attribute name='accel'>&lt;Primary&gt;s</attribute>"
        "                   </item>"
        "                   <item>"//Save As
        "                       <attribute name='label' translatable='yes'>_Save As</attribute>"
        "                       <attribute name='action'>actionGroup.saveAs</attribute>"
        "                   </item>"
        "                   <item>"//Load
        "                       <attribute name='label' translatable='yes'>_Load</attribute>"
        "                       <attribute name='action'>actionGroup.load</attribute>"
        "                       <attribute name='accel'>&lt;Primary&gt;l</attribute>"
        "                   </item>"
        "               </section>"
        "               <section>"
        "                   <item>"//Exit
        "                       <attribute name='label' translatable='yes'>_Exit</attribute>"
        "                       <attribute name='action'>actionGroup.exit</attribute>"
        "                       <attribute name='accel'>&lt;Primary&gt;q</attribute>"
        "                   </item>"
        "               </section>"
        "           </section>"
        "       </submenu>"
        "       <submenu>"
        "           <attribute name='label' translatable='yes'>_Options</attribute>"//Options menu
        "           <section>"
        "                   <item>"//Auto Save
        "                       <attribute name='label' translatable='yes'>_Auto Save</attribute>"
        "                       <attribute name='action'>actionGroup.autoSave</attribute>"
        "                       <attribute name='accel'>&lt;Primary&gt;a</attribute>"
        "                   </item>"
        "           </section>"
        "       </submenu>"
        "       <submenu>"
        "           <attribute name='label' translatable='yes'>_Help</attribute>"//Help menu
        "           <section>"
        "                   <item>"//How to play
        "                       <attribute name='label' translatable='yes'>_How to play</attribute>"
        "                       <attribute name='action'>actionGroup.demo</attribute>"
        "                       <attribute name='accel'>&lt;Primary&gt;h</attribute>"
        "                   </item>"
        "                   <item>"//About
        "                       <attribute name='label' translatable='yes'>_About 15Slide</attribute>"
        "                       <attribute name='action'>actionGroup.about</attribute>"
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
    {
        g_warning("newMenuBar not found");

        return Gtk::MenuBar {};
    }
    else
    {
        return Gtk::MenuBar {newMenuBar};
    }
}

void MainWindow::on_menuBar_newGame()
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::clog << "(debug)not done" << std::endl;

    //check if grid was not saved

    saveFile = {""};
    tileGrid.saveFile = {""};

    (*gridPtr) = {Grid15::GridHelp::generateRandomGrid()};

    tileGrid.lableTiles();
}

void MainWindow::on_menuBar_save()
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::clog << "(debug)not done" << std::endl;

    if (saveFile != "")
        Grid15::GridHelp::save(saveFile, *gridPtr);//error handlign needed
    else
        on_menuBar_saveAs();
}

void MainWindow::on_menuBar_saveAs()
{
    SlideFileDialog saveDialog(*this, "Choose a file to save to", Gtk::FILE_CHOOSER_ACTION_SAVE);

    if (saveDialog.run() == Gtk::RESPONSE_OK)
    {
        try
        {
            Grid15::GridHelp::save(saveDialog.get_filename(), *gridPtr);

            //we only get here if the file works
            saveFile = {saveDialog.get_filename()};

            tileGrid.saveFile = {saveFile};
        }
        catch (std::ios_base::failure &e)
        {
            Gtk::MessageDialog wonDialog("Some this went wrong while saving");//second string is a trophy
            wonDialog.set_title("Oh no!");

            wonDialog.set_secondary_text("Try a diffrent file/location, or change permissions to allow writing");

            wonDialog.set_transient_for(*this);
            wonDialog.show_all();
            wonDialog.present();
            wonDialog.run();
        }
    }
}

void MainWindow::on_menuBar_load()
{
    SlideFileDialog loadDialog(*this, "Choose a file to load", Gtk::FILE_CHOOSER_ACTION_OPEN);

    if (loadDialog.run() == Gtk::RESPONSE_OK)
    {
        try
        {
            Grid15::GridHelp::load(loadDialog.get_filename(), *gridPtr);

            //we only get here if the file works
            saveFile = {loadDialog.get_filename()};

            tileGrid.saveFile = {saveFile};
            tileGrid.lableTiles();
        }
        catch (std::ios_base::failure &e)
        {
            Gtk::MessageDialog wonDialog("Some this went wrong while loading");//second string is a trophy
            wonDialog.set_title("Oh no!");

            wonDialog.set_secondary_text("Try a diffrent file/location, change permissions to allow reading, and make sure it is a valid 15Slide save file");

            wonDialog.set_transient_for(*this);
            wonDialog.show_all();
            wonDialog.present();
            wonDialog.run();
        }
        catch (std::invalid_argument &e)
        {
            Gtk::MessageDialog wonDialog("Some this went wrong while importing the grid");//second string is a trophy
            wonDialog.set_title("Oh no!");

            wonDialog.set_secondary_text("The file was read sucessfully, but the grid may be corrupted");

            wonDialog.set_transient_for(*this);
            wonDialog.show_all();
            wonDialog.present();
            wonDialog.run();
        }
    }
}

void MainWindow::on_menuBar_exit()
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::clog << "(debug)not done" << std::endl;
    //check if grid was not saved
    hide();
}

void MainWindow::on_menuBar_autoSave()
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::clog << "(debug)to do" << std::endl;
}

void MainWindow::on_menuBar_demo()
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::clog << "(debug)to do" << std::endl;
}

void MainWindow::on_menuBar_about()
{
    (AboutSlide {*this}).display();
}
}
