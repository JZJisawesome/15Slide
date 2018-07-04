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
MainWindow::MainWindow(const Glib::RefPtr<Gtk::Application> &application, std::shared_ptr<Grid15::Grid> &newGridPtr): tileGrid(newGridPtr), gridPtr(newGridPtr)
{
    set_title(std::string ("15Slide Version ") + std::to_string(ProgramStuff::Build::SLIDE_VERSION));//fixme: too many decimal points
    //set_border_width(10);//fixme makes menu bar look weird

    add(mainGrid);

    mainMenu = createMenuBar(application);//create a menu bar
    mainGrid.add(mainMenu);//adds a menu bar to the box

    mainGrid.attach_next_to(tileGrid, mainMenu, Gtk::POS_BOTTOM, 1, 1);

    show_all_children();
}

MainWindow::~MainWindow()
{
}

Gtk::MenuBar MainWindow::createMenuBar(const Glib::RefPtr<Gtk::Application> &application)
{
    Glib::RefPtr<Gio::SimpleActionGroup> actionGroup {Gio::SimpleActionGroup::create()};
    actionGroup->add_action("test", sigc::mem_fun(*this, &MainWindow::on_menubar_test));
    insert_action_group("testactiongroup", actionGroup);

    Glib::RefPtr<Gtk::Builder> menuBuilder {Gtk::Builder::create()};

    const char* ui_info =
    "<interface>"
    "  <menu id='menubar'>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_File</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Test</attribute>"
    "          <attribute name='action'>testactiongroup.test</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;t</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "  </menu>"
    "</interface>";

    application->set_accel_for_action("testactiongroup.test", "<Primary>t");//setup keyboard shortcut

    try
    {
        menuBuilder->add_from_string(ui_info);
    }
    catch(const Glib::Error& ex)
    {
        std::cerr << "Building menus and toolbar failed: " <<  ex.what();
    }

    //Get the menubar:
    auto object = menuBuilder->get_object("menubar");
    auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
    if (!gmenu)
    {
        g_warning("GMenu not found");

        return Gtk::MenuBar {};
    }
    else
    {
        //Gtk::MenuBar *ptrMenuBar = Gtk::manage(new Gtk::MenuBar(gmenu));

        return Gtk::MenuBar {gmenu};

        //Add the MenuBar to the window:
        //mainBox.pack_start(*ptrMenuBar, Gtk::PACK_SHRINK);
    }
}

void MainWindow::on_menubar_test()
{
    std::cout << "it works" << std::endl;
}
}
