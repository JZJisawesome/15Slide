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
#ifndef PROGRAMSTUFF_H
#define PROGRAMSTUFF_H


#include <cstdint>


/** \namespace ProgramStuff
 *
 * \brief Information/options for use in 15Slide
 *
 * \author John Jekel
 * \date 2018-2018
*/
namespace ProgramStuff
{
    /* Namespace Definitions */
    ///Compiliation related constants
    namespace Build {}
    ///Operating System related constants
    namespace OS {}
    ///GTKSlide related constants
    namespace GTKSlide {}
    ///File names and locations for GTKSlide reasources
    namespace GTKSlide::Resources {}


    /* Macros to constants */
    namespace OS
    {
        #if     defined(__unix__) || defined(__unix) || defined(__linux__)
        #define __SLIDELINUX 1
        constexpr char STRING[] {"Linux"};      ///<The string for the OS

        constexpr bool LINUX    {true}; ///<Running on Linux
        constexpr bool BSD      {false};///<Running on FreeBSD
        constexpr bool WINDOWS  {false};///<Running on Windows
        constexpr bool MAC      {false};///<Running on macOS
        constexpr bool UNKNOWN  {false};///<Running on an unknown operating system
        #elif   defined(_FreeBSD_)
        #define __SLIDEBSD 1
        constexpr char STRING[] {"FreeBSD"};    ///<The string for the OS

        constexpr bool LINUX    {false};///<Running on Linux
        constexpr bool BSD      {true}; ///<Running on FreeBSD
        constexpr bool WINDOWS  {false};///<Running on Windows
        constexpr bool MAC      {false};///<Running on macOS
        constexpr bool UNKNOWN  {false};///<Running on an unknown operating system
        #elif   defined(WIN32) || defined(_WIN32) || defined(_WIN64)
        #define __SLIDEWINDOWS 1
        constexpr char STRING[] {"Windows"};    ///<The string for the OS

        constexpr bool LINUX    {false};///<Running on Linux
        constexpr bool BSD      {false};///<Running on FreeBSD
        constexpr bool WINDOWS  {true}; ///<Running on Windows
        constexpr bool MAC      {false};///<Running on macOS
        constexpr bool UNKNOWN  {false};///<Running on an unknown operating system

        #define WIN32_LEAN_AND_MEAN//reduce <windows.h> size
        #elif   defined(__APPLE__) || defined(__MACH__)
        #define __SLIDEMAC 1
        constexpr char STRING[] {"macOS"};      ///<The string for the OS

        constexpr bool LINUX    {false};///<Running on Linux
        constexpr bool BSD      {false};///<Running on FreeBSD
        constexpr bool WINDOWS  {false};///<Running on Windows
        constexpr bool MAC      {true}; ///<Running on macOS
        constexpr bool UNKNOWN  {false};///<Running on an unknown operating system
        #else
        constexpr char STRING[] {"unknown"};    ///<The string for the OS

        constexpr bool LINUX    {false};///<Running on Linux
        constexpr bool BSD      {false};///<Running on FreeBSD
        constexpr bool WINDOWS  {false};///<Running on Windows
        constexpr bool MAC      {false};///<Running on macOS
        constexpr bool UNKNOWN  {true}; ///<Running on an unknown operating system
        #endif
    }

    namespace Build
    {
        #if     defined(__clang__)
        constexpr char COMPILER_STRING[] {"CLang"};     ///<The string for the compiler

        constexpr bool CLANG    {true}; ///<Compiled with CLang
        constexpr bool MINGW    {false};///<Compiled with MinGW
        constexpr bool GCC      {false};///<Compiled with GCC
        #elif   defined(__MINGW32__)
        constexpr char COMPILER_STRING[] {"MinGW"};     ///<The string for the compiler

        constexpr bool CLANG    {false};///<Compiled with CLang
        constexpr bool MINGW    {true}; ///<Compiled with MinGW
        constexpr bool GCC      {false};///<Compiled with GCC
        #elif   defined(__GNUG__)
        constexpr char COMPILER_STRING[] {"GCC"};       ///<The string for the compiler

        constexpr bool CLANG    {false};///<Compiled with CLang
        constexpr bool MINGW    {false};///<Compiled with MinGW
        constexpr bool GCC      {true}; ///<Compiled with GCC
        #else
        constexpr char COMPILER_STRING[] {"Unknown"};   ///<The string for the compiler

        constexpr bool CLANG    {false};///<Compiled with CLang
        constexpr bool MINGW    {false};///<Compiled with MinGW
        constexpr bool GCC      {false};///<Compiled with GCC
        #endif

        #if     defined(__VERSION__)
        constexpr char COMPILER_VERSION[] {__VERSION__};    ///<Compiler version (equal to __VERSION__ on compatiable compilers)
        #else
        constexpr char COMPILER_VERSION[] {"???"};          ///<Compiler version (equal to __VERSION__ on compatiable compilers)
        #endif

        constexpr std::uint32_t CPP_VERSION {__cplusplus};  ///<C++ version (equal to __cplusplus)

        constexpr char DATE[] {__DATE__};                   ///<Compiliation date (equal to __DATE__)
        constexpr char TIME[] {__TIME__};                   ///<Compiliation time (equal to __TIME__)
    }


    /* Safe to modify constants */
    constexpr bool CHEAT_MODE {false};///<Create a cheap grid each run
    constexpr bool USE_UTF8_TERMINAL {true && !OS::WINDOWS};///<Use UTF-8 throuought the program; not avaliable on Windows

    constexpr bool CLEAR_SCREEN_ON_START {false};///<Clear Screen on start with acsii code

    //FIXME changing this will not effect the graphical checkbox in the options of GTKSlide
    //the menuBar.glade file must be changed to inactive as well
    constexpr bool AUTOSAVE_ON_SLIDE_DEFAULT {true};///<To autosave after each slide by default or not


    #ifndef __SLIDEWINDOWS
        //comment out to disable
        #define ENABLE_GUI 1
    #endif

    #if defined(ENABLE_GUI)
    constexpr bool GTKSLIDE_ENABLED {true};///<15Slide will use GTKSlide instead of CommandUI
    #else
    constexpr bool GTKSLIDE_ENABLED {false};///<15Slide will use GTKSlide instead of CommandUI
    #endif


    namespace Build
    {
        constexpr char  SLIDE_VERSION_STRING[]   {"0.10.1"}; ///<15Slide Version String

        constexpr bool DEBUG            {true};     ///<Debug build (adds messages and command in CommandUI)
        constexpr bool RELEASE          {!DEBUG};   ///<Release build
    }
}
#endif //PROGRAMSTUFF_H
