#ifndef SNAKEUNIT_H
#define SNAKEUNIT_H

#include "arcobject.h"

class SnakeUnit : public ArcObject

{
public:
    SnakeUnit(un x, un y, un w, un h, un id, int hp);
    ~SnakeUnit() override;
    void setView() override;
    void live() override;
    void animation() override;
    void death() override;
    void refresh();
};

#endif // SNAKEUNIT_H
