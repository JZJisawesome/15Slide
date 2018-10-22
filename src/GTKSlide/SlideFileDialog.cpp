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


#include "GTKSlide/SlideFileDialog.h"

#include <gtkmm.h>


namespace GTKSlide
{
    /** \brief Creates and populates a SlideFileDialog, ready to run()
     *
     * \param parent To automatically call Gtk::AboutDialog::set_transient_for()
     * \param title A title for the window
     * \param action Whether to save or load
     * \throw std::invalid_argument If action is not Gtk::FILE_CHOOSER_ACTION_OPEN or Gtk::FILE_CHOOSER_ACTION_SAVE
     */
    SlideFileDialog::SlideFileDialog(Gtk::Window &parent, const std::string &title, Gtk::FileChooserAction action) : Gtk::FileChooserDialog{title, action}
    {
        set_transient_for(parent);

        add_button("_Cancel", Gtk::RESPONSE_CANCEL);

        if (action == Gtk::FILE_CHOOSER_ACTION_OPEN)//If it is being used for loading a grid
            add_button("_Open", Gtk::RESPONSE_OK);
        else if (action == Gtk::FILE_CHOOSER_ACTION_SAVE)//If it is being used for saving a grid
            add_button("_Save", Gtk::RESPONSE_OK);
        else
            throw std::invalid_argument {"Invalid Gtk::FileChooserAction!"};

        //create file filters

        Glib::RefPtr<Gtk::FileFilter> filter_slideSave = Gtk::FileFilter::create();
        filter_slideSave->set_name("15Slide save files (.15S)");
        filter_slideSave->add_pattern("*.15S");
        //filter_slideSave->add_mime_type("text/plain");
        add_filter(filter_slideSave);

        Glib::RefPtr<Gtk::FileFilter> filter_any = Gtk::FileFilter::create();
        filter_any->set_name("Any files");
        filter_any->add_pattern("*");
        add_filter(filter_any);
    }

//not used
//SlideFileDialog::~SlideFileDialog() {}

    /** \brief Like Gtk::FileChooser::get_filename() but automatically adds the ".15S" extention if needed
     *
     * Should only be used with saving dialogs; the file extention is only added if the user saves as a "15Slide save files" type
     *
     * \return The filename choose with the ".15S" extention if needed
     */
    std::string SlideFileDialog::getFilenameWithExtention()
    {
        if ((get_filter()->get_name()) == "15Slide save files (.15S)")
            return get_filename() + ".15S";
        else
            return get_filename();
    }
}
