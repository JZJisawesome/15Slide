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
    gridArray_t gridArray {};///<The grid

    index_t index {};///<The index to keep track of tile locations

    static constexpr std::size_t NO_TILE   {0};    ///<The number representing the lack of a tile
    static constexpr std::size_t TILE_MAX  {15};   ///<The maximum tile number
    static constexpr std::size_t TILE_MIN  {0};    ///<The mininum tile number
    static constexpr std::size_t X_MAX     {3};    ///<The maximum x coordinate
    static constexpr std::size_t X_MIN     {0};    ///<The mininum x coordinate
    static constexpr std::size_t Y_MAX     {3};    ///<The maximum y coordinate
    static constexpr std::size_t Y_MIN     {0};    ///<The mininum x coordinate

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
#endif // GRID_H
