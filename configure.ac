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


AC_INIT([15Slide], 0.9)
AM_INIT_AUTOMAKE


: ${CXXFLAGS=""}
AC_PROG_CXX
CXXFLAGS+=" --std=c++1z -Wall -Iinclude -Isrc -Isrc/Grid15 -Isrc/GTKSlide"

#Optomization Options
CXXFLAGS+=" -s -O3"
#CXXFLAGS+=" -s -Os"
#CXXFLAGS+=" -g -Og"

PKG_CHECK_MODULES([GTKMM], [gtkmm-3.0])


AC_CONFIG_FILES(Makefile)
AC_OUTPUT
