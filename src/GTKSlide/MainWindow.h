//Copyright 2018 John Jekel
//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Grid15/Grid.h"

#include "GTKSlide/TileGrid.h"

#include <gtkmm.h>

namespace GTKSlide
{
/** \class MainWindow
 *
 * \brief The main window of GTKSlide
 *
 * \author John Jekel
 * \date 2018-2018
 */
class MainWindow : public Gtk::Window
{
public:
    MainWindow(const Glib::RefPtr<Gtk::Application>& application, std::shared_ptr<Grid15::Grid> &newGridPtr);
    virtual ~MainWindow();

protected:
    //Signal handlers:
    void on_menubar_test();
    Gtk::MenuBar createMenuBar(const Glib::RefPtr<Gtk::Application> &application);

    //Member widgets:
    //Gtk::Box mainBox {Gtk::ORIENTATION_HORIZONTAL};
    Gtk::Grid mainGrid;

    Gtk::MenuBar mainMenu;
    TileGrid tileGrid;

    //Grid
    std::shared_ptr<Grid15::Grid> gridPtr;
};
}

#endif //MAINWINDOW_H
