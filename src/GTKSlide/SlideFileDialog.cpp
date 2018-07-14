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