#MIT License

#Copyright (c) 2018 John Jekel

#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:

#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.

#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.



AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = 15Slide

#Comment out these lines to use 15Slide in the terminal
15Slide_CPPFLAGS = $(GTKMM_CFLAGS)
15Slide_LDADD = $(GTKMM_LIBS)
15Slide_SOURCES = src/Grid15/Grid.cpp src/Grid15/Grid.h src/Grid15/GridHelp.cpp src/Grid15/GridHelp.h src/main.cpp src/GTKSlide/MainWindow.cpp src/GTKSlide/MainWindow.h src/GTKSlide/SlideFileDialog.cpp src/GTKSlide/SlideFileDialog.h src/GTKSlide/TileGrid.cpp src/GTKSlide/TileGrid.h

#Comment out this line to use GTKSlide
#15Slide_SOURCES = src/CommandUI.cpp src/CommandUI.h src/Grid15/Grid.cpp src/Grid15/Grid.h src/Grid15/GridHelp.cpp src/Grid15/GridHelp.h src/main.cpp

include_HEADERS = include/termcolor/termcolor.hpp
