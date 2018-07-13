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
#ifndef ABOUTSLIDE_H
#define ABOUTSLIDE_H

#include <gtkmm.h>

namespace GTKSlide
{
class AboutSlide : public Gtk::AboutDialog
{
public:
    AboutSlide(Gtk::Window &parent);
    virtual ~AboutSlide();

    void display();
};
}
#endif //ABOUTSLIDE_H
