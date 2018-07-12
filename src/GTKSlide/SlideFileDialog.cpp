//Copyright 2018 John Jekel
//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms

#include "GTKSlide/SlideFileDialog.h"
#include <gtkmm.h>

namespace GTKSlide
{
SlideFileDialog::SlideFileDialog(Gtk::Window &parent, const std::string &title, Gtk::FileChooserAction action) : Gtk::FileChooserDialog{title, action}
{
    set_transient_for(parent);

    add_button("_Cancel", Gtk::RESPONSE_CANCEL);

    if (action == Gtk::FILE_CHOOSER_ACTION_OPEN)
        add_button("_Open", Gtk::RESPONSE_OK);
    else if (action == Gtk::FILE_CHOOSER_ACTION_SAVE)
        add_button("_Save", Gtk::RESPONSE_OK);
    else
        throw std::invalid_argument {"Invalid File Chooser Action"};

    Glib::RefPtr<Gtk::FileFilter> filter_slideSave = Gtk::FileFilter::create();
    filter_slideSave->set_name("15Slide save files");
    filter_slideSave->add_mime_type("text/plain");//fixme make file extention
    add_filter(filter_slideSave);

    Glib::RefPtr<Gtk::FileFilter> filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    add_filter(filter_any);
}

SlideFileDialog::~SlideFileDialog() {}
}
