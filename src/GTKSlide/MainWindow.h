#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Grid15/Grid.h"

#include "GTKSlide/GUIGrid.h"

#include <gtkmm.h>

namespace GTKSlide
{
/** \class MainWindow
 *
 * \brief The main window of GTKSlide
 *
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

    //Member widgets:
    Gtk::Box mainBox;

    Glib::RefPtr<Gtk::Builder> menuBuilder;
    Glib::RefPtr<Gio::SimpleActionGroup> actionGroup {};

    GUIGrid guiGrid {};

    //Grid
    std::shared_ptr<Grid15::Grid> gridPtr {};
};
}

#endif //MAINWINDOW_H
