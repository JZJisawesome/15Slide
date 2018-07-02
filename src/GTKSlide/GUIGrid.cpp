//Copyright 2018 John Jekel
//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms
#include "GTKSlide/GUIGrid.h"

#include <gtkmm.h>

#include <iostream>
#include <utility>

#include "Grid15/Grid.h"
#include "Grid15/GridHelp.h"

namespace GTKSlide
{
GUIGrid::GUIGrid() {}

GUIGrid::GUIGrid(std::shared_ptr<Grid15::Grid> &newGridPtr)
{
    setupGrid(newGridPtr);
}

GUIGrid::~GUIGrid() {}

void GUIGrid::setupGrid(std::shared_ptr<Grid15::Grid> &newGridPtr)
{
    gridPtr = newGridPtr;

    for (std::uint_fast32_t j {0}; j < 4; ++j)
    {
        gridButtons[0][j].signal_clicked().connect
        (
            sigc::bind<std::pair<int,int>> (sigc::mem_fun(*this, &GUIGrid::on_tile_clicked), std::make_pair(0, j))
        );

        add(gridButtons[0][j]);
    }

    for (std::uint_fast32_t i {1}; i < 4; ++i)
        for (std::uint_fast32_t j {0}; j < 4; ++j)
        {
            gridButtons[i][j].signal_clicked().connect
            (
                sigc::bind<std::pair<int,int>> (sigc::mem_fun(*this, &GUIGrid::on_tile_clicked), std::make_pair(i, j))
            );

            attach_next_to(gridButtons[i][j], gridButtons[i - 1][j], Gtk::POS_BOTTOM, 1, 1);
        }

    lableTiles();
}

void GUIGrid::on_tile_clicked(std::pair<int,int> &coordinates)
{
    if (gridPtr)
    {
        int &x = coordinates.first;
        int &y = coordinates.second;

        std::cout << std::boolalpha;

        std::cout << "Coordinates (" << x << ", " << y << ") was pressed, with tile number " << static_cast<int> ((*gridPtr).gridArray[x][y]) << ". Valid move: " << Grid15::GridHelp::validMove(x, y, *gridPtr) << std::endl;
        if (Grid15::GridHelp::validMove(x, y, *gridPtr))
        {
            std::cout << "Swapping tile..." << std::endl;
            Grid15::GridHelp::swapTile(x, y, *gridPtr);

            lableTiles();

            std::cout << "Won: " << Grid15::GridHelp::hasWon(*gridPtr) << std::endl;
        }

        std::cout << std::noboolalpha;

        std::cout.flush();
    }
}

void GUIGrid::lableTiles()
{
    if (gridPtr)
    {
        for (std::uint_fast32_t i {0}; i < 4; ++i)
            for (std::uint_fast32_t j {0}; j < 4; ++j)
            {
                if ((*gridPtr).gridArray[i][j] != 0)
                    gridButtons[i][j].set_label(std::to_string((*gridPtr).gridArray[i][j]));
                else
                    gridButtons[i][j].set_label("◉");
            }
    }
}
}
