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
 * \date 2018-2018
 */
namespace GridHelp
{
bool validMove(const std::int64_t tileNum, const Grid15::Grid &grid);
bool validMove(const std::int64_t tileX, const std::int64_t tileY, const Grid15::Grid &grid);
bool hasWon(const Grid &grid);

void copyGridArray(const Grid15::Grid::gridArray_t &newGrid, Grid15::Grid &grid);
void copyGrid(const Grid &newGrid, Grid15::Grid &grid);

bool validGridArray(const Grid15::Grid::gridArray_t &grid);
bool validGrid(const Grid &grid);

bool validIndex(const Grid15::Grid::gridArray_t &grid, const Grid15::Grid::index_t &index);

void swapTile(const std::uint8_t tileX, const std::uint8_t tileY, Grid15::Grid &grid);
void swapTile(const std::uint8_t tileNum, Grid15::Grid &grid);

std::uint8_t getTile(const std::uint8_t tileX, const std::uint8_t tileY, const Grid15::Grid &grid);
std::uint8_t getX(const std::uint8_t tileNum, const Grid15::Grid &grid);
std::uint8_t getY(const std::uint8_t tileNum, const Grid15::Grid &grid);

Grid15::Grid::gridArray_t generateRandomGridArray();
Grid15::Grid generateRandomGrid();
bool solvableGrid(const Grid15::Grid &grid);
bool solvableGrid(const Grid15::Grid::gridArray_t &gridArray);

void save(const std::string &saveFile, const Grid15::Grid &grid);
void load(const std::string &saveFile, Grid15::Grid &grid);

void reIndex(Grid &grid);
}
}
#endif // GRIDHELP_H
