//Copyright 2018 John Jekel
//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms
#include "GridManager.h"
#include "ProgramStuff.h"

#include <iostream>
#include <istream>
#include <cstdint>

#include <fstream>

#include <string>
#include <array>

#include <algorithm>
#include <random>
#include <chrono>

#include <exception>

//#include <execution>//include when supported finally


/* Constructors */
/// \brief Creates a new grid, initialized to GridManager::GOAL_GRID
GridManager::GridManager()
{
    setGrid(GridManager::GOAL_GRID);//default grid
}

/** \brief Creates a new grid from a file. May throw exceptions from GridManager::load
 *
 * \param saveFile The file to load from
 */
GridManager::GridManager(const std::string &saveFile)
{
    load(saveFile);//may throw exception
}

/** \brief Creates a new grid from an existing grid. May throw exceptions from GridManager::setGrid
 *
 * \param newGrid The grid to copy
 */
GridManager::GridManager(const std::array<std::array<std::uint8_t, 4>, 4> &newGrid)
{
    setGrid(newGrid);//may throw exception
}

/** \brief Creates a new grid from an existing grid. May throw exceptions from GridManager::setGrid
 *
 * \param newGrid The grid to copy
 */
GridManager::GridManager(const std::uint8_t newGrid[4][4])
{
    setGrid(newGrid);//may throw exception
}


/* Tile Movement */
/** \brief Swaps the tile at the given coordinates with the no tile
 *
 * \param tileX The x coordinate
 * \param tileY The y coordinate
 * \throw std::invalid_argument The tile being moved is invalid or not next to the no tile
 */
void GridManager::swapTile(const std::uint8_t tileX, const std::uint8_t tileY)
{
    if (validMove(tileX, tileY))
        swapTile(gameGrid[tileX][tileY]);
    else
        throw std::invalid_argument {"GridManager::swapTile tileX or tileY invalid."};
}

/** \brief Swaps the tile given with the no tile
 *
 * \param tileNum The tile to swap
 * \throw std::invalid_argument The tile being moved is invalid or not next to the no tile
 */
void GridManager::swapTile(const std::uint8_t tileNum)
{
    //original location of tile
    const std::uint8_t tileX {index[tileNum][0]};
    const std::uint8_t tileY {index[tileNum][1]};

    if (validMove(tileX, tileY))
    {
        std::uint8_t oldNoTileX = {index[GridManager::NO_TILE][0]};
        std::uint8_t oldNoTileY = {index[GridManager::NO_TILE][1]};

        gameGrid[index[GridManager::NO_TILE][0]][index[GridManager::NO_TILE][1]] = {tileNum};//moves tile

        //updates location of moved tile in index
        index[tileNum][0] = {oldNoTileX};
        index[tileNum][1] = {oldNoTileY};

        gameGrid[tileX][tileY] = {GridManager::NO_TILE};//moves noTile

        //updates location of noTile in index
        index[GridManager::NO_TILE][0] = {tileX};
        index[GridManager::NO_TILE][1] = {tileY};
    }
    else
        throw std::invalid_argument {"GridManager::swapTile tileNum invalid."};//not a valid move
}

/** \brief Gets the tile at the given coordinates
 *
 * \param tileX The x coordinate
 * \param tileY The y coordinate
 * \return The tile
 * \throw std::out_of_range From std::array::at, if the coordinates are off the grid (see GridManager::X_MAX, GridManager::X_MIN, GridManager::Y_MAX and GridManager::Y_MIN)
 */
std::uint8_t GridManager::getTile(const std::uint8_t tileX, const std::uint8_t tileY)
{
    return gameGrid.at(tileX).at(tileY);//no need to do manual out of bounds checks wiht at()
}

/** \brief Gets the x coordinate of the given tile
 *
 * \param tileNum The tile
 * \return The x coordinate
 * \throw std::invalid_argument If tile if greater than GridManager::TILE_MAX or less than GridManager::TILE_MIN
 */
std::uint8_t GridManager::getX(const std::uint8_t tileNum)
{
    if (tileNum <= GridManager::TILE_MAX)//uint8_t prevents ints < 0
        return index[tileNum][0];
    else
        throw std::invalid_argument {"GridManager::getTile tileNum invalid."};//invalid
}

/** \brief Gets the y coordinate of the given tile
 *
 * \param tileNum The tile
 * \return The y coordinate
 * \throw std::invalid_argument If tile if greater than GridManager::TILE_MAX or less than GridManager::TILE_MIN
 */
