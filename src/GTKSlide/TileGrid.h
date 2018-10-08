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
#ifndef TILEGRID_H
#define TILEGRID_H


#include "Grid15/Grid.h"
#include "GTKSlide/SaveManager.h"

#include <gtkmm.h>

#include <memory>
#include <utility>
#include <cstdint>


namespace GTKSlide
{
/** \class TileGrid
 *
 * \brief A Gtk::Grid graphical representation of a Grid15::Grid
 *
 * \author John Jekel
 * \date 2018-2018
 */
class TileGrid : public Gtk::Grid
{
public:
    TileGrid(Gtk::Window &parent, std::shared_ptr<Grid15::Grid> &newGridPtr, std::shared_ptr<SaveManager> &saveManagerPtr);
    //virtual ~TileGrid();

    void lableTiles();
    void sensitizeTiles();
    void updateTiles();
protected:
    //not smart pointer because window will be on stack
    Gtk::Window *parentPtr {};///<A pointer to the parent window to call various dialogs set_transient_for()
    std::shared_ptr<Grid15::Grid> gridPtr {};///<A pointer to the grid to use

    void on_tile_clicked(std::uint8_t coordinates);
    std::unique_ptr<Gtk::Button[]> gridButtons {new Gtk::Button [16]};///<The array of buttons which represent tiles

    void displayWonDialog();
    std::shared_ptr<SaveManager> saveManager {};///<A pointer to a SaveManager for managing autosaving

    std::pair<std::uint8_t, std::uint8_t> singleToTwoD(std::uint8_t coordinates);
    std::uint8_t twoDToSingle(std::uint8_t y, std::uint8_t x);
};
}

#endif //TILEGRID_H
