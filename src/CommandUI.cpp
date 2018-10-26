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


#include "CommandUI.h"

#include "ProgramStuff.h"
#include "Grid15/Grid.h"
#include "Grid15/GridHelp.h"

#include "termcolor/termcolor.hpp"

#include <cstdint>
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <array>
#include <exception>


/* Command Handling */
///Possible commands
enum class CommandUI::command
{
    invalid,
    help,
    demo,
    newgame,
    slide,
    print,
    save,
    load,
    options,
    enable,
    disable,
    about,
    licence,
    exit,
    debug
};

///A map from std::string to CommandUI::command for input parsing
const std::unordered_map<std::string, CommandUI::command> CommandUI::commandMap
{
    {"help",    CommandUI::command::help},
    {"demo",    CommandUI::command::demo},
    {"newgame", CommandUI::command::newgame},
    {"slide",   CommandUI::command::slide},
    {"print",   CommandUI::command::print},
    {"save",    CommandUI::command::save},
    {"load",    CommandUI::command::load},
    {"options", CommandUI::command::options},
    {"enable",  CommandUI::command::enable},
    {"disable", CommandUI::command::disable},
    {"about",   CommandUI::command::about},
    {"licence",   CommandUI::command::licence},
    {"exit",    CommandUI::command::exit},
    {"debug",   CommandUI::command::debug}
};

/** \brief The main loop for the CommandUI
 *
 * \param grid A Grid to use
 */
void CommandUI::start(Grid15::Grid &grid)
{
    std::string inputtedLine {};

    while(!wantsToExit)
    {
        std::cout << termcolor::reverse;
        if constexpr (ProgramStuff::OS::WINDOWS)
            std::cout << "slide>";
        else
            std::cout << "slide»";//unicode
        std::cout << termcolor::reset;

        std::getline(std::cin, inputtedLine);//this seems unnecessary and slow
        handleCommand(inputtedLine, grid);
    }
}

/** \brief Handles a command from the user and does something acordingly
 *
 * \param inputtedLine The line to parse
 * \param grid The Grid to change
 */
