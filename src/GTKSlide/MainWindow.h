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
            //virtual ~MainWindow();

        protected:
            Gtk::Grid mainGrid;///<The Gtk::Grid used for holding MainWindow::tileGrid and MainWindow::mainMenu

            void createMenuBarAndAddToMainGrid();

            void on_menuBar_newGame();
            void on_menuBar_load();

            void on_menubar_about();

            //void on_menuBar_autoSave();//move to settings dialog

            //replaced with lambdas
            //void on_menubar_save();
            //void on_menubar_saveAs();
            //void on_menuBar_exit();
            //void on_menubar_demo();

            bool save();
            bool saveAs();
            bool exit(GdkEventAny* event);

            int createNotSavedDialogAndRun();
            int createErrorDialogAndRun(std::string errorMessage, std::string details = "");


            std::shared_ptr<SaveManager> saveManager {};///<A SaveManager to manage autosaving with Gtk::MenuBar

            TileGrid tileGrid;///<A graphical and interactive representation of a Grid15::Grid
            std::shared_ptr<Grid15::Grid> gridPtr {};///<A pointer to a Grid15::Grid for use with GTKSlide classes

            Glib::RefPtr<Gtk::Application> applicationPtr {};///<The Gtk::Application assisiated with this class, because Gtk::Window::get_application() is unreliable
    };
}

#endif //MAINWINDOW_H
