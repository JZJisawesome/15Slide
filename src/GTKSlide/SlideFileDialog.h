//Copyright 2018 John Jekel
//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms
#ifndef SLIDEFILEDIALOG_H
#define SLIDEFILEDIALOG_H

#include <gtkmm.h>

#include <string>

namespace GTKSlide
{
class SlideFileDialog : public Gtk::FileChooserDialog
{
public:
    SlideFileDialog(Gtk::Window &window, const std::string &title);
    virtual ~SlideFileDialog();

    void display();
};
}

#endif // SLIDEFILEDIALOG_H
