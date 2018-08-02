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


#include "Grid15/GridHelp.h"

#include <iostream>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <algorithm>
#include <random>
#include <chrono>
#include <exception>
#include <cassert>


namespace Grid15
{
namespace GridHelp
{
/** \brief Swaps the tile at the given coordinates with the no tile of a Grid
 *
 * \param tileX The x coordinate
 * \param tileY The y coordinate
 * \param grid The Grid to change
 * \throw std::invalid_argument The tile being moved is invalid or not next to the no tile
 */
void swapTile(const std::uint8_t tileX, const std::uint8_t tileY, Grid &grid)
{
    if (validMove(tileX, tileY, grid))
        swapTile(grid.gridArray[tileX][tileY], grid);//find tile to swap and pass grid to change
    else
        throw std::invalid_argument {"tileX or tileY invalid!"};
}

/** \brief Swaps the tile given with the no tile of a Grid
 *
 * \param tileNum The tile to swap
 * \param grid The Grid to change
 * \throw std::invalid_argument The tile being moved is invalid, not next to the no tile or the Grid is invalid
 */
void swapTile(const std::uint8_t tileNum, Grid &grid)
{
    //original location of tile
    const std::uint8_t tileX {grid.index[tileNum][0]};
    const std::uint8_t tileY {grid.index[tileNum][1]};

    if (validMove(tileX, tileY, grid))
    {
        std::uint8_t oldNoTileX = {grid.index[Grid::NO_TILE][0]};
        std::uint8_t oldNoTileY = {grid.index[Grid::NO_TILE][1]};

        grid.gridArray[grid.index[Grid::NO_TILE][0]][grid.index[Grid::NO_TILE][1]] = {tileNum};//moves tile

        //updates location of moved tile in index
        grid.index[tileNum][0] = {oldNoTileX};
        grid.index[tileNum][1] = {oldNoTileY};

        grid.gridArray[tileX][tileY] = {Grid::NO_TILE};//moves noTile

        //updates location of noTile in index
        grid.index[Grid::NO_TILE][0] = {tileX};
        grid.index[Grid::NO_TILE][1] = {tileY};
    }
    else
        throw std::invalid_argument {"tileNum or Grid invalid!"};//not a valid move
}

/** \brief Checks if the tile movement will be valid between a tile and the no tile of a Grid
 *
 * \param tileNum The tile to check
 * \param grid The Grid to use
 * \return If swapping the tile would work (true) or not (false)
 * \throw std::invalid_argument If the Grid is not valid
 */
bool validMove(const std::uint8_t tileNum, const Grid& grid)
{
    if (tileNum <= Grid::TILE_MAX/* && tileNum >= Grid::TILE_MIN*/)//unsigned integer is always greater than 0
        return validMove(grid.index[tileNum][0], grid.index[tileNum][1], grid);
    else
        return false;
}

/** \brief Checks if the tile movement will be valid between a tile and the no tile of a Grid
 *
 * \param tileX The tile's x coordinate
 * \param tileY The tile's y coordinate
 * \param grid The Grid to use
 * \return If swapping the tile would work (true) or not (false)
 * \throw std::invalid_argument If the Grid array is not valid
 */
bool validMove(const std::uint8_t tileX, const std::uint8_t tileY, const Grid& grid)
{
    if (validGridArray(grid.gridArray))
    {
        if (tileX > Grid::X_MAX || tileY > Grid::Y_MAX)//not out off array boundries
            return false;
        else if (tileX == grid.index[Grid::NO_TILE][0] && tileY == grid.index[Grid::NO_TILE][1])//not no tile itself
            return false;
        else if (((tileY == grid.index[Grid::NO_TILE][1] - 1) || (tileY == grid.index[Grid::NO_TILE][1] + 1)) && tileX == grid.index[Grid::NO_TILE][0])//same row, a colum beside
            return true;
        else if (((tileX == grid.index[Grid::NO_TILE][0] - 1) || (tileX == grid.index[Grid::NO_TILE][0] + 1)) && tileY == grid.index[Grid::NO_TILE][1])//same colum, a row beside
            return true;
        else
            return false;
    }
    else
        throw std::invalid_argument {"Grid invalid!"};
}

/** \brief Checks if a Grid is won
 *
 * \param grid The Grid to use
 * \return If Grid::grid is equal to Grid::GOAL_GRID
 * \throw std::invalid_argument If the grid array is not valid
 */
bool hasWon(const Grid& grid)
{
    if (validGridArray(grid.gridArray))
    {
        for (std::uint_fast32_t i {0}; i < 4; ++i)
            for (std::uint_fast32_t j {0}; j < 4; ++j)
                if (!(grid.gridArray[i][j] == Grid::GOAL_GRID[i][j]))
                    return false;//false if anything is wrong

        return true;//if everything is right return true
    }
    else
        throw std::invalid_argument {"Grid invalid!"};
}

/** \brief Checks if a grid array is valid
 *
 * \param grid The grid array to check
 * \return If the grid array is valid (true) or not (false)
 */
bool validGridArray(const Grid::gridArray_t &grid)
{
    std::array<std::uint8_t, 16> numCount {0};//start at 0//FIX TO SET ALL TO 0 (MAYBE NEEDED)

    for (std::uint_fast32_t i {0}; i < 4; ++i)
        for (std::uint_fast32_t j {0}; j < 4; ++j)
        {
            if (grid[i][j] > Grid::TILE_MAX)
                return false;//too high a number (out of bounds)
        }


    for (std::uint_fast32_t i {0}; i < 4; ++i)
        for (std::uint_fast32_t j {0}; j < 4; ++j)
            numCount[grid[i][j]] += 1;//increment each number

    for (std::uint_fast32_t i {0}; i < 16; ++i)
    {
        if (!(numCount[i] == 1))
            return false;//exactly 1 of each number
    }

    return true;//everything is good
}

/** \brief Checks if an index is valid.
 *
 * \param grid The grid array to compare the index to
 * \param index The index
 * \return If the index is valid (true) or not (false)
 * \throw std::invalid_argument If the grid (not the index) is invalid
 */
bool validIndex(const Grid::gridArray_t &grid, const Grid::index_t &index)
{
    Grid tempGrid {grid};
    reIndex(tempGrid);//we can rely on this to throw std::invalid_argument

    return std::equal(std::begin(tempGrid.index), std::end(tempGrid.index), std::begin(index));
}

/** \brief Copies a Grid. Better than Grid::setGrid because it ensures validation and also creates a new index
 *
 * \param newGrid The new grid array to use
 * \param grid The Grid to copy to
 * \throw std::invalid_argument If the new Grid is invalid
 */
void safeCopy(const Grid::gridArray_t &newGrid, Grid &grid)
{
    if (validGridArray(newGrid))//fixme rely on validGridArray in index only
    {
        grid.setGridArray(newGrid);

        reIndex(grid);//also checks validGridArray; unavoidable for now but inefficient
    }
    else
        throw std::invalid_argument {"Grid invalid!"};
}

/** \brief Copies a Grid. Better than Grid::setGrid because it ensures validation of the grid array and the index
 *
 * \param newGrid The new grid to
 * \param grid The Grid to copy to
 * \throw std::invalid_argument If the new Grid is invalid
 */
void safeCopy(const Grid &newGrid, Grid &grid)
{
    if (validGrid(newGrid))
    {
        grid.setGrid(newGrid);
    }
    else
        throw std::invalid_argument {"Grid invalid!"};
}

/** \brief Checks if a Grid is valid, including grid array and index
 *
 * \param grid The Grid to check
 * \return If the Grid is valid (true) or not (false)
 */
bool validGrid(const Grid& grid)
{
    return validGridArray(grid.gridArray) && validIndex(grid.gridArray, grid.index);//fixme validGridArray is used in valid index (unnnessary, but again unavoidable)
}

/** \brief Creates a new, random grid array
 *
 * \return A new grid array
 */
Grid15::Grid::gridArray_t generateRandomGridArray()
{
    //FIXME get rid of single dimentional intermediary array
    //we have to have it because otherwise std::shuffle only shuffles rows themselves, not inside or in between
    std::array<std::uint8_t, 16> tempGrid
    {
        1,  2,  3,  4,
        5,  6,  7,  8,
        9,  10, 11, 12,
        13, 14, 15, Grid::NO_TILE
    };

    Grid::gridArray_t multiDimentional {};

    do
    {
        std::shuffle(std::begin(tempGrid), std::end(tempGrid), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));//get a seed and shuffle grid randomly

        //copy it to the actual game grid (ineficient, but direct shuffle would just move rows, not in between)
        for (std::uint_fast32_t i {0}; i < 4; ++i)
            for (std::uint_fast32_t j {0}; j < 4; ++j)
                multiDimentional[i][j] = {tempGrid[(i * 4) + j]};

    } while (!solvableGrid(multiDimentional));

