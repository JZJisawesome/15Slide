/* Copyright 2018 John Jekel
 * This file is part of 15Slide.
 *
 * 15Slide is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * 15Slide is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with 15Slide.  If not, see <https://www.gnu.org/licenses/>
*/


/** \mainpage
 *
 * \section welcome_sec Welcome!!!
 *
 * Welcome to the 15Slide Documentation!
 *
 * For all things 15Slide go to <a href="https://jzjisawesome.github.io/15Slide/">the website</a>, or the <a href="https://github.com/JZJisawesome/15Slide">the Github repo</a>.
 *
 * \author John Jekel
 * \date 2017-2018
 * \copyright <a href="https://github.com/JZJisawesome/15Slide/blob/master/LICENSE">GNU Lesser General Public Licence Version 3 (LGPL v.3.0)</a>
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

#if defined(ENABLE_GUI)
#include "GTKSlide/MainWindow.h"
#include <gtkmm/application.h>

#if defined(ENABLE_CHECKS_WITH_STD_FILESYSTEM)
#include <filesystem>
#endif
#endif


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

#if defined(ENABLE_GUI)
#if defined(ENABLE_CHECKS_WITH_STD_FILESYSTEM)
        if (!(std::filesystem::exists("data/")))
            g_warning("The 15Slide \"data\" folder could not be found; 15Slide may act weird or may not work at all");
#endif
        if constexpr (ProgramStuff::GTKSlide::RUNNING_UNINSTALLED)
            Glib::setenv ("GSETTINGS_SCHEMA_DIR", ".", false);

        Glib::RefPtr<Gtk::Application> application = Gtk::Application::create(argc, argv, "15Slide");

        //application refrence is needed because get_application returns nullptr sometimes
        GTKSlide::MainWindow window {application, gameGrid};//give the gameGrid to the GUI (may want to move to heap)

        //std::unique_ptr<GTKSlide::MainWindow> window {new GTKSlide::MainWindow {application, gameGrid}};//give the gameGrid to the GUI

        return application->run(window);
#else
        std::cout << "Type \"help\" for a list of commands." << "\n";
        std::cout << termcolor::underline;
        std::cout << "If it's your first time playing, type \"demo.\"" << "\n";
        std::cout << termcolor::reset;
        std::cout << std::endl;

        CommandUI::printGrid(*gameGrid);
        std::cout << std::endl;

        CommandUI terminalUI {};
        terminalUI.start(*gameGrid);

        std::cout << std::endl;
        std::cout << "Thanks for playing 15Slide. Goodbye!";
        if constexpr (ProgramStuff::USE_UTF8_TERMINAL)
            std::cout << "\xF0\x9F\x91\x8B";//waving hand
        std::cout << "\n";
#endif
    }
    catch (...)
    {
        std::cerr << termcolor::bold << termcolor::red;
        std::cerr << "A fatal error has occured and 15Slide has crashed." << "\n";
        std::cerr << termcolor::reset;
        std::cerr << std::endl;

        if constexpr (ProgramStuff::Build::DEBUG)
            std::clog << "(debug)Rethrowing Exception" << "\n";

        throw;
    }

    return 0;
}
