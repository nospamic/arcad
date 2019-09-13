#include "screen.h"

Screen::Screen()
{
    sizeX = 100;
    sizeY = 40;

    console = FastConsole (sizeX, sizeY);;

}

void Screen::setMap(Map &map, un posX, un posY)
{
    DynArry<char>pic(sizeX, sizeY, ' ');
    for(un y=0; y<sizeY; y++)
    {
        for(un x=0; x<sizeX; x++)
        {
            if(x+posX < map.sizeX && y+posY < map.sizeY) pic.set(x,y,map.space.get(x+posX,y+posY).symbol);
        }
    }
    console.setPicture(pic, 0, 0);

}

void Screen::setObject(DynArry<Cell> &arr)
{
    DynArry<char>pic(arr.sizeX, arr.sizeY, ' ');
    for(un y=0; y<arr.sizeY; y++)
    {
        for(un x=0; x<arr.sizeX; x++)
        {
            un type = arr.get(x,y).type;
            if(!(type==Cell::EMPTY
                 || type==Cell::SENSOR_F
                 || type==Cell::SENSOR_B))pic.set(x,y,arr.get(x,y).symbol);
        }
    }
    console.setPicture(pic, sizeX/2 - pic.sizeX/2, sizeY/2 - pic.sizeY/2);

}

void Screen::setPicture(DynArry<char> &arr,un x,un y)
{
    console.setPicture(arr,x,y);
}

void Screen::show()
{
    console.show();
}

void Screen::text(un x, un y, std::string text)
{
    console.text(x,y,text);
}

void Screen::setMsg(std::string msg)
{
    console.setMsg(msg);
}
