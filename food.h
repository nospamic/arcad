#ifndef FOOD_H
#define FOOD_H

#include "arcobject.h"

class Food : public ArcObject
{
public:
    void setView() override;
    void live() override;
    void animation() override;
    void refresh();
    Food(un posX, un posY, un sizeX, un sizeY, un id);
    ~Food() override;
    void death() override;

};
#endif // FOOD_H
