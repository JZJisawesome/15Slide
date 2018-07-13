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
#ifndef SLIDEFILEDIALOG_H
#define SLIDEFILEDIALOG_H

#include <gtkmm.h>

#include <string>

namespace GTKSlide
{
class SlideFileDialog : public Gtk::FileChooserDialog
{
public:
    SlideFileDialog(Gtk::Window &parent, const std::string &title, Gtk::FileChooserAction action);
    virtual ~SlideFileDialog();

    void display();
};
}

#endif // SLIDEFILEDIALOG_H
