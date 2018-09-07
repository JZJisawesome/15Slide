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


#include "Grid.h"

#include <cstdint>
#include <array>
#include <algorithm>


namespace Grid15
{
/* Grid Setup */
///Creates a new Grid, leaving everything uninitialized
Grid::Grid() {}

/** \brief Creates a new Grid and copies a grid array to it
 *
 * \param newGrid The new grid array
 */
Grid::Grid(const gridArray_t &newGrid)
{
    //setGridArray(newGrid);
    std::copy(std::begin(newGrid), std::end(newGrid), std::begin(gridArray));
}

/** \brief Creates a new Grid and copies an index to it
 *
 * \param newIndex The new index
 */
Grid::Grid(const index_t &newIndex)
{
    std::copy(std::begin(newIndex), std::end(newIndex), std::begin(index));
}

/** \brief Creates a new Grid and copies a grid array and an index to it
 *
 * \param newGrid The new grid array
 * \param newIndex The new index
 */
Grid::Grid(const gridArray_t &newGrid, const index_t &newIndex)
{
    std::copy(std::begin(newGrid), std::end(newGrid), std::begin(gridArray));
    std::copy(std::begin(newIndex), std::end(newIndex), std::begin(index));
}

/** \brief Creates and copies a new Grid
 *
 * \param newGrid The new Grid
 */
Grid::Grid(const Grid& newGrid)
{
    std::copy(std::begin(newGrid.gridArray), std::end(newGrid.gridArray), std::begin(gridArray));
    std::copy(std::begin(newGrid.index), std::end(newGrid.index), std::begin(index));
}

/** \brief Copies a Grid
 *
 * \param newGrid The new Grid
 */
Grid& Grid::operator=(const Grid& newGrid)
{
    if (this == &newGrid)
        return *this;

    std::copy(std::begin(newGrid.gridArray), std::end(newGrid.gridArray), std::begin(gridArray));
    std::copy(std::begin(newGrid.index), std::end(newGrid.index), std::begin(index));

    return *this;
}

/** \brief Sets Grid::grid
 *
 * \param newGrid The new grid array to use
 */
void Grid::setGridArray(const gridArray_t &newGrid)
{
    std::copy(std::begin(newGrid), std::end(newGrid), std::begin(gridArray));
}

/** \brief Sets Grid::index
 *
 * \param newIndex The new index array to use
 */
void Grid::setIndex(const index_t &newIndex)
{
    std::copy(std::begin(newIndex), std::end(newIndex), std::begin(index));
}

/** \brief Copies a Grid
 *
 * \param newGrid The new grid
 */
void Grid::setGrid(const Grid &newGrid)
{
    std::copy(std::begin(newGrid.gridArray), std::end(newGrid.gridArray), std::begin(gridArray));
    std::copy(std::begin(newGrid.index), std::end(newGrid.index), std::begin(index));
}
}
