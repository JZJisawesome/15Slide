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


#include "GTKSlide/AboutSlide.h"

#include "ProgramStuff.h"//still used for version
#include "GTKSlide/GTKSlide.h"

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
            set_logo(Gdk::Pixbuf::create_from_file(GTKSlide::Resources::LOGO, 25, 25));
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
