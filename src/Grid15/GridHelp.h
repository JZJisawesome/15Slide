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
#ifndef GRIDHELP_H
#define GRIDHELP_H


#include "Grid15/Grid.h"

#include <cstdint>
#include <string>
#include <array>


namespace Grid15
{
/** \brief Helps with movement of tiles, saving/loading, and other management features for a Grid
 *
 * \author John Jekel
 * \date 2018-2018
 */
namespace GridHelp
{
bool validMove(const std::uint8_t tileNum, const Grid &grid);
bool validMove(const std::uint8_t tileX, const std::uint8_t tileY, const Grid &grid);
bool hasWon(const Grid &grid);

void safeCopy(const Grid::gridArray_t &newGrid, Grid &grid);
void safeCopy(const Grid &newGrid, Grid &grid);

bool validGridArray(const Grid::gridArray_t &grid);
bool validGrid(const Grid &grid);

bool validIndex(const Grid::gridArray_t &grid, const Grid::index_t &index);

void swapTile(const std::uint8_t tileX, const std::uint8_t tileY, Grid &grid);
void swapTile(const std::uint8_t tileNum, Grid &grid);

Grid::gridArray_t generateRandomGridArray();
Grid generateRandomGrid();
bool solvableGrid(const Grid &grid);
bool solvableGrid(const Grid::gridArray_t &gridArray);

void save(const std::string &saveFile, const Grid15::Grid &grid);
void load(const std::string &saveFile, Grid &grid);

void reIndex(Grid &grid);
}
}
#endif //GRIDHELP_H
