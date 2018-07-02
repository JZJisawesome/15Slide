//Copyright 2018 John Jekel
//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms
/** \mainpage
 *
 * \section welcome_sec Welcome!!!
 *
 * Welcome to 15Slide, a fun, cross-platform, slidy-tile game written with C++17!
 *
 * To contribute, to learn about used libraries and for much more, go to <a href="https://github.com/JZJisawesome/15Slide">the 15Slide Github repo</a>.
 *
 * \author John Jekel
 * \date 2017-2018
 * \copyright <a href="https://github.com/JZJisawesome/15Slide/blob/master/LICENSE">Lesser GNU Public Licence (LGPL)</a>
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
 * \author John Jekel
 * \date 2017-2018
**/
int main(int argc, char *argv[])
{
    if constexpr (ProgramStuff::Build::DEBUG)
    {
        std::clog << "(debug)Debug mode enabled because ProgramStuff::Build::DEBUG == true" << "\n";
        std::clog << "(debug)Entering main() try block" << "\n";
    }

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
