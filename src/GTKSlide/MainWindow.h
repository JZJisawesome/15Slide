/* MIT License
 *
 * Copyright (c) 2018 John Jekel
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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

            void onMenuBarNewGame();
            void onMenuBarLoad();

            void onMenuBarAbout();

            //replaced with lambdas/shared with other functions
            //void onMenuBarSave();
            //void onMenuBarSaveAs();
            //void onMenuBarExit();
            //void onMenuBarDemo();
            //void onMenuBarAutoSave();//should probably move to settings dialog

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
