//Copyright 2018 John Jekel
//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms
#include "GTKSlide/MainWindow.h"

#include "Grid15/Grid.h"
#include "Grid15/GridHelp.h"
#include "CommandUI.h"

#include "ProgramStuff.h"

#include <gtkmm.h>
#include <iostream>

#include <memory>

namespace GTKSlide
{
MainWindow::MainWindow(Glib::RefPtr<Gtk::Application> &application, std::shared_ptr<Grid15::Grid> &newGridPtr): tileGrid(newGridPtr), gridPtr(newGridPtr), applicationPtr(application)
{
    set_title("15Slide");// + std::to_string(ProgramStuff::Build::SLIDE_VERSION));//fixme: too many decimal points
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

    if constexpr (ProgramStuff::Build::DEBUG)
    {
        actionGroup->add_action("test", sigc::mem_fun(*this, &MainWindow::menuBar_test));
        applicationPtr->set_accel_for_action("actionGroup.test", "<Primary>t");
    }

    actionGroup->add_action("save", sigc::mem_fun(*this, &MainWindow::menuBar_save));
    applicationPtr->set_accel_for_action("actionGroup.save", "<Primary>s");

    actionGroup->add_action("saveAs", sigc::mem_fun(*this, &MainWindow::menuBar_saveAs));

    actionGroup->add_action("load", sigc::mem_fun(*this, &MainWindow::menuBar_load));
    applicationPtr->set_accel_for_action("actionGroup.load", "<Primary>l");

    actionGroup->add_action("exit", sigc::mem_fun(*this, &MainWindow::menuBar_exit));


    actionGroup->add_action("autoSave", sigc::mem_fun(*this, &MainWindow::menuBar_autoSave));
    applicationPtr->set_accel_for_action("actionGroup.autoSave", "<Primary>a");


    actionGroup->add_action("demo", sigc::mem_fun(*this, &MainWindow::menuBar_demo));
    applicationPtr->set_accel_for_action("actionGroup.demo", "<Primary>d");

    actionGroup->add_action("about", sigc::mem_fun(*this, &MainWindow::menuBar_about));


    const char* menuXML
    {
        "<interface>"
        "   <menu id='menuBar'>"
        "       <submenu>"
        "           <attribute name='label' translatable='yes'>_File</attribute>"//File menu
        "           <section>"
        "               <section>"
        "                   <item>"//Test
        "                       <attribute name='label' translatable='yes'>_Test</attribute>"
        "                       <attribute name='action'>actionGroup.test</attribute>"
        "                       <attribute name='accel'>&lt;Primary&gt;t</attribute>"
        "                   </item>"
        "               </section>"
        "               <section>"
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
        "                       <attribute name='accel'>&lt;Primary&gt;d</attribute>"
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
    try
    {
        menuBuilder->add_from_string(menuXML);
        //menuBuilder->add_from_resource("data/toolbars/mainMenu.glade");
    }
    catch (Glib::Error &e)
    {
        std::cout << "Gtk::Builder ERROR: " << e.what() << std::endl;
    }

    //return it
    Glib::RefPtr<Glib::Object> menuObject = menuBuilder->get_object("menuBar");
    Glib::RefPtr<Gio::Menu> newMenuBar = Glib::RefPtr<Gio::Menu>::cast_dynamic(menuObject);
    if (!newMenuBar)
    {
        g_warning("GMenu not found");

        return Gtk::MenuBar {};
    }
    else
        return Gtk::MenuBar {newMenuBar};
}

void MainWindow::menuBar_test()
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::cout << "(debug)Hey! It works!!!" << std::endl;
}

void MainWindow::menuBar_save()
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::cout << "(debug)to do" << std::endl;
}

void MainWindow::menuBar_saveAs()
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::cout << "(debug)to do" << std::endl;
}

void MainWindow::menuBar_load()
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::cout << "(debug)to do" << std::endl;
}

void MainWindow::menuBar_exit()
{
    applicationPtr->quit();
}

void MainWindow::menuBar_autoSave()
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::cout << "(debug)to do" << std::endl;
}

void MainWindow::menuBar_demo()
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::cout << "(debug)to do" << std::endl;
}

void MainWindow::menuBar_about()
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::cout << "(debug)to do" << std::endl;
}
}
