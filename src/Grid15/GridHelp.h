#ifndef GRIDHELP_H
#define GRIDHELP_H

#include "Grid.h"

#include <cstdint>

#include <string>
#include <array>

namespace Grid15
{
/** \brief Helps with movement of tiles, saving/loading, and other management features for a Grid
 *
 * \author JZJisawesome
 * \date 2018-2018
 */
namespace GridHelp
{
bool validMove(const std::int64_t tileNum, const Grid &grid);
bool validMove(const std::int64_t tileX, const std::int64_t tileY, const Grid &grid);
bool hasWon(const Grid &grid);

void copyGridArray(const Grid15::Grid::gridArray_t &newGrid, Grid &grid);
void copyGrid(const Grid &newGrid, Grid &grid);

bool validGridArray(const Grid15::Grid::gridArray_t &grid);
bool validGrid(const Grid &grid);

bool validIndex(const Grid15::Grid::gridArray_t &grid, const Grid15::Grid::index_t &index);

void swapTile(const std::uint8_t tileX, const std::uint8_t tileY, Grid &grid);
void swapTile(const std::uint8_t tileNum, Grid &grid);

std::uint8_t getTile(const std::uint8_t tileX, const std::uint8_t tileY, const Grid &grid);
std::uint8_t getX(const std::uint8_t tileNum, const Grid &grid);
std::uint8_t getY(const std::uint8_t tileNum, const Grid &grid);

Grid15::Grid::gridArray_t generateRandomGridArray();
Grid generateRandomGrid();

void save(const std::string &saveFile, const Grid &grid);
void load(const std::string &saveFile, Grid &grid);

void reIndex(Grid &grid);
}
}
#endif // GRIDHELP_H
