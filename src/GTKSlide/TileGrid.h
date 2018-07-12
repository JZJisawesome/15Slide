//Copyright 2018 John Jekel
//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms
#ifndef TILEGRID_H
#define TILEGRID_H


#include "Grid15/Grid.h"
#include "GTKSlide/SaveManager.h"

#include <gtkmm.h>
#include <memory>
#include <utility>


namespace GTKSlide
{
class TileGrid : public Gtk::Grid
{
public:
    TileGrid(Gtk::Window &parent, std::shared_ptr<Grid15::Grid> &newGridPtr, std::shared_ptr<SaveManager> &saveManagerPtr);
    virtual ~TileGrid();

    void lableTiles();
    void sensitizeTiles();
    void updateTiles();
protected:
    Gtk::Window *parentPtr {};//not smart pointer because window will be on stack
    std::shared_ptr<Grid15::Grid> gridPtr {};

    void on_tile_clicked(std::pair<int,int> &coordinates);
    Gtk::Button gridButtons[4][4];
    //std::unique_ptr<Gtk::Button>//this array takes up lots of space

    void displayWonDialog();
    std::shared_ptr<SaveManager> saveManager {};

    void setupGrid(std::shared_ptr<Grid15::Grid> &newGridPtr);
};
}

#endif //TILEGRID_H
