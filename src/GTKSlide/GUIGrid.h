#ifndef GUIGRID_H
#define GUIGRID_H

#include "Grid15/Grid.h"

#include <gtkmm.h>

#include <memory>

#include <utility>

namespace GTKSlide
{
class GUIGrid : public Gtk::Grid
{
public:
    GUIGrid();
    GUIGrid(std::shared_ptr<Grid15::Grid> &newGridPtr);
    virtual ~GUIGrid();

    void setupGrid(std::shared_ptr<Grid15::Grid> &newGridPtr);
protected:
    Gtk::Button gridButtons[4][4];

    std::shared_ptr<Grid15::Grid> gridPtr {nullptr};

    void on_tile_clicked(std::pair<int,int> &coordinates);

    void lableTiles();
};
}

#endif //GUIGRID_H