std::uint8_t GridManager::getY(const std::uint8_t tileNum)
{
    if (tileNum <= GridManager::TILE_MAX)//uint8_t prevents ints < 0
        return index[tileNum][1];
    else
        throw std::invalid_argument {"GridManager::getTile tileNum invalid."};//invalid
}

/** \brief Checks if the tile movement will be valid
 *
 * \param tileNum The tile to check
 * \return If swapping the tile would work (true) or not (false)
 */
bool GridManager::validMove(const std::int64_t tileNum)
{
    if (tileNum <= GridManager::TILE_MAX && tileNum >= GridManager::TILE_MIN)
        return validMove(index[tileNum][0], index[tileNum][1]);
    else
        return false;

}

/** \brief Checks if the tile movement will be valid
 *
 * \param tileX The tile's x coordinate
 * \param tileY The tile's y coordinate
 * \return If swapping the tile would work (true) or not (false)
 */
bool GridManager::validMove(const std::int64_t tileX, const std::int64_t tileY)
{
    if (tileX > GridManager::X_MAX || tileY > GridManager::Y_MAX)//not out off array boundries
        return false;
    else if (tileX == index[GridManager::NO_TILE][0] && tileY == index[GridManager::NO_TILE][1])//not no tile itself
        return false;
    else if (((tileY == index[GridManager::NO_TILE][1] - 1) || (tileY == index[GridManager::NO_TILE][1] + 1)) && tileX == index[GridManager::NO_TILE][0])//same row, a colum beside
        return true;
    else if (((tileX == index[GridManager::NO_TILE][0] - 1) || (tileX == index[GridManager::NO_TILE][0] + 1)) && tileY == index[GridManager::NO_TILE][1])//same colum, a row beside
        return true;
    else
        return false;
}

/** \brief Checks if the grid is won
 *
 * \return If GridManager::gameGrid is equal to GridManager::GOAL_GRID
 */
bool GridManager::hasWon()
{
    for (std::uint_fast8_t i {0}; i < 4; ++i)
        for (std::uint_fast8_t j {0}; j < 4; ++j)
            if (!(gameGrid[i][j] == GOAL_GRID[i][j]))
                return false;//false if anything is wrong

    return true;//if everything is right return true
}


/* Grid Management */
/** \brief Checks if a grid is valid
 *
 * \param grid The grid to check
 * \return If the grid is valid (true) or not (false)
 */
bool GridManager::validGrid(const std::array<std::array<std::uint8_t, 4>, 4> &grid)
{
    std::array<std::uint8_t, 16> numCount {0};//start at 0//FIX TO SET ALL TO 0

    for (std::uint_fast8_t i {0}; i < 4; ++i)
        for (std::uint_fast8_t j {0}; j < 4; ++j)
        {
            if (grid[i][j] > GridManager::TILE_MAX)
                return false;//too high a number (out of bounds)
        }

    for (std::uint_fast8_t i {0}; i < 4; ++i)
        for (std::uint_fast8_t j {0}; j < 4; ++j)
            numCount[grid[i][j]] += 1;//increment

    for (std::uint_fast8_t i {0}; i < 16; ++i)
    {
        if (!(numCount[i] == 1))
            return false;//exactly 1 of each number
    }

    return true;//everything is good
}

/** \brief Checks if a grid is valid
 *
 * \param grid The grid to check
 * \return If the grid is valid (true) or not (false)
 */
bool GridManager::validGrid(const std::uint8_t grid[4][4])
{
    std::array<std::uint8_t, 16> numCount {0};//start at 0//FIX TO SET ALL TO 0

    for (std::uint_fast8_t i {0}; i < 4; i++)
        for (std::uint_fast8_t j {0}; j < 4; j++)
        {
            if (grid[i][j] > GridManager::TILE_MAX)
                return false;//too high a number (out of bounds)
        }

    for (std::uint_fast8_t i {0}; i < 4; i++)
        for (std::uint_fast8_t j {0}; j < 4; j++)
            numCount[grid[i][j]] += 1;//increment

    for (std::uint_fast8_t i {0}; i < 16; i++)
    {
        if (!(numCount[i] == 1))
            return false;//exactly 1 of each number
    }

    return true;//everything is good
}

/** \brief Sets GridManager::gameGrid
 *
 * \param newGrid The new grid to use
 * \throw std::invalid_argument If the grid is not valid
 */