    assert(solvableGrid(multiDimentional));

    return multiDimentional;
}

/** \brief Creates a new, random Grid
 *
 * \return A new Grid
 */
Grid generateRandomGrid()
{
    Grid newGrid {generateRandomGridArray()};//set the new grid array here

    reIndex(newGrid);

    return newGrid;
}

/** \brief Checks if a grid is solvable or not.
 *
 * \param gridArray The grid array to check
 * \return If the grid is solvable or not
 * \throw std::invalid_argument If the new Grid is invalid (index and/or grid array)
 */
bool solvableGrid(const Grid::gridArray_t &gridArray)
{
    //create a new grid with an index
    Grid tempGrid {gridArray};
    reIndex(tempGrid);

    return solvableGrid(tempGrid);
}

/** \brief Checks if a grid is solvable or not.
 *
 * Portions of this function are someone else's code, and may not be bound by 15Slide licences
 * Original title: C++ program to check if a given instance of N * N - 1 puzzle is solvable or not.
 * Accessed and first modified 29 June 2018.
 * Unknown author and code version.
 * Original source can be found at: https://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/
 *
 * \param grid The Grid to check
 * \return If the Grid is  (index and/or grid array) or not
 * \throw std::invalid_argument If the new Grid is invalid (index and/or grid array)
 */
bool solvableGrid(const Grid &grid)
{
    if (validGrid(grid))
    {
        std::array<std::uint8_t, 16> tempGrid;

        for (std::uint_fast32_t i {0}; i < 4; ++i)
            for (std::uint_fast32_t j {0}; j < 4; ++j)
                tempGrid[(i * 4) + j] = {grid.gridArray[i][j]};

        auto inversionCount//https://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/
        {
            [](const std::array<std::uint8_t, 16> arr)
            {
                std::uint_fast32_t currentInversionCount = 0;
                for (std::uint_fast32_t i = 0; i < 4 * 4 - 1; i++)
                {
                    for (std::uint_fast32_t j = i + 1; j < 4 * 4; j++)
                    {
                        //count pairs(i, j) such that i appears
                        //before j, but i > j.
                        if (arr[j] && arr[i] && arr[i] > arr[j])
                            currentInversionCount++;
                    }
                }

                return currentInversionCount;
            }
        };

        auto noTilePositionFromBottom//uses Grid::index instead of the borowed source code; already avaliable and a bit faster
        {
            [](const Grid15::Grid &aGrid)
            {
                return 4 - aGrid.index[Grid15::Grid::NO_TILE][0];
            }
        };

        //https://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/
        if (noTilePositionFromBottom(grid) & 1)//if no tile row is odd
            return !(inversionCount(tempGrid) & 1);
        else//if no tile row is even
            return inversionCount(tempGrid) & 1;
    }
    else
        throw std::invalid_argument {"Grid invalid!"};
}

/** \brief Saves a Grid to disk (not the index)
 *
 * \param saveFile The save file
 * \param grid The Grid to save
 * \throw std::ios_base::failure From std::ifstream; if a file operation goes wrong
 * \throw std::invalid_argument If the Grid is not valid (ignores index)
 */
void save(const std::string& saveFile, const Grid& grid)
{
    if (validGridArray(grid.gridArray))
    {
        std::ofstream saveFileStream {};

        saveFileStream.exceptions(saveFileStream.failbit | saveFileStream.badbit);//to throw exceptions if something goes wrong
        saveFileStream.open(saveFile);

        std::string saveFileBuffer {};//to avoid to many write calls and speed up the process

        for (std::uint_fast32_t i {0}; i < 4; ++i)
            for (std::uint_fast32_t j {0}; j < 4; ++j)
                saveFileBuffer += {std::to_string(static_cast<int> (grid.gridArray[i][j])) + " "};

        saveFileStream << saveFileBuffer;

        saveFileStream.close();
    }
    else
        throw std::invalid_argument {"Grid invalid!"};
}

/** \brief Loads a Grid from disk (and recreates the index)
 *
 * \param saveFile The save file
 * \param grid The Grid to load to
 * \throw std::ios_base::failure From std::ifstream; if a file operation goes wrong
 * \throw std::invalid_argument If the newly loaded Grid is not valid
 */
void load(const std::string& saveFile, Grid& grid)
{
    Grid::gridArray_t newGridArray {};

    std::ifstream saveFileStream {};
    saveFileStream.exceptions(saveFileStream.failbit | saveFileStream.badbit);//to throw exceptions if something goes wrong

    short temp {};

    saveFileStream.open(saveFile);

    for (std::uint_fast32_t i {0}; i < 4; ++i)
        for (std::uint_fast32_t j {0}; j < 4; ++j)
        {
            //FIXME extraction right into newGrid even though unsigned char (extract number not character)
            saveFileStream >> temp;
            newGridArray[i][j] = {static_cast<std::uint8_t> (temp)};
        }

    saveFileStream.close();

    safeCopy(newGridArray, grid);//this reindexes it along the way, and throws an exception if it is invalid
}

/** \brief Reads the grid array of a Grid and updates its index
 *
 * \param grid The Grid to change
 * \throw std::invalid_argument If the grid array is not valid
 */
void reIndex(Grid& grid)
{
    if (validGridArray(grid.gridArray))
    {
        for (std::uint_fast32_t i {0}; i < 4; ++i)
            for (std::uint_fast32_t j {0}; j < 4; ++j)
            {
                grid.index[grid.gridArray[i][j]][0] = {static_cast<std::uint8_t> (i)};
                grid.index[grid.gridArray[i][j]][1] = {static_cast<std::uint8_t> (j)};
            }
    }
    else
        throw std::invalid_argument {"Grid invalid!"};
}
}
}
