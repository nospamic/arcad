#ifndef ARCMOB_H
#define ARCMOB_H
#include "arcobject.h"


class ArcMob : public ArcObject
{
public:
    ArcMob();
    ~ArcMob() override;
    void setView() override;
    void live() override;
    void animation() override;
    void death() override;
    float angle;
    float speedX, speedY;
    bool blockF, blockB;


protected:

};



#endif // ARCMOB_H
