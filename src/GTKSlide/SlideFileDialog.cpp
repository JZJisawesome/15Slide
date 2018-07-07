//Copyright 2018 John Jekel
//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms

#include "SlideFileDialog.h"
#include <gtkmm.h>

namespace GTKSlide
{
SlideFileDialog::SlideFileDialog(Gtk::Window &window, const std::string &title) : Gtk::FileChooserDialog(title, Gtk::FILE_CHOOSER_ACTION_OPEN)
{
    set_transient_for(window);

    add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    add_button("_Open", Gtk::RESPONSE_OK);

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
