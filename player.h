#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <windows.h>
#include <string>
#include "dynarry.h"
#include "arcmob.h"
#include "map.h"
#include "cell.h"


class Player : public ArcMob
{
public:
    Player(un posX, un posY, un sizeX, un sizeY, int hp);
    Player();
    ~Player() override;

    void move();
    void live()override;
    void animation() override;
    void death() override;
    void control();
    void refresh();
    COORD getMouse();
private:



};

#endif // PLAYER_H
