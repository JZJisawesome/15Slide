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
#ifndef TILEGRID_H
#define TILEGRID_H


#include "Grid15/Grid.h"
#include "GTKSlide/SaveManager.h"

#include <gtkmm.h>

#include <memory>
#include <utility>
#include <cstdint>


namespace GTKSlide
{
    /** \class TileGrid
     *
     * \brief A Gtk::Grid graphical representation of a Grid15::Grid
     *
     * \author John Jekel
     * \date 2018-2018
     */
    class TileGrid : public Gtk::Grid
    {
        public:
            TileGrid(Gtk::Window &parent, std::shared_ptr<Grid15::Grid> &newGridPtr, std::shared_ptr<SaveManager> &saveManagerPtr);
            //virtual ~TileGrid();

            void lableTiles();
            void sensitizeTiles();
            void updateTiles();
        protected:
            //not smart pointer because window will be on stack
            Gtk::Window *parentPtr {};///<A pointer to the parent window to call various dialogs set_transient_for()
            std::shared_ptr<Grid15::Grid> gridPtr {};///<A pointer to the grid to use

            void on_tile_clicked(std::uint8_t coordinates);
            std::unique_ptr<Gtk::Button[]> gridButtons {new Gtk::Button [16]};///<The array of buttons which represent tiles

            void displayWonDialog();
            std::shared_ptr<SaveManager> saveManager {};///<A pointer to a SaveManager for managing autosaving

            std::pair<std::uint8_t, std::uint8_t> singleToTwoD(std::uint8_t coordinates);
            std::uint8_t twoDToSingle(std::uint8_t y, std::uint8_t x);
    };
}

#endif //TILEGRID_H
