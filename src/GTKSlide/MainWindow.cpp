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
MainWindow::MainWindow(const Glib::RefPtr<Gtk::Application> &application, std::shared_ptr<Grid15::Grid> &newGridPtr): gridPtr(newGridPtr)
{
    guiGrid.setupGrid(gridPtr);

    set_title(std::string ("15Slide Version ") + std::to_string(ProgramStuff::Build::SLIDE_VERSION));
    // Sets the border width of the window.
    set_border_width(10);

    add(mainBox);

    //guiGrid.show_all();//show the game grid

    mainBox.pack_start(guiGrid);

    /*
    actionGroup = Gio::SimpleActionGroup::create();

    actionGroup->add_action("test", sigc::mem_fun(*this, &MainWindow::on_menubar_test));

    insert_action_group("testmenubar", actionGroup);

    const char* ui_info =
    "<interface>"
    "  <menu id='testmenubar'>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_File</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Test</attribute>"
    "          <attribute name='action'>testmenubar.test</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;t</attribute>"
    "        </item>"
    "      <section>"
    "    </submenu>"
    "  </menu>"
    "</interface>";

    application->set_accel_for_action("testmenubar.test", "<Primary>t");

    try
    {
        menuBuilder->add_from_string(ui_info);
    }
    catch(const Glib::Error& ex)
    {
        std::cerr << "Building menus and toolbar failed: " <<  ex.what();
    }

    //Get the menubar:
    auto object = menuBuilder->get_object("testmenubar");
    auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
    if (!gmenu)
        g_warning("GMenu not found");
    else
    {
        auto ptrMenuBar = Gtk::manage(new Gtk::MenuBar(gmenu));

        //Add the MenuBar to the window:
        mainBox.pack_start(*ptrMenuBar, Gtk::PACK_SHRINK);
    }

    Gtk::Toolbar *toolbar = nullptr;
    menuBuilder->get_widget("toolbar", toolbar);
    if (!toolbar)
        g_warning("GtkToolbar not found");
    else
        mainBox.pack_start(*toolbar, Gtk::PACK_SHRINK);

        */

    show_all_children();
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_menubar_test()
{
}

}