void GridManager::setGrid(const std::array<std::array<std::uint8_t, 4>, 4> &newGrid)
{
    if (GridManager::validGrid(newGrid))
    {
        std::copy(std::begin(newGrid), std::end(newGrid), std::begin(gameGrid));
        //std::copy(std::execution::par, std::begin(newGrid), std::end(newGrid), std::begin(gameGrid));
        //use std::execution when avaliable

        reIndex();
    }
    else
        throw std::invalid_argument {"GridManager::setGrid newGrid invalid."};
}

/** \brief Sets GridManager::gameGrid
 *
 * \param newGrid The new grid to use
 * \throw std::invalid_argument If the grid is not valid
 */
void GridManager::setGrid(const std::uint8_t newGrid[4][4])
{
    if (GridManager::validGrid(newGrid))
    {
        std::copy(&newGrid[0][0], &newGrid[3][3], &gameGrid[0][0]);
        //std::copy(std::execution::par, &newGrid[0][0], &newGrid[3][3], &gameGrid[0][0]);
        //use std::execution when avaliable

        reIndex();
    }
    else
        throw std::invalid_argument {"GridManager::setGrid newGrid invalid."};
}

/** \brief Creates a new, random and valid grid, which can be assigned using GridManager::setGrid
 *
 * \return A new grid
 */
std::array<std::array<std::uint8_t, 4>, 4> GridManager::generateRandomGrid()
{
    //FIXME no single dimentional intermediary array
    //otherwise only shuffles rows, not inside or in between
    std::array<std::uint8_t, 16> tempGrid
    {
        1,  2,  3,  4,
        5,  6,  7,  8,
        9,  10, 11, 12,
        13, 14, 15, GridManager::NO_TILE
    };

    std::array<std::array<std::uint8_t, 4>, 4> multiDimentional {};

    //thanks to http://www.cplusplus.com/reference/algorithm/shuffle/
    const std::int64_t seed {std::chrono::system_clock::now().time_since_epoch().count()};
    std::shuffle(std::begin(tempGrid), std::end(tempGrid), std::default_random_engine(seed));


    //copy it to the actual game grid (ineficient, but direct shuffle would just move rows, not in between)
    for (std::uint_fast8_t i {0}; i < 4; i++)
        for (std::uint_fast8_t j {0}; j < 4; j++)
            multiDimentional[i][j] = {tempGrid[(i * 4) + j]};


    return multiDimentional;
}

/** \brief Returns a copy of GridManager::gameGrid
 *
 * \return GridManager::gameGrid
 */
std::array<std::array<std::uint8_t, 4>, 4> GridManager::getGrid()
{
    return gameGrid;
}

/// \brief Reads the current gameGrid and updates the index
void GridManager::reIndex()
{
    for (std::uint_fast8_t i {0}; i < 4; i++)
        for (std::uint_fast8_t j {0}; j < 4; j++)
        {
            index[gameGrid[i][j]][0] = {i};
            index[gameGrid[i][j]][1] = {j};
        }
}


/* Grid Storage */
//try to save/load as char and turn to uint8_t for reduced file size (raw bytes)
/** \brief Save the grid to disk
 *
 * \param saveFile The save file
 */
void GridManager::save(const std::string &saveFile)
{
    std::ofstream saveFileStream {};
    saveFileStream.exceptions(saveFileStream.failbit | saveFileStream.badbit);//to throw exceptions if something goes wrong


    saveFileStream.open(saveFile);

    for (std::uint_fast8_t i {0}; i < 4; i++)
        for (std::uint_fast8_t j {0}; j < 4; j++)
            saveFileStream << static_cast<int> (gameGrid[i][j]) << " ";

    saveFileStream.close();
}

/** \brief Load the grid from disk
 *
 * \param saveFile The save file
 */
void GridManager::load(const std::string &saveFile)
{
    std::array<std::array<std::uint8_t, 4>, 4> newGrid {};

    std::ifstream saveFileStream {};
    saveFileStream.exceptions(saveFileStream.failbit | saveFileStream.badbit);//to throw exceptions if something goes wrong

    short temp {};


    saveFileStream.open(saveFile);

    for (std::uint_fast8_t i {0}; i < 4; i++)
        for (std::uint_fast8_t j {0}; j < 4; j++)
        {
            //FIXME extraction right into newGrid even though unsigned char
            saveFileStream >> temp;
            newGrid[i][j] = {static_cast<std::uint8_t> (temp)};
        }

    saveFileStream.close();

    setGrid(newGrid);//throws exception if something goes wrong
}
