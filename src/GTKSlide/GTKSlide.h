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
