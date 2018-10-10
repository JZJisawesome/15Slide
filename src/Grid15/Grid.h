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
#ifndef GRID_H
#define GRID_H


#include <cstdint>
#include <array>


namespace Grid15
{
    /** \class Grid
     *
     * \brief A data type consisting of a 4 by 4 grid array, and a 16 by 2 index, for use with 15Slide
     *
     * \author John Jekel
     * \date 2018-2018
     */
    class Grid
    {
        public:
            /* Typedefs */
            typedef std::array<std::array<std::uint8_t, 4>, 4>  gridArray_t;///<The type used for Grid::gridArray
            typedef std::array<std::array<std::uint8_t, 2>, 16> index_t;///<The type used for Grid::index


            /* Grid Setup */
            Grid();
            Grid(const gridArray_t &newGrid);
            Grid(const index_t &newIndex);
            Grid(const gridArray_t &newGrid, const index_t &newIndex);
            Grid(const Grid &other);
            Grid& operator=(const Grid &other);

            void setGridArray(const gridArray_t &newGrid);
            void setGrid(const Grid &newGrid);

            void setIndex(const index_t &newIndex);

            /* Storage */
            //the grid, with [y] and [x] indexes from top left to bottom right
            //0 is no tile, 1 to 15 are the other tiles
            //FIXME [y][x] should be [x][y]
            gridArray_t gridArray {};///<The grid

            //coordinates of tiles on the grid
            //0 is no tile, 1 to 15 are the other tiles
            //eg. index[5][1] is the x coordinate of the tile 5 on the game grid from top left to bottom right
            //FIXME [tile][0] is y, [tile][1] is x, again these should be flipped
            index_t index {};///<The index to keep track of tile locations

            static constexpr std::size_t NO_TILE   {0};    ///<The number representing the lack of a tile
            static constexpr std::size_t TILE_MAX  {15};   ///<The maximum tile number
            static constexpr std::size_t TILE_MIN  {0};    ///<The mininum tile number
            static constexpr std::size_t Y_MAX     {3};    ///<The maximum y coordinate
            static constexpr std::size_t Y_MIN     {0};    ///<The mininum x coordinate
            static constexpr std::size_t X_MAX     {3};    ///<The maximum x coordinate
            static constexpr std::size_t X_MIN     {0};    ///<The mininum x coordinate

            static constexpr gridArray_t GOAL_GRID
            {
                {
                    {1,  2,  3,  4,},
                    {5,  6,  7,  8,},
                    {9,  10, 11, 12,},
                    {13, 14, 15, Grid::NO_TILE}
                }
            };
    };
}
#endif //GRID_H
