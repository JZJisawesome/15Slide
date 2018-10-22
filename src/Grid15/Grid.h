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
            //TODO change to std::uint_fast32_t for speed
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

            //TODO change "no tile" to "blank tile" or just "blank"
            static constexpr std::size_t NO_TILE   {0};    ///<The number representing the lack of a tile
            static constexpr std::size_t TILE_MAX  {15};   ///<The maximum tile number
            static constexpr std::size_t TILE_MIN  {0};    ///<The mininum tile number
            static constexpr std::size_t Y_MAX     {3};    ///<The maximum y coordinate
            static constexpr std::size_t Y_MIN     {0};    ///<The mininum x coordinate
            static constexpr std::size_t X_MAX     {3};    ///<The maximum x coordinate
            static constexpr std::size_t X_MIN     {0};    ///<The mininum x coordinate

            ///How the gridArray should be when the game is won
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
