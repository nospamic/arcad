#ifndef FASTCONSOLE_H
#define FASTCONSOLE_H

#include <iostream>
#include <windows.h>
#include <string>
#include "dynarry.h"

typedef unsigned int un;

class FastConsole
{
public:
    FastConsole(un sizeX, un sizeY);
    FastConsole();

    void prepare();
    un sizeX, sizeY;
    void setPicture (DynArry<char>&pic, un Xpos, un Ypos);
    void setRectangle(un posX, un posY, un sizeX, un sizeY, char brush);
    void setCircle(un posX, un posY, un radius, char brush);
    void setLine(un posX, un posY, int sizeX, int sizeY, char brush);
    void show();
    void resetScr();
    void reset();
    void text(un x, un y, std::string text);
    void setMsg(std::string str);



private:
    DynArry<char> screen;
    DynArry<char> buffer;
    void setCursor(un x, un y);
    std::string str;
};

#endif // FASTCONSOLE_H
