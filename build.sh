#!/bin/sh
#Copyright 2018 John Jekel
#See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms

#15Slide Linux and cross-platform Windows build script
#See https://github.com/JZJisawesome/15Slide/wiki/Installing-15Slide for usage


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
