//Copyright 2018 John Jekel
//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms
#include "GTKSlide/AboutSlide.h"

#include "ProgramStuff.h"

namespace GTKSlide
{
AboutSlide::AboutSlide(Gtk::Window &parent)
{
    set_transient_for(parent);

    //set_logo(Gdk::Pixbuf::create_from_resource("test.png", -1, 40, true));
    set_program_name("15Slide");
    set_version(ProgramStuff::Build::SLIDE_VERSION_STRING);
    set_comments("A fun, cross-platform, slidy-tile game written with C++ 17!");

    set_copyright("John Jekel @JZJisawesome");
    set_license
    (
        "This program comes with absolutely no warranty.\n"
        "See the GNU Lesser General Public License, version 3 or later for details."
    );
    set_authors
    (
        {
            "John Jekel @JZJisawesome"
        }
    );

    set_website("https://jzjisawesome.github.io/15Slide/");
    set_website_label("15Slide Website");
}

AboutSlide::~AboutSlide() {}

void AboutSlide::display()
{
    show_all();
    present();
    run();
}
}
