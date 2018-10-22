#!/bin/sh
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


#15Slide Linux and cross-platform Windows build script
#This script is deprecated; use the autotools instructions at https://jzjisawesome.github.io/15Slide/Installing-15Slide


#Linux compilers
compiler="g++"
#compiler="clang++"

#Cross-platform compilers for Windows
#compiler="i686-w64-mingw32-g++"


#Options
compiler_options="-Wall -fexceptions -std=c++1z -Isrc -Iinclude -Og -g"
linker_options="-Lsrc -Linclude"


mkdir ./obj
mkdir ./obj/Grid15
mkdir ./obj/GTKSlide
$compiler $compiler_options -c ./src/CommandUI.cpp -o ./obj/CommandUI.o `pkg-config gtkmm-3.0 --cflags --libs`
$compiler $compiler_options -c ./src/Grid15/Grid.cpp -o ./obj/Grid15/Grid.o `pkg-config gtkmm-3.0 --cflags --libs`
$compiler $compiler_options -c ./src/Grid15/GridHelp.cpp -o ./obj/Grid15/GridHelp.o `pkg-config gtkmm-3.0 --cflags --libs`
$compiler $compiler_options -c ./src/main.cpp -o ./obj/main.o `pkg-config gtkmm-3.0 --cflags --libs`

$compiler $compiler_options -c ./src/GTKSlide/AboutSlide.cpp -o ./obj/GTKSlide/AboutSlide.o `pkg-config gtkmm-3.0 --cflags --libs`
$compiler $compiler_options -c ./src/GTKSlide/MainWindow.cpp -o ./obj/GTKSlide/MainWindow.o `pkg-config gtkmm-3.0 --cflags --libs`
$compiler $compiler_options -c ./src/GTKSlide/SlideFileDialog.cpp -o ./obj/GTKSlide/SlideFileDialog.o `pkg-config gtkmm-3.0 --cflags --libs`
$compiler $compiler_options -c ./src/GTKSlide/TileGrid.cpp -o ./obj/GTKSlide/TileGrid.o `pkg-config gtkmm-3.0 --cflags --libs`

mkdir ./bin
$compiler $linker_options -o ./bin/15Slide ./obj/CommandUI.o ./obj/Grid15/Grid.o ./obj/Grid15/GridHelp.o ./obj/main.o ./src/GTKSlide/AboutSlide.cpp ./src/GTKSlide/MainWindow.cpp ./src/GTKSlide/SlideFileDialog.cpp ./src/GTKSlide/TileGrid.cpp

echo "Done compiling 15Slide"

#if [compiler == "*mingw32*"]
#	then
#		echo "You may need the libgcc_s_sjlj-1.dll and libstdc++-6.dll libraries or something similar in the run directory"
#fi
