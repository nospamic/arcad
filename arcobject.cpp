#include "arcobject.h"






ArcObject::~ArcObject()
{

}

bool ArcObject::isInArea(Area area)
{
    if (sizeX<area.w && sizeY<area.h)
    {
        return (posX>area.x && posX<unsigned(area.x)+area.w && posY>area.y && posY<unsigned(area.y)+area.h);
    }
    else return true;
}
