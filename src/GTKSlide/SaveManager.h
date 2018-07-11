//Copyright 2018 John Jekel
//See https://github.com/JZJisawesome/15Slide/blob/master/LICENSE for the terms
#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <string>

namespace GTKSlide
{
class SaveManager
{
public:
    std::string saveFile {""};
    bool autoSave {true};
    bool isSaved {false};
};
}

#endif //SAVEMANAGER_H
