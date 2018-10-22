/* MIT License
 *
 * Copyright (c) 2017-2018 John Jekel
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
#ifndef GRID15_H
#define GRID15_H


#include "Grid15/Grid.h"
#include "Grid15/GridHelp.h"


/** \namespace Grid15
 *
 * \brief Contains the game engine for 15Slide: the Grid and management tools
 *
 * \bug Because of the way initilizer lists are in C++, and because this issue as noticed long into development, Y coordinates are switched with X in GridHelp.
 * \bug This effects the order of function parameters, loops (i == y, j == x ) and arrays in both this library and other 15Slide code that uses it.
 * \bug See https://github.com/JZJisawesome/15Slide/issues/22 for details and possible changes to this.
 *
 * \author John Jekel
 * \date 2017-2018
 */
namespace Grid15 {}

#endif //GRID15_H
