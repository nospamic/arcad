#ifndef SNAKE_H
#define SNAKE_H

#include "snakeunit.h"


class Snake
{
public:
    Snake(un x, un y, un size, int hp, un id);
    ~Snake();
    std::vector<ArcObject*>body;
    int hp;
    un x, y, size, id;

};

#endif // SNAKE_H
