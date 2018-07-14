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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Grid15/Grid.h"

#include "GTKSlide/TileGrid.h"
#include "GTKSlide/SaveManager.h"

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
    MainWindow(Glib::RefPtr<Gtk::Application> &application, std::shared_ptr<Grid15::Grid> &newGridPtr);
    virtual ~MainWindow();

protected:
    Gtk::Grid mainGrid;

    Gtk::MenuBar mainMenu;
    Gtk::MenuBar createMenuBar();

    void on_menuBar_newGame();
    void on_menuBar_save();
    void on_menuBar_saveAs();
    void on_menuBar_load();

    //void on_menuBar_autoSave();

    //replaced with lambdas
    //void on_menuBar_exit();
    //void on_menubar_demo();
    //void on_menubar_about();

    bool onExit(GdkEventAny* event);


    std::shared_ptr<SaveManager> saveManager {};

    TileGrid tileGrid;
    std::shared_ptr<Grid15::Grid> gridPtr {};

    Glib::RefPtr<Gtk::Application> &applicationPtr;
};
}

#endif //MAINWINDOW_H
