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


#include "GTKSlide/TileGrid.h"

#include "ProgramStuff.h"
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
    parentPtr = {&parent};
    saveManager = {saveManagerPtr};

    if (Grid15::GridHelp::validGrid(*newGridPtr))
        gridPtr = newGridPtr;
    else
        std::invalid_argument {"Grid invalid!"};

    //create the first row of tiles
    for (std::uint_fast32_t i {0}; i < 4; ++i)
    {
        gridButtons[twoDToSingle(0, i)].signal_clicked().connect
        (
            sigc::bind<std::uint8_t> (sigc::mem_fun(*this, &TileGrid::on_tile_clicked), twoDToSingle(0, i))//bind the tile coordinates
        );

        add(gridButtons[twoDToSingle(0, i)]);
    }

    //attach remaning tiles underneath first row
    for (std::uint_fast32_t i {1}; i < 4; ++i)
        for (std::uint_fast32_t j {0}; j < 4; ++j)
        {
            gridButtons[twoDToSingle(i, j)].signal_clicked().connect
            (
                sigc::bind<std::uint8_t> (sigc::mem_fun(*this, &TileGrid::on_tile_clicked), twoDToSingle(i, j))//bind the tile coordinates
            );

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
    auto [x, y] = singleToTwoD(coordinates);

    if constexpr (ProgramStuff::Build::DEBUG)
    {
        std::clog << std::boolalpha;
        std::clog << "(debug)Coordinates (" << static_cast<int> (x) << ", " << static_cast<int>(y);
        std::clog << ") was pressed, with tile number " << static_cast<int> ((*gridPtr).gridArray[x][y]);
        std::clog << ". Valid move: " << Grid15::GridHelp::validMove(x, y, *gridPtr) << "\n";
    }

    if (Grid15::GridHelp::validMove(x, y, *gridPtr))
    {
        if constexpr (ProgramStuff::Build::DEBUG)
            std::clog << "(debug)Swapping tile... ";

        Grid15::GridHelp::swapTile(x, y, *gridPtr);
        saveManager->isSaved = {false};

        updateTiles();//fixme: just relable the 2 tiles instead

        if constexpr (ProgramStuff::Build::DEBUG)
            std::clog << "Won: " << Grid15::GridHelp::hasWon(*gridPtr) << "\n";


        if (Grid15::GridHelp::hasWon(*gridPtr))
            displayWonDialog();

        if (saveManager->autoSave && (saveManager->saveFile != ""))
        {
            try
            {
                Grid15::GridHelp::save(saveManager->saveFile, *gridPtr);//fixme error handling


                //we only get here if above works
                saveManager->isSaved = {true};

                if constexpr (ProgramStuff::Build::DEBUG)
                    std::clog << "(debug)Auto-saved the game" << "\n";
            }
            catch (std::ios_base::failure &e)
            {
                saveManager->saveFile = {""};
                saveManager->isSaved = {false};

                Gtk::MessageDialog errorDialog("Some this went wrong while auto-saving");
                errorDialog.set_title("Oh no!");

                errorDialog.set_secondary_text("Go to File -> Save As to choose a new save location");

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

///Both lables and sensitizes (depending on ProgramStuff::GTKSlide::SENSITIZE_VALID_MOVES_ONLY) the tiles at one
void TileGrid::updateTiles()
{
    lableTiles();

    if constexpr (ProgramStuff::GTKSlide::SENSITIZE_VALID_MOVES_ONLY)
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

    //super jankey looking and discouraged way to remove ok button
    wonDialog.get_action_area()->remove
    (
        *(wonDialog.get_action_area()->get_children()[0])//1st and only element is ok button (gone now)
    );

    wonDialog.add_button("YAY!", Gtk::RESPONSE_OK);

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
 * \return A std::pair with first = x coordinate and second = y coordinate
 */
std::pair<std::uint8_t, std::uint8_t> TileGrid::singleToTwoD(std::uint8_t coordinates)
{
    return std::pair<std::uint8_t, std::uint8_t> {coordinates / 4, coordinates % 4};
}

/** \brief A helper function to convert an x and y coordinate from 0 to 3 to a single number from 0 to 15
 *
 * Used to access the single dimentional array of Gtk::Buttons like a 2D one
 *
 * \param x The x coordinate (rows)
 * \param y The y coordinate (colums)
 * \return The merged coordinates
 */
std::uint8_t TileGrid::twoDToSingle(std::uint8_t x, std::uint8_t y)
{
    return (x * 4) + y;
}
}