void CommandUI::handleCommand(const std::string &inputtedLine, Grid15::Grid &grid)
{
    std::stringstream argsStream{inputtedLine};
    std::int64_t tile {0};

    constexpr auto invalidSyntaxError
    {
        []()
        {
            std::cerr << termcolor::bold << termcolor::red;
            std::cerr << "Sorry, but that syntax you used is not valid. ";
            std::cerr << termcolor::reset;
            std::cerr << "Try typing \"help\" for proper usage." << "\n";
        }
    };


    if (easySlide && argsStream >> tile)//if command is a tile and easySlide on
    {
        //FIXME check for other arguments and give an error if there is
        swapTile(tile, grid);
    }
    else
    {
        std::string input {};//place for raw user input

        argsStream.clear();//reset bad and fail bits
        argsStream >> input;//get the first command

        CommandUI::command parsedCommand {CommandUI::command::invalid};//default of invalid comman

        //make sure command is valid
        try
        {
            parsedCommand = {CommandUI::commandMap.at(input)};//throws exception if invalid
        }
        catch (std::out_of_range &e) {} //parsedCommand will remain invalid if a bad command is given

        //switch for command
        switch (parsedCommand)
        {
            case CommandUI::command::help:
            {
                CommandUI::displayHelp();
                break;
            }
            case CommandUI::command::demo:
            {
                CommandUI::runDemo();
                break;
            }
            case CommandUI::command::newgame:
            {
                if constexpr (ProgramStuff::CHEAT_MODE)
                {
                    std::cout << termcolor::on_red;
                    std::cout << "BUT WHY? YOU WERE SO CLOSE!" << "\n";
                    std::cout << termcolor::reset;
                }

                Grid15::GridHelp::safeCopy(Grid15::GridHelp::generateRandomGrid(), grid);

                std::cout << std::endl;
                printGrid(grid);
                std::cout << std::endl;

                if constexpr (ProgramStuff::Build::DEBUG)
                    std::clog << "(debug)Reseting defaultSaveFile" << "\n";

                defaultSaveFile = {""};
                break;
            }
            case CommandUI::command::slide:
            {
                if (argsStream >> tile)
                    Grid15::GridHelp::swapTile(tile, grid);
                else
                    invalidSyntaxError();
                break;
            }
            case CommandUI::command::print:
            {
                if (argsStream >> input)
                {
                    std::cout << std::endl;

                    if (input == "grid")
                        printGrid(grid);
                    else if (input == "goal")
                        printGrid(Grid15::Grid::GOAL_GRID);
                    else
                    {
                        std::cerr << termcolor::bold << termcolor::red;
                        std::cerr << "Sorry, but \"" << input << "\" is not a valid grid. ";
                        std::cerr << termcolor::reset;
                        std::cerr << "Try \"grid\" or \"goal.\"";
                    }

                    std::cout << std::endl;
                }
                else
                    invalidSyntaxError();
                break;
            }
            case CommandUI::command::save:
            {
                if (argsStream >> input)
                    saveGame(input, grid);
                else
                    invalidSyntaxError();
                break;
            }
            case CommandUI::command::load:
            {
                if (argsStream >> input)
                    loadGame(input, grid);
                else
                    invalidSyntaxError();
                break;
            }
            case CommandUI::command::options:
            {
                CommandUI::displayOptions();
                break;
            }
            case CommandUI::command::enable:
            {
                if (argsStream >> input)
                    handleOptions(input, true);
                else
                    invalidSyntaxError();
                break;
            }
            case CommandUI::command::disable:
            {
                if (argsStream >> input)
                    handleOptions(input, false);
                else
                    invalidSyntaxError();
                break;
            }
            case CommandUI::command::about:
            {
                CommandUI::displayAbout();
                break;
            }
            case CommandUI::command::licence:
            {
                CommandUI::displayLicence();
                break;
            }
            case CommandUI::command::exit:
            {
                wantsToExit = true;//if user wants to exit
                break;
            }
            case CommandUI::command::debug:
            {
                std::getline(argsStream, input);
                handleDebug(input);
                break;
            }
            case CommandUI::command::invalid://this might be triggered
            default://this not really used, but to make certain compiler warnings stop
            {
                std::cerr << termcolor::bold << termcolor::red;
                std::cerr << "Sorry, but \"" << input << "\" is not a valid command. ";
                std::cerr << termcolor::reset;
                std::cerr << "Try typing \"help\" for a list." << "\n";
            }
        }
    }
}

/* Tutorials, Settings and Information */
/// \brief The 15Slide demo
void CommandUI::runDemo()
{
    using namespace std;

    cout << endl;
    cout << termcolor::reverse << termcolor::bold;
    cout << "15Slide" << "\n";
    cout << termcolor::reset;
    cout << endl;

    cout << "Welcome to 15Slide, a fun slidy-tile game. The object is to make the grid like this:" << "\n";
    cout << endl;

    printGrid(Grid15::Grid::GOAL_GRID);
    cout << endl;

    cout << "Move the tiles agacient to the ";
    cout << termcolor::on_blue << termcolor::white;
    if constexpr (ProgramStuff::USE_UTF8_TERMINAL)
        cout << "◉◉◉";
    else
        cout << "X";
    cout << termcolor::reset;
    cout << " by typing a number and pressing enter." << "\n";
    cout << "You can save or load a game by typing \"save\" or \"load\" and the file name." << "\n";
    cout << "Start over by typing \"newgame.\"" << "\n";
    cout << "To learn about more awesome commands, type \"help.\"" << "\n";
    cout << endl;

    cout << termcolor::blink;
    cout << "ENJOY 15Slide!!!";
    if constexpr (ProgramStuff::USE_UTF8_TERMINAL)
        cout << "\xF0\x9F\x99\x82";//smile
    cout << termcolor::reset;
    cout << endl;
}

