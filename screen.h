#ifndef SCREEN_H
#define SCREEN_H

#include <windows.h>
#include "map.h"
#include "fastconsole.h"
#include "dynarry.h"
#include "arcobject.h"
#include "arcmob.h"
#include "player.h"

class Screen
{
public:
    Screen();

    un sizeX, sizeY;
    void setMap(Map &map, un posX, un posY);
    void setObject(DynArry<Cell> &arr);
    void setPicture(DynArry<char>&arr, un x, un y);
    void show();
    void text(un x, un y, std::string text);
    void setMsg(std::string msg);
private:
    FastConsole console;

};

#endif // SCREEN_H
