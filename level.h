#ifndef LEVEL_H
#define LEVEL_H

#include <conio.h>
#include <thread>
#include <ctime>
#include "fastconsole.h"
#include "dynarry.h"
#include "screen.h"
#include "map.h"
#include "player.h"
#include "food.h"
#include "textbutor.h"
#include "snake.h"


class Level
{
public:
    Level();
    ~Level();
    void play();
    void setObjToMap(ArcObject *obj);
private:
    std::vector<ArcObject*>food;
    void FoodCreate();
    void setFood();
    void snakeCreate();
    std::vector<Snake>snake;
    Area area;
    void setArea();

    Screen screen;
    Map map;
    Player player;
    void move();
    Cell feelFront();
    Cell feelBack();
    void feel();
    Map getMiniMap();
    void keyCtrl();
    bool rotate;
    void info();
    int infoTimer;
    int lifeTimer;
    bool lifeControl();
    void playerDeath();

    DynArry<char>arrow;
    std::string hpInfo;

    Snake *s;
};

#endif // LEVEL_H
