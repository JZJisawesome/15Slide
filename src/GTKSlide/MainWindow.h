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
    MainWindow(Glib::RefPtr<Gtk::Application> & application, std::shared_ptr<Grid15::Grid> &newGridPtr);
    virtual ~MainWindow();

protected:
    Gtk::Grid mainGrid;

    Gtk::MenuBar mainMenu;
    Gtk::MenuBar createMenuBar();

    void on_menuBar_newGame();
    void on_menuBar_save();
    void on_menuBar_saveAs();
    void on_menuBar_load();
    void on_menuBar_exit();

    void on_menuBar_autoSave();

    void on_menuBar_demo();
    void on_menuBar_about();

    TileGrid tileGrid;


    std::shared_ptr<Grid15::Grid> gridPtr {};
    std::string saveFile {""};

    Glib::RefPtr<Gtk::Application> &applicationPtr;
};
}

#endif //MAINWINDOW_H