/// \brief List commands to user
void CommandUI::displayHelp()
{
    using namespace std;

    cout << endl;
    cout << termcolor::underline;
    cout << "Commands" << "\n";
    cout << termcolor::reset;
    cout << endl;

    cout << "help\t\tDisplays a list of valid commands" << "\n";
    cout << "demo\t\tWalks you through the game" << "\n";
    cout << endl;

    cout << "newgame\t\tEnds the current game and starts a new one" << "\n";
    cout << "slide\tnum\tSlides the tile with the number given" << "\n";
    cout << "print\tstr\tPrints the current \"grid\" or the \"goal\" grid" << "\n";
    cout << endl;

    cout << "save\tstr\tSaves the game to the specified file" << "\n";
    cout << "load\tstr\tLoads the game from the specified file" << "\n";
    cout << endl;

    cout << "options\t\tDisplays a list of valid options" << "\n";
    cout << "enable\tstr\tEnables the specified option" << "\n";
    cout << "disable\tstr\tDisables the specified option" << "\n";
    cout << endl;

    cout << "about\t\tCool stuff about 15Slide" << "\n";
    cout << "licence\t\tLicence information for 15Slide and other libraries" << "\n";
    cout << "exit\t\tExit 15Slide" << "\n";
    cout << endl;
}

/// \brief About 15Slide
void CommandUI::displayAbout()
{
    using namespace std;

    cout << endl;
    cout << termcolor::reverse << termcolor::bold;
    cout << "15Slide" << "\n";
    cout << termcolor::reset;
    cout << "Copyright 2017-2018 John Jekel" << "\n";
    cout << "See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms";
    cout << endl;

    cout << endl;
    cout << "15Slide is a fun, cross-platform, slidy-tile game first developed in 2017 with the C++ 17 programming language." << "\n";
    cout << "For all things 15Slide go to https://jzjisawesome.github.io/15Slide/" << "\n";
    cout << "If you find some problem or want a new feature, go create a new issue at https://github.com/JZJisawesome/15Slide/issues/new" << "\n";
    cout << "Type \"licence\" for 15Slide and other library licencing." << "\n";
    cout << endl;


    cout << endl;
    cout << termcolor::underline;
    cout << "Build Information" << "\n";
    cout << termcolor::reset;
    cout << endl;

    cout << termcolor::reverse << termcolor::bold;
    cout << "15Slide";
    cout << termcolor::reset;
    cout << " Version " << ProgramStuff::Build::SLIDE_VERSION_STRING << "\n";

    cout << "Built on " << ProgramStuff::Build::DATE << " at " << ProgramStuff::Build::TIME << " for " << ProgramStuff::OS::STRING << "\n";
    cout << "Compiler: " << ProgramStuff::Build::COMPILER_STRING << ", Version: " << ProgramStuff::Build::COMPILER_VERSION << "\n";
    cout << "C++ Version: " << ProgramStuff::Build::CPP_VERSION << "\n";
    if constexpr (ProgramStuff::CHEAT_MODE)
    {
        std::cout << termcolor::on_red;
        std::cout << "CHEATING BUILD" << "\n";
        std::cout << termcolor::reset;
    }
    cout << endl;
}

