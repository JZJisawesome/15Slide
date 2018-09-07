#!/bin/sh
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


#15Slide Linux and cross-platform Windows build script
#See https://github.com/JZJisawesome/15Slide/wiki/Installing-15Slide for usage

#(this script might be broken)


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
$compiler $compiler_options -c ./src/CommandUI.cpp -o ./obj/CommandUI.o
$compiler $compiler_options -c ./src/Grid15/Grid.cpp -o ./obj/Grid15/Grid.o
$compiler $compiler_options -c ./src/Grid15/GridHelp.cpp -o ./obj/Grid15/GridHelp.o
$compiler $compiler_options -c ./src/main.cpp -o ./obj/main.o

mkdir ./bin
$compiler $linker_options -o ./bin/15Slide ./obj/CommandUI.o ./obj/Grid15/Grid.o ./obj/Grid15/GridHelp.o ./obj/main.o

echo "Done compiling 15Slide"

#if [compiler == "*mingw32*"]
#	then
#		echo "You may need the libgcc_s_sjlj-1.dll and libstdc++-6.dll libraries or something similar in the run directory"
#fi
