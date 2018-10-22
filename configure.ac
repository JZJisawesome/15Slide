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


AC_INIT([15Slide], 0.10.1)
AM_INIT_AUTOMAKE


: ${CXXFLAGS=""}
AC_PROG_CXX
#Using -I flags is the only way I could get #include in source files to work
CXXFLAGS+=" --std=c++1z -Wall -Iinclude -Isrc -Isrc/Grid15 -Isrc/GTKSlide"


#Optomization Options
CXXFLAGS+=" -s -O3"
#CXXFLAGS+=" -s -Os"
#CXXFLAGS+=" -g -Og"

#Comment this out if you just want to run 15Slide in the command line
PKG_CHECK_MODULES([GTKMM], [gtkmm-3.0])


AC_CONFIG_FILES(Makefile)
AC_OUTPUT
