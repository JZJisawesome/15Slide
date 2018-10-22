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


#include "GTKSlide/TileGrid.h"

#include "ProgramStuff.h"//still used for debug messages and won dialog
#include "GTKSlide/GTKSlide.h"
#include "Grid15/Grid.h"
#include "Grid15/GridHelp.h"
#include "GTKSlide/SaveManager.h"

#include <gtkmm.h>

#include <iostream>
#include <utility>


namespace GTKSlide
{
    /** \brief Creates and populates the GTKSlide main window
     *
     * \param parent The parent window to call various dialogs set_transient_for()
     * \param newGridPtr The Grid15::Grid to use
     * \param saveManagerPtr A pointer to a SaveManager for managing autosaving
     * \throw std::invalid_argument If the Grid15::Grid given is invalid
     */
    TileGrid::TileGrid(Gtk::Window &parent, std::shared_ptr<Grid15::Grid> &newGridPtr, std::shared_ptr<SaveManager> &saveManagerPtr)
    {
        parentPtr = {&parent};//save a pointer of the parent window
        saveManager = {saveManagerPtr};//save a pointer to the save manager

        if (Grid15::GridHelp::validGrid(*newGridPtr))
            gridPtr = newGridPtr;
        else
            throw std::invalid_argument {"Grid invalid!"};

        set_border_width(5);

        //create grid of buttons

        //create the first row of tile buttons
        for (std::uint_fast32_t i {0}; i < 4; ++i)
        {
            //add signal handler
            gridButtons[twoDToSingle(0, i)].signal_clicked().connect
            (
                sigc::bind<std::uint8_t> (sigc::mem_fun(*this, &TileGrid::on_tile_clicked), twoDToSingle(0, i))//bind the tile coordinates
            );

            add(gridButtons[twoDToSingle(0, i)]);//add button to grid
        }

        //attach remaning tiles underneath first row
        for (std::uint_fast32_t i {1}; i < 4; ++i)
            for (std::uint_fast32_t j {0}; j < 4; ++j)
            {
                //add signal handler
                gridButtons[twoDToSingle(i, j)].signal_clicked().connect
                (
                    sigc::bind<std::uint8_t> (sigc::mem_fun(*this, &TileGrid::on_tile_clicked), twoDToSingle(i, j))//bind the tile coordinates
                );

                //add button to grid under last row
                attach_next_to(gridButtons[twoDToSingle(i, j)], gridButtons[twoDToSingle(i - 1, j)], Gtk::POS_BOTTOM, 1, 1);
            }

        updateTiles();
    }

//not used
//TileGrid::~TileGrid() {}

