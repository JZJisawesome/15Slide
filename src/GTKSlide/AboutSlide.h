//Copyright 2018 John Jekel
//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms
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
