#ifndef ENEMY_H
#define ENEMY_H

#include "arcmob.h"

class Enemy : public ArcMob
{
public:
    Enemy(un sizeX, un sizeY, un posX, un posY);
    ~Enemy() override;
    void live()override;
    void animation() override;
    void setView() override;
    void death() override;
    void control();
    void refresh();
};

#endif // ENEMY_H
