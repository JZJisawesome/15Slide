//Copyright 2018 John Jekel
//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms
#include "GTKSlide/AboutSlide.h"

#include "ProgramStuff.h"

namespace GTKSlide
{
AboutSlide::AboutSlide(Gtk::Window &window)
{
    set_transient_for(window);

    set_program_name("15Slide");
    set_version(ProgramStuff::Build::SLIDE_VERSION_STRING);
    set_comments("A fun, cross-platform, slidy-tile game written with C++ 17!");

    set_copyright("John Jekel");
    set_license
    (
        "Lesser GNU Public Licence\n"
        "See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms"
    );
    set_authors
    (
        {
            "John Jekel"
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
