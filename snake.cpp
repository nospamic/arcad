#include "snake.h"

Snake::Snake(un x, un y, un size, int hp, un id)
{
    this->x = x;
    this->y = y;
    this->hp = hp;
    this->size = size;
    this->id = id;
    for (un n = 0; n < size; n++){
        SnakeUnit *unit = new SnakeUnit(x,y,6,6,id,hp);
        body.push_back(unit);
    }
}

Snake::~Snake()
{
    //for(un n=0; n<body.size();n++) delete body[n];
}