/// \brief Licence information for 15Slide and other libraries
void CommandUI::displayLicence()
{
    using namespace std;

    cout << endl;
    cout << termcolor::underline;
    cout << "Licencing" << "\n";
    cout << termcolor::reset;
    cout << endl;


    cout << endl;
    cout << termcolor::reverse << termcolor::bold;
    cout << "15Slide" << "\n";
    cout << termcolor::reset;
    cout << "MIT License" << "\n";
    cout << endl;
    
    cout << "Copyright (c) 2017-2018 John Jekel" << "\n";
    cout << endl;
    
    cout << "Permission is hereby granted, free of charge, to any person obtaining a copy" << "\n";
    cout << "of this software and associated documentation files (the \"Software\"), to deal" << "\n";
    cout << "in the Software without restriction, including without limitation the rights" << "\n";
    cout << "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell" << "\n";
    cout << "copies of the Software, and to permit persons to whom the Software is" << "\n";
    cout << "furnished to do so, subject to the following conditions:" << "\n";
    cout << endl;

    cout << "The above copyright notice and this permission notice shall be included in all" << "\n";
    cout << "copies or substantial portions of the Software." << "\n";
    cout << endl;

    cout << "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR" << "\n";
    cout << "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY," << "\n";
    cout << "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE" << "\n";
    cout << "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER" << "\n";
    cout << "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM," << "\n";
    cout << "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE" << "\n";
    cout << "SOFTWARE." << "\n";
    cout << endl;


    cout << endl;
    cout << "Termcolor" << "\n";
    cout << "A header-only C++ library for printing colored messages to the terminal." << "\n";
    cout << "Copyright (c) 2013, Ihor Kalnytskyi." << "\n";
    cout << "All rights reserved." << "\n";
    cout << endl;

    cout << "Redistribution and use in source and binary forms of the software as well" << "\n";
    cout << "as documentation, with or without modification, are permitted provided" << "\n";
    cout << "that the following conditions are met:" << "\n";
    cout << endl;

    cout << "* Redistributions of source code must retain the above copyright" << "\n";
    cout << "  notice, this list of conditions and the following disclaimer." << "\n";
    cout << endl;

    cout << "* Redistributions in binary form must reproduce the above" << "\n";
    cout << "  copyright notice, this list of conditions and the following" << "\n";
    cout << "  disclaimer in the documentation and/or other materials provided" << "\n";
    cout << "  with the distribution." << "\n";
    cout << endl;

    cout << "* The names of the contributors may not be used to endorse or" << "\n";
    cout << "  promote products derived from this software without specific" << "\n";
    cout << "  prior written permission." << "\n";
    cout << endl;

    cout << "THIS SOFTWARE AND DOCUMENTATION IS PROVIDED BY THE COPYRIGHT HOLDERS AND" << "\n";
    cout << "CONTRIBUTORS \"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT" << "\n";
    cout << "NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR" << "\n";
    cout << "A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER" << "\n";
    cout << "OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL," << "\n";
    cout << "EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO," << "\n";
    cout << "PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR" << "\n";
    cout << "PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF" << "\n";
    cout << "LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING" << "\n";
    cout << "NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS" << "\n";
    cout << "SOFTWARE AND DOCUMENTATION, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH" << "\n";
    cout << "DAMAGE." << "\n";
    cout << endl;


    cout << endl;
    cout << "gtkmm - a C++ wrapper for the Gtk toolkit" << "\n";
    cout << "Copyright 1999-2002 The gtkmm Development Team" << "\n";
    cout << endl;

    cout << "gtkmm is free software: you can redistribute it and/or modify" << "\n";
    cout << "it under the terms of the GNU Lesser General Public License as published by" << "\n";
    cout << "the Free Software Foundation, either version 2.1 of the License, or" << "\n";
    cout << "(at your option) any later version." << "\n";
    cout << endl;

    cout << "gtkmm is distributed in the hope that it will be useful," << "\n";
    cout << "but WITHOUT ANY WARRANTY; without even the implied warranty of" << "\n";
    cout << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" << "\n";
    cout << "GNU Lesser General Public License for more details." << "\n";
    cout << endl;

    cout << "You should have received a copy of the GNU Lesser General Public License" << "\n";
    cout << "along with gtkmm.  If not, see <https://www.gnu.org/licenses/>" << "\n";
    cout << endl;
}

/// \brief List options to user
void CommandUI::displayOptions()
{
    using namespace std;

    cout << endl;
    cout << termcolor::underline;
    cout << "Options" << "\n";
    cout << termcolor::reset;
    cout << endl;

    cout << "autoSave bool\tIf enabled, automatically saves the game to the last savefile. Enabled by default." << "\n";
    cout << "autoGrid bool\tIf enabled, autoprints the grid after certain commands. Enabled by default." << "\n";
    cout << "autoExit bool\tIf enabled, automatically exits the game after you win. Disabled by default." << "\n";
    cout << "easySlide bool\tAllows you to just type in a number rather than \"slide\" first. Enabled by default." << "\n";
    cout << endl;
}

/** \brief Handles an option string and sets the appropriate option
 *
 * \param option The option string to set
 * \param optionSetting Turn it on or off
 */
void CommandUI::handleOptions(const std::string &option, bool optionSetting)
{
    if      (option == "autoSave")
        autoSave = {optionSetting};
    else if (option == "autoGrid")
        autoGrid = {optionSetting};
    else if (option == "autoExit")
        autoExit = {optionSetting};
    else if (option == "easySlide")
        easySlide = {optionSetting};
    else
    {
        std::cerr << termcolor::bold << termcolor::red;
        std::cerr << "Sorry, but \"" << option << "\" is not a valid option. ";
        std::cerr << termcolor::reset;
        std::cerr << "Try typing \"options\" for a list." << "\n";
    }
}

