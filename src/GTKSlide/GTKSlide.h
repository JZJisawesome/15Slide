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
#ifndef GTKSLIDE_H
#define GTKSLIDE_H


#include "GTKSlide/MainWindow.h"
#include "GTKSlide/TileGrid.h"
#include "GTKSlide/SlideFileDialog.h"
#include "GTKSlide/SaveManager.h"


/** \namespace GTKSlide
 *
 * \brief A graphical user interface for 15Slide
 *
 * \author John Jekel
 * \date 2018-2018
 */
namespace GTKSlide
{
    constexpr bool RUNNING_UNINSTALLED          {true};                 ///<Not really important until a settings dialog is created
    constexpr bool SENSITIZE_VALID_MOVES_ONLY   {true};                 ///<Only allow tiles that can be validly moved to be clicked in GTKSlide::TileGrid

    ///15Slide file locations
    namespace Resources
    {
        constexpr char  MENUBAR_XML[]       {"data/menuBar.glade"};     ///<File to create the menu bar for GTKSlide::MainWindow
        constexpr char  ABOUTSLIDE_XML[]    {"data/aboutSlide.glade"};  ///<File to create the about dialog box
        constexpr char  LOGO[]              {"data/logo.png"};          ///<The location of the 15Slide logo
    }
}

#endif // GTKSLIDE_H
