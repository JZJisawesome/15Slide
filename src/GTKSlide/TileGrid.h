//Copyright 2018 John Jekel
//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms
#ifndef TILEGRID_H
#define TILEGRID_H


#include "Grid15/Grid.h"

#include <gtkmm.h>
#include <memory>
#include <utility>


namespace GTKSlide
{
class TileGrid : public Gtk::Grid
{
public:
    TileGrid();
    TileGrid(std::shared_ptr<Grid15::Grid> &newGridPtr);
    virtual ~TileGrid();

    void setupGrid(std::shared_ptr<Grid15::Grid> &newGridPtr);

    bool saveOnSlide {false};
    std::string saveFile {""};

    void lableTiles();
protected:
    Gtk::Button gridButtons[4][4];

    std::shared_ptr<Grid15::Grid> gridPtr {nullptr};

    void on_tile_clicked(std::pair<int,int> &coordinates);
};
}

#endif //TILEGRID_H