/** \brief Handles the debug commands. Only avaliable if ProgramStuff::Build::DEBUG equals true
 *
 * \param inputtedLine The arguments to parse
 * \throw std::runtime_error If the user uses the "crash" command
 */
void CommandUI::handleDebug(const std::string& inputtedLine)
{
    if constexpr (ProgramStuff::Build::DEBUG)
    {
        std::string input {};//place for raw user input

        std::stringstream debugStream{inputtedLine};
        debugStream >> input;//parse first word

        if (input == "help")
        {
            using namespace std;

            cout << endl;
            cout << termcolor::underline;
            cout << "(debug)Debug Commands" << "\n";
            cout << termcolor::reset;
            cout << endl;

            cout << "debug help\tDisplays a list of valid debugging commands" << "\n";
            cout << endl;

            cout << "debug crash\tThrows an instance of std::runtime_error, terminating 15Slide" << "\n";
            cout << endl;
        }
        else if (input == "crash")
        {
            std::cout << "(debug)Throwing an instance of std::runtime_error" << "\n";
            throw std::runtime_error {"User induced crash by command \"debug crash\""};
        }
        else
        {
            std::cerr << termcolor::bold << termcolor::red;
            std::cerr << "(debug)Sorry, but \"" << input << "\" is not a valid debug command. ";
            std::cerr << termcolor::reset;
            std::cerr << "Try typing \"debug help\" for a list." << std::endl;
        }
    }
    else//release build
        std::cout << "Sorry, but \"debug\" is not avaliable in release builds. See \"about.\"" << "\n";
}

/* Grid Management */
/** \brief Prints a grid array
 *
 * \param grid The grid array to print
 */
void CommandUI::printGrid(const Grid15::Grid::gridArray_t gridArray)
{
    //we use printf here for speed, except for termcolor which has to use ostream
    //probably unnessary, and just makes things confusing

    if constexpr (ProgramStuff::USE_UTF8_TERMINAL)
    {
        std::printf("┏━━━┳━━━┳━━━┳━━━┓\n");//start

        for (std::uint_fast32_t i {0}; i < 4; ++i)
        {
            std::printf("┃");//coloums
            for (std::uint_fast32_t j {0}; j < 4; ++j)
            {
                if (gridArray[i][j] == Grid15::Grid::NO_TILE)
                {
                    //no tile is represented by ◉◉◉
                    std::cout << termcolor::on_blue << termcolor::white;
                    std::printf("◉◉◉");
                    std::cout << termcolor::reset;
                }
                else
                {
                    if (gridArray[i][j] <= 9)//add extra space for single digit numbers
                        std::printf(" ");

                    std::printf(" %d", static_cast<int> (gridArray[i][j]));
                }

                std::printf("┃");//coloums
            }

            std::printf("\n");

            if ((i <= 2))//all except last line
                std::printf("┣━━━╋━━━╋━━━╋━━━┫\n");//rows
        }

        std::printf("┗━━━┻━━━┻━━━┻━━━┛\n");//end
    }
    else//there is no border for this non UTF-8 method
    {
        for (std::uint_fast32_t i {0}; i < 4; ++i)
        {
            for (std::uint_fast32_t j {0}; j < 4; ++j)
            {
                if (gridArray[i][j] == Grid15::Grid::NO_TILE)
                {
                    //no tile is represented by an X
                    std::cout << termcolor::on_blue << termcolor::white;
                    std::printf("X");
                    std::cout << termcolor::reset;
                }
                else
                    std::printf("%d", static_cast<int> (gridArray[i][j]));

                if (gridArray[i][j] <= 9)//add extra space for single digit numbers
                    std::printf("   ");
                else
                    std::printf("  ");
            }
            std::printf("\n");
        }
    }
}

/** \brief Prints a Grid
 *
 * \param grid The Grid to print
 */
void CommandUI::printGrid(const Grid15::Grid &grid)
{
    printGrid(grid.gridArray);
}

/** \brief Saves the game
 *
 * \param saveFile The file to save to
 * \param grid The Grid to save
 */
