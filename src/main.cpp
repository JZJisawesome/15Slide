/** \mainpage
 *
 * \section welcome_sec Welcome!!!
 *
 * Welcome to 15Slide, a cross-platform(ish) slidy-tile game written in C++!
 *
 *
 * \author JZJisawesome
 * \date 2017-2018
 *
 * \section status_sec Status
 *
 * - Grid15 classes are done except for more optomization
 * - CommandUI is pretty much done, except for more detailed parsing
 * - Spelling throuought needs work, and UTF-8 support with Windows builds needs fixing
 * - Better/more documentation
 * - Simplfy this page and move it to README.MD
 *
 * \section credits_sec Credits, Libraries and Reasources
 * People (so far)
 * - JZJisawesome (14 as of 2018)
 *
 * Libraries
 * - termcolor (for terminal colour and fonts: http://termcolor.readthedocs.io/)
 * - gtkmm (for GTKSlide: https://www.gtkmm.org/)
 *
 * Reasources
 * - cpprefrence (https://www.cppreference.com)
 * - cplusplus (http://www.cplusplus.com/)
 * - Standard C++ Website (https://isocpp.org/)
 * - C++ 17 STL Cookbook by Jacek Galowicz in June 2017 (https://www.packtpub.com/application-development/c17-stl-cookbook)
 * - gtkmm Tutorial and Refrence (https://developer.gnome.org/gtkmm-tutorial/)
 * - Various forums (espically https://stackoverflow.com/)
 */


#include "ProgramStuff.h"

#include "Grid15/Grid.h"
#include "Grid15/GridHelp.h"
#include "CommandUI.h"


#include "termcolor/termcolor.hpp"

#include <cstdint>

#include <iostream>

#include <memory>

#include <exception>

/** \brief 15Slide main loop
 *
 * \author JZJisawesome
 * \date 2017-2018
**/
int main(int argc, char *argv[])
{
    if constexpr (ProgramStuff::Build::DEBUG)
        std::clog << "(debug)Entering main() try block" << "\n";

    try
    {
        std::shared_ptr<Grid15::Grid> gameGrid {new Grid15::Grid {}};

        if constexpr (ProgramStuff::CHEAT_MODE)
        {
            Grid15::GridHelp::copyGridArray(Grid15::Grid::GOAL_GRID, *gameGrid);//start initiliazed as the goal grid
            Grid15::GridHelp::swapTile(15, *gameGrid);//instead of setting an entire new grid

            std::cout << termcolor::on_red;
            std::cout << "CHEATING BUILD" << "\n";
            std::cout << termcolor::reset;
        }
        else
            Grid15::GridHelp::copyGrid(Grid15::GridHelp::generateRandomGrid(), *gameGrid);


        if constexpr (ProgramStuff::CLEAR_SCREEN_ON_START)
            std::cout << "\x1b[2J";//dosent work well, maybe not at all on windows

        std::cout << termcolor::reverse << termcolor::bold;
        std::cout << "15Slide" << "\n";
        std::cout << termcolor::reset;
        std::cout << std::endl;

        std::cout << "Type \"help\" for a list of commands." << "\n";
        std::cout << termcolor::underline;
        std::cout << "If it's your first time playing, type \"demo.\"" << "\n";
        std::cout << termcolor::reset;
        std::cout << std::endl;

        CommandUI::printGrid(*gameGrid);
        std::cout << std::endl;

        CommandUI terminalUI {};
        terminalUI.start(*gameGrid);
    }
    catch (std::exception &e)
    {
        std::cerr << termcolor::bold << termcolor::red;
        std::cerr << "A fatal error has occured and 15Slide has crashed." << "\n";
        std::cerr << termcolor::reset;
        std::cerr << std::endl;

        if constexpr (ProgramStuff::Build::DEBUG)
            std::clog << "(debug)Rethrowing Exception" << "\n";

        //throw e;
        throw;//so we get the authentic exceptiony goodness
    }

    std::cout << std::endl;
    std::cout << "Thanks for playing 15Slide. Goodbye!";
    if constexpr (ProgramStuff::USE_UTF8_TERMINAL)
        std::cout << "\xF0\x9F\x91\x8B";//waving hand
    std::cout << "\n";

    return 0;
}
