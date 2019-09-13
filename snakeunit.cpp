#include "snakeunit.h"

SnakeUnit::SnakeUnit(un x, un y, un w, un h, un id, int hp )
{
    dead = false;
    this->posX = x;
    this->posY = y;
    this->sizeX = w;
    this->sizeY = h;
    this->id = id;
    this->hp = hp;
    refresh();
    setView();
    animateTimer = clock();
    animate = char(191);
}

SnakeUnit::~SnakeUnit()
{

}

void SnakeUnit::setView()
{
    view = body;
}

void SnakeUnit::live()
{
    setView();
}

void SnakeUnit::animation()
{

}

void SnakeUnit::death()
{

}

void SnakeUnit::refresh()
{
    Cell empty(Cell::EMPTY, ' ', 0);
    Cell cell(Cell::ENEMY, '*', id);
    body = DynArry<Cell>(sizeX,sizeY,empty);
    body.setCircle(0,0,(sizeX-2)/2,cell);

}
