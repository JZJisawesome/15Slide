//Copyright 2018 John Jekel
//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms
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

namespace Build
{
constexpr float SLIDE_VERSION   {0.9};                  ///<15Slide Version
constexpr char  SLIDE_VERSION_STRING[]   {"0.9-debug"}; ///<15Slide Version String


constexpr bool DEBUG            {true};     ///<Debug build
constexpr bool RELEASE          {!DEBUG};   ///<Release build
}


namespace GTKSlide
{
#ifndef __SLIDEWINDOWS
#define ENABLE_GUI 1
#endif

#if defined(ENABLE_GUI)
constexpr bool ENABLED {true};///<15Slide will use GTKSlide instead of CommandUI
#else
constexpr bool ENABLED {false};///<15Slide will use GTKSlide instead of CommandUI
#endif

constexpr bool SENSITIZE_VALID_MOVES_ONLY {true};///<Only allow tiles that can be validly moved to be clicked in GTKSlide::TileGrid

constexpr bool USE_EXTERNAL_MENUBAR_XML {true};///<Use an external file (see ProgramStuff::GTKSlide::Resources::MENUBAR_XML) to create the menu bar for GTKSlide::MainWindow

namespace Resources
{
constexpr char  MENUBAR_XML[]   {"data/menuBar.glade"};///<If ProgramStuff::GTKSlide::USE_EXTERNAL_MENUBAR_XML is true, use this file to create the menu bar for GTKSlide::MainWindow
constexpr char  LOGO[] {"data/logo.png"};///<The location of the 15Slide logo
}
}
}
#endif //PROGRAMSTUFF_H
