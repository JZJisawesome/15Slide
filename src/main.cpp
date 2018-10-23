/* MIT License
 *
 * Copyright (c) 2017-2018 John Jekel
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
 * \copyright <a href="https://github.com/JZJisawesome/15Slide/blob/master/LICENSE">MIT Licence</a>
 */


#include "ProgramStuff.h"
#include "Grid15/Grid.h"
#include "Grid15/GridHelp.h"

#include "termcolor/termcolor.hpp"

#include <cstdint>
#include <iostream>
#include <memory>
#include <exception>

#if defined(ENABLE_GUI)
    #include "GTKSlide/GTKSlide.h"
    #include "GTKSlide/MainWindow.h"
    #include <gtkmm/application.h>

    #if defined(ENABLE_CHECKS_WITH_STD_FILESYSTEM)
        #include <filesystem>
    #endif
#else
    #include "CommandUI.h"
#endif


/** \brief 15Slide main loop
 *
 * \author John Jekel
 * \date 2017-2018
**/
int main(int argc, char *argv[])
{
    try
    {
        if constexpr (ProgramStuff::Build::DEBUG)
            std::clog << "(debug)Debug mode enabled because ProgramStuff::Build::DEBUG == true" << "\n";

        std::shared_ptr<Grid15::Grid> gameGrid {new Grid15::Grid {}};

        if constexpr (ProgramStuff::CHEAT_MODE)
        {
            Grid15::GridHelp::safeCopy(Grid15::Grid::GOAL_GRID, *gameGrid);//start initiliazed as the goal grid
            Grid15::GridHelp::swapTile(15, *gameGrid);//instead of setting an entire new grid

            std::cout << termcolor::on_red;
            std::cout << "CHEATING BUILD" << "\n";
            std::cout << termcolor::reset;
        }
        else
            Grid15::GridHelp::safeCopy(Grid15::GridHelp::generateRandomGrid(), *gameGrid);


        if constexpr (ProgramStuff::CLEAR_SCREEN_ON_START)
            std::cout << "\x1b[2J";//dosent work well, maybe not at all on Windows

        std::cout << termcolor::reverse << termcolor::bold;
        std::cout << "15Slide" << "\n";
        std::cout << termcolor::reset;
        std::cout << std::endl;


        #if defined(ENABLE_GUI)

        #if defined(ENABLE_CHECKS_WITH_STD_FILESYSTEM)
        if (!(std::filesystem::exists("data/")))
            g_warning("The 15Slide \"data\" folder could not be found; 15Slide may act weird or may not work at all");
        #endif

        //does nothing usefull, no settings menu anaways
        if constexpr (GTKSlide::RUNNING_UNINSTALLED)
            Glib::setenv ("GSETTINGS_SCHEMA_DIR", ".", false);

        Glib::RefPtr<Gtk::Application> application = Gtk::Application::create(argc, argv, "io.github.jzjisawesome._15slide");//give GTK the command line arguments

        //application refrence is needed because get_application returns nullptr sometimes
        GTKSlide::MainWindow window {application, gameGrid};//give the gameGrid and application to the GUI (may want to move to heap, see below)

        //std::unique_ptr<GTKSlide::MainWindow> window {new GTKSlide::MainWindow {application, gameGrid}};//give the gameGrid and application to the GUI

        return application->run(window);//run GTKSlide and then end the main function returning the code from GTK
        #else


        std::cout << "Type \"help\" for a list of commands." << "\n";
        std::cout << termcolor::underline;
        std::cout << "If it's your first time playing, type \"demo.\"" << "\n";
        std::cout << termcolor::reset;
        std::cout << std::endl;

        CommandUI::printGrid(*gameGrid);//print initial grid
        std::cout << std::endl;

        //create a new CommandUI and give the grid to it
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
