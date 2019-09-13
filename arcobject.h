#ifndef ARCOBJECT_H
#define ARCOBJECT_H

#include <iostream>
#include <windows.h>
#include <string>
#include "dynarry.h"
#include "cell.h"

class ArcObject
{
public:
    virtual ~ArcObject();
    virtual void setView() = 0;
    virtual void live() = 0;
    virtual void animation() = 0;
    virtual void death() = 0;
    bool isInArea(Area area);
    float posX, posY;
    un sizeX, sizeY;
    un id;
    DynArry<Cell>body;
    DynArry<Cell>view;
    Cell piece;
    char animate;
    int animateTimer;
    bool dead;
    int hp;
};

#endif // ARCOBJECT_H
