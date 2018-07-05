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
    MainWindow(Glib::RefPtr<Gtk::Application> & pplication, std::shared_ptr<Grid15::Grid> &newGridPtr);
    virtual ~MainWindow();

protected:
    Gtk::Grid mainGrid;

    Gtk::MenuBar mainMenu;
    Gtk::MenuBar createMenuBar();

    void menuBar_test();
    void menuBar_save();
    void menuBar_saveAs();
    void menuBar_load();
    void menuBar_exit();

    void menuBar_autoSave();

    void menuBar_demo();
    void menuBar_about();

    TileGrid tileGrid;


    std::shared_ptr<Grid15::Grid> gridPtr;
    Glib::RefPtr<Gtk::Application> &applicationPtr;
};
}

#endif //MAINWINDOW_H
