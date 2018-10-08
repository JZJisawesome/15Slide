//Copyright 2018 John Jekel
//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms
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
#ifndef GRID15_H
#define GRID15_H


#include "Grid15/Grid.h"
#include "Grid15/GridHelp.h"
#include "Grid15/GridManager.h"//DON'T USE


/** \namespace Grid15
 *
 * \brief Contains the game engine for 15Slide: the Grid and management tools
 *
 * Because of the way initilizer lists are in C++, and because this issue as noticed long into development, Y coordinates are typically switched with X in the parameters of functions, and in arrays.
 * See https://github.com/JZJisawesome/15Slide/issues/22 for details and possible changes to this.
 *
 * \author John Jekel
 * \date 2018-2018
 */
namespace Grid15 {}

#endif //GRID15_H
