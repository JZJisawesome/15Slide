#!/bin/sh

compiler=g++
#compiler=clang++

mkdir ./obj
mkdir ./obj/Grid15
g++ -Wall -fexceptions -std=c++1z -Og -g -Isrc -Iinclude -c ./src/CommandUI.cpp -o ./obj/CommandUI.o
g++ -Wall -fexceptions -std=c++1z -Og -g -Isrc -Iinclude -c ./src/Grid15/Grid.cpp -o ./obj/Grid15/Grid.o
g++ -Wall -fexceptions -std=c++1z -Og -g -Isrc -Iinclude -c ./src/Grid15/GridHelp.cpp -o ./obj/Grid15/GridHelp.o
g++ -Wall -fexceptions -std=c++1z -Og -g -Isrc -Iinclude -c ./src/main.cpp -o ./obj/main.o

mkdir ./bin
g++ -Lsrc -Linclude -o ./bin/15Slide ./obj/CommandUI.o ./obj/Grid15/Grid.o ./obj/Grid15/GridHelp.o ./obj/main.o

echo "Done compiling 15Slide"
