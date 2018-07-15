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
#include "GTKSlide/AboutSlide.h"

#include "ProgramStuff.h"

#include <iostream>

namespace GTKSlide
{
/** \brief Creates and populates an about dialog for 15Slide
 *
 * \param parent To automatically call Gtk::AboutDialog::set_transient_for()
 */
AboutSlide::AboutSlide(Gtk::Window &parent)
{
    set_transient_for(parent);
    //set_modal(false);

    try
    {
        set_logo(Gdk::Pixbuf::create_from_file(ProgramStuff::GTKSlide::Resources::LOGO, 25, 25));
    }
    catch (...)
    {
        g_warning("Could not open 15Slide logo");//not catostrophic if logo cannot be found
    }

    set_program_name("15Slide");
    set_version(ProgramStuff::Build::SLIDE_VERSION_STRING);
    set_comments("A fun, cross-platform, slidy-tile game written with C++ 17!");

    set_copyright("John Jekel @JZJisawesome");
    set_license
    (
        "15Slide is free software: you can redistribute it and/or modify "
        "it under the terms of the GNU Lesser General Public License as published by "
        "the Free Software Foundation, either version 3 of the License, or "
        "(at your option) any later version.\n"
        "\n"
        "15Slide is distributed in the hope that it will be useful, "
        "but WITHOUT ANY WARRANTY; without even the implied warranty of "
        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
        "GNU Lesser General Public License for more details.\n"
        "\n"
        "You should have received a copy of the GNU Lesser General Public License "
        "along with 15Slide.  If not, see <https://www.gnu.org/licenses/>."
    );
    set_wrap_license(true);
    set_authors
    (
    {
        "John Jekel @JZJisawesome"
    }
    );

    set_website("https://jzjisawesome.github.io/15Slide/");
    set_website_label("15Slide Website");
}

//not used
//AboutSlide::~AboutSlide() {}

///Calls show_all(), present() and run() in one handy function
void AboutSlide::display()
{
    show_all();
    present();
    run();
}
}