    /** The signal handler if a tile is clicked
     *
     * \param coordinates A 1 dimentional array position that will be converted to 2D for use
    */
    void TileGrid::on_tile_clicked(std::uint8_t coordinates)
    {
        auto [y, x] = singleToTwoD(coordinates);

        if constexpr (ProgramStuff::Build::DEBUG)
        {
            std::clog << std::boolalpha;//makes true or false statements appear as "true" or "false"
            std::clog << "(debug)Coordinates (" << static_cast<int> (x) << ", " << static_cast<int>(y);
            std::clog << ") aka gridArray" << "[" << static_cast<int>(y) << "][" << static_cast<int> (x) << "]";
            std::clog << " was pressed, with tile number " << static_cast<int> ((*gridPtr).gridArray[y][x]);
            std::clog << ". Valid move: " << Grid15::GridHelp::validMove(y, x, *gridPtr) << "\n";
        }

        if (Grid15::GridHelp::validMove(y, x, *gridPtr))
        {
            if constexpr (ProgramStuff::Build::DEBUG)
                std::clog << "(debug)Swapping tile... ";

            Grid15::GridHelp::swapTile(y, x, *gridPtr);
            saveManager->isSaved = {false};//just changed grid, must be unsaved

            updateTiles();//FIXME just relable the 2 tiles instead

            //check if user has won
            if constexpr (ProgramStuff::Build::DEBUG)
                std::clog << "Won: " << Grid15::GridHelp::hasWon(*gridPtr) << "\n";

            if (Grid15::GridHelp::hasWon(*gridPtr))
                displayWonDialog();

            if (saveManager->autoSave && (saveManager->saveFile != ""))//if auto save is enabled and there is a save file
            {
                try
                {
                    Grid15::GridHelp::save(saveManager->saveFile, *gridPtr);

                    //we only get here if above works
                    saveManager->isSaved = {true};

                    if constexpr (ProgramStuff::Build::DEBUG)
                        std::clog << "(debug)Auto-saved the game" << "\n";
                }
                catch (std::ios_base::failure &e)
                {
                    //reset broken save file so user can fix in save as
                    saveManager->saveFile = {""};
                    saveManager->isSaved = {false};

                    Gtk::MessageDialog errorDialog("Some this went wrong while auto-saving");
                    errorDialog.set_title("Oh no!");

                    errorDialog.set_secondary_text("Go to File -> Save As to choose a new save location");

                    //display dialog
                    errorDialog.set_transient_for(*parentPtr);
                    errorDialog.show_all();
                    errorDialog.present();
                    errorDialog.run();
                }
            }
        }


        if constexpr (ProgramStuff::Build::DEBUG)
        {
            std::clog << std::noboolalpha;
            std::clog.flush();//sometimes nothing prints until clog is flushed
        }
    }

///Both lables and sensitizes (depending on GTKSlide::SENSITIZE_VALID_MOVES_ONLY) the tiles at one
    void TileGrid::updateTiles()
    {
        lableTiles();

        if constexpr (GTKSlide::SENSITIZE_VALID_MOVES_ONLY)
            sensitizeTiles();
    }

///Lables the Gtk::Button tiles based on gridPtr tile values
    void TileGrid::lableTiles()
    {
        for (std::uint_fast32_t i {0}; i < 4; ++i)
            for (std::uint_fast32_t j {0}; j < 4; ++j)
            {
                if ((*gridPtr).gridArray[i][j] != 0)
                    gridButtons[twoDToSingle(i, j)].set_label(std::to_string((*gridPtr).gridArray[i][j]));//set the lable to the tile number
                else
                    gridButtons[twoDToSingle(i, j)].set_label("◉");//special character for the no tile
            }
    }

///Sensitizes or desensitizes Gtk::Button the tiles based on if moving them would be valid, based on gridPtr tile values
    void TileGrid::sensitizeTiles()
    {
        for (std::uint_fast32_t i {0}; i < 4; ++i)
            for (std::uint_fast32_t j {0}; j < 4; ++j)
                gridButtons[twoDToSingle(i, j)].set_sensitive(Grid15::GridHelp::validMove(i, j, *gridPtr));//allows the button to be pressed if the move is valid
    }

///Creates and displays a "won" dialog if the game is won
    void TileGrid::displayWonDialog()
    {
        Gtk::MessageDialog wonDialog("YOU WON!!!" "\xf0\x9f\x8f\x86");//second string is a trophy
        wonDialog.set_title("YOU WON!!!");

        if constexpr (ProgramStuff::CHEAT_MODE)
            wonDialog.set_secondary_text("BUT YOU CHEATED (CHEAT_MODE = true)");
        else
            wonDialog.set_secondary_text("Great Work!!!");

        //super jankey looking and discouraged way to remove ok button from dialog
        wonDialog.get_action_area()->remove
        (
            *(wonDialog.get_action_area()->get_children()[0])//1st and only element is ok button (gone now)
        );

        wonDialog.add_button("YAY!", Gtk::RESPONSE_OK);

        //display dialog
        wonDialog.set_transient_for(*parentPtr);
        wonDialog.show_all();
        wonDialog.present();
        wonDialog.run();
    }

    /** \brief A helper function to convert a single number from 0 to 15 to an x and y coordinate from 0 to 3
     *
     * Used along with TileGrid::twoDToSingle to convert the other way
     *
     * \param coordinates The merged coordinates
     * \return A std::pair with first = y coordinate and second = x coordinate
     */
    std::pair<std::uint8_t, std::uint8_t> TileGrid::singleToTwoD(std::uint8_t coordinates)
    {
        return std::pair<std::uint8_t, std::uint8_t> {coordinates / 4, coordinates % 4};
    }

    /** \brief A helper function to convert an x and y coordinate from 0 to 3 to a single number from 0 to 15
     *
     * Used to access the single dimentional array of Gtk::Buttons like a 2D one
     *
     * \param y The y coordinate (rows)
     * \param x The x coordinate (colums)
     * \return The merged coordinates
     */
    std::uint8_t TileGrid::twoDToSingle(std::uint8_t y, std::uint8_t x)
    {
        return (y * 4) + x;
    }
}
