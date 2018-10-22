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
#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H


#include "ProgramStuff.h"//just used for autosave

#include <string>


namespace GTKSlide
{
    /** \class SaveManager
     *
     * \brief A simple class to manage save files, save options, and status of saves
     *
     * \author John Jekel
     * \date 2018-2018
     */
    class SaveManager
    {
        public:
            std::string saveFile    {""};                                       ///<The save file
            bool isSaved            {false};                                    ///<Whether the file is saved or not currently
            bool autoSave           {ProgramStuff::AUTOSAVE_ON_SLIDE_DEFAULT};  ///<Whether to autosave or not
    };
}

#endif //SAVEMANAGER_H
