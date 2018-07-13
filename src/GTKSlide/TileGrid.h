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


namespace GTKSlide
{
class TileGrid : public Gtk::Grid
{
public:
    TileGrid(Gtk::Window &parent, std::shared_ptr<Grid15::Grid> &newGridPtr, std::shared_ptr<SaveManager> &saveManagerPtr);
    virtual ~TileGrid();

    void lableTiles();
    void sensitizeTiles();
    void updateTiles();
protected:
    Gtk::Window *parentPtr {};//not smart pointer because window will be on stack
    std::shared_ptr<Grid15::Grid> gridPtr {};

    void on_tile_clicked(std::pair<int,int> &coordinates);
    Gtk::Button gridButtons[4][4];
    //std::unique_ptr<Gtk::Button>//this array takes up lots of space

    void displayWonDialog();
    std::shared_ptr<SaveManager> saveManager {};

    void setupGrid(std::shared_ptr<Grid15::Grid> &newGridPtr);
};
}

#endif //TILEGRID_H
