#Copyright 2018 John Jekel
#This file is part of 15Slide.

#15Slide is free software: you can redistribute it and/or modify
#it under the terms of the GNU Lesser General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.

#15Slide is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU Lesser General Public License for more details.

#You should have received a copy of the GNU Lesser General Public License
#along with 15Slide.  If not, see <https://www.gnu.org/licenses/>

AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = 15Slide
15Slide_CPPFLAGS = $(GTKMM_CFLAGS)
15Slide_LDADD = $(GTKMM_LIBS)
15Slide_SOURCES = src/CommandUI.cpp src/CommandUI.h src/Grid15/Grid.cpp src/Grid15/Grid.h src/Grid15/GridHelp.cpp src/Grid15/GridHelp.h src/main.cpp src/GTKSlide/AboutSlide.cpp src/GTKSlide/AboutSlide.h src/GTKSlide/MainWindow.cpp src/GTKSlide/MainWindow.h src/GTKSlide/SlideFileDialog.cpp src/GTKSlide/SlideFileDialog.h src/GTKSlide/TileGrid.cpp src/GTKSlide/TileGrid.h
include_HEADERS = include/termcolor/termcolor.hpp