void CommandUI::saveGame(const std::string &saveFile, const Grid15::Grid &grid)
{
    std::cout << "Saving game to " + saveFile + "..." << std::endl;

    try
    {
        Grid15::GridHelp::save(saveFile, grid);

        std::cout << termcolor::green;
        std::cout << "Save Complete!";
        std::cout << termcolor::reset << std::endl;

        if constexpr (ProgramStuff::Build::DEBUG)
            std::clog << "(debug)Set defaultSaveFile to " << saveFile << "\n";

        //we only get here if above works
        defaultSaveFile = {saveFile};
    }
    catch (std::ios_base::failure &e)
    {
        std::cerr << termcolor::bold << termcolor::red;
        std::cerr << "Something went wrong while saving. ";
        std::cerr << termcolor::reset;
        std::cerr << "Try a diffrent file name/location, or change permissions to allow writing.";
        std::cerr << std::endl;
    }
}

/** \brief Loads the game
 *
 * \param saveFile The file to load from
 * \param grid The Grid to load to
 */
void CommandUI::loadGame(const std::string &saveFile, Grid15::Grid &grid)
{
    std::cout << "Loading game from " + saveFile + "..." << std::endl;

    try
    {
        Grid15::GridHelp::load(saveFile, grid);

        std::cout << termcolor::green;
        std::cout << "Load Sucessfull!";
        std::cout << termcolor::reset << std::endl;

        if constexpr (ProgramStuff::Build::DEBUG)
            std::clog << "(debug)Set defaultSaveFile to " << saveFile << "\n";

        //we only get here if above works
        defaultSaveFile = {saveFile};
    }
    catch (std::ios_base::failure &e)
    {
        std::cerr << termcolor::bold << termcolor::red;
        std::cerr << "Something went wrong while loading. ";
        std::cerr << termcolor::reset;

        std::cerr << "Try a diffrent file name/location, or change permissions to allow reading.";
        std::cerr << std::endl;
    }
    catch (std::invalid_argument &e)
    {
        std::cerr << termcolor::bold << termcolor::red;
        std::cerr << "Something went wrong while importing the grid. ";
        std::cerr << termcolor::reset;

        std::cerr << "The file was read sucessfully, but the grid may be corrupted.";
        std::cerr << std::endl;
    }
}

/** \brief Swaps a tile
 *
 * \param tile The tile to swap
 * \param grid The Grid to use
 */
void CommandUI::swapTile(const std::int64_t tile, Grid15::Grid &grid)
{
    if (Grid15::GridHelp::validMove(tile, grid))//instead of a try catch block
    {
        Grid15::GridHelp::swapTile(tile, grid);

        wantsToExit = {Grid15::GridHelp::hasWon(grid) && autoExit};//if the game is over and autoExit is on then exit

        if (autoSave && (defaultSaveFile != ""))//if auto save is on and there is a default save file
        {
            try
            {
                Grid15::GridHelp::save(defaultSaveFile, grid);//silent save (dosent use saveGame)

                if constexpr (ProgramStuff::Build::DEBUG)
                    std::clog << "(debug)Autosaved the game" << "\n";
            }
            catch (std::ios_base::failure &e)
            {
                std::cerr << "Warning: The autosave failed. Try saving to a new location using \"save,\" or change file permissions." << std::endl;
            }
        }
    }
    else
    {
        std::cout << termcolor::bold << termcolor::red;
        std::cout << "Sorry, but \"" << tile << "\" is not a valid tile. ";
        std::cout << termcolor::reset;
        std::cout << "Please try again." << "\n";
    }

    if (autoGrid)
    {
        std::cout << std::endl;
        printGrid(grid);
        std::cout << std::endl;
    }

    if (Grid15::GridHelp::hasWon(grid))
    {
        std::cout << std::endl;
        std::cout << termcolor::green << termcolor::bold << termcolor::blink;
        std::cout << "YOU WON!!!";
        if constexpr (ProgramStuff::USE_UTF8_TERMINAL)
            std::cout << "\xf0\x9f\x8f\x86";//trophy
        std::cout << "\n";
        std::cout << termcolor::reset;
        std::cout << std::endl;

        if constexpr (ProgramStuff::CHEAT_MODE)
        {
            std::cout << termcolor::on_red;
            std::cout << "BUT YOU CHEATED (CHEAT_MODE = true)" << "\n";
            std::cout << termcolor::reset;
        }
    }
}
