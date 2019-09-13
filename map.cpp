#include "map.h"

Map::Map()
{

}

Map::Map(un gameSizeX, un gameSizeY)
{
    borderWidth = 3;
    gameSizeX > gameSizeY ? padding = gameSizeX/2 : padding = gameSizeY/2;
    this->gameSizeX = gameSizeX;
    this->gameSizeY = gameSizeY;
    sizeX = gameSizeX + (padding * 2) + (borderWidth * 2);
    sizeY = gameSizeY + (padding * 2) + (borderWidth * 2);
    empty = Cell(Cell::EMPTY, ' ', 0);
    border = Cell(Cell::BORDER, char(177) , 0);
    space = DynArry<Cell>(sizeX, sizeY, empty);
    startX = sizeX/2;
    startY = sizeY - padding - borderWidth - 50;

}


DynArry<Cell> Map::getBorder()
{
    DynArry<Cell>borderLine(gameSizeX+borderWidth*2, gameSizeY+borderWidth*2, empty);
    for(un n=0;n<borderWidth;n++)
    {
        borderLine.setRectangle(n, n, gameSizeX+(borderWidth*2)-(n*2), gameSizeY+(borderWidth*2)-(n*2),border,empty);
        //borderLine.setRectangle(n, n, gameSizeX-5, gameSizeY-5, border, empty);
    }

    Cell point(Cell::DECOR,'.',0);
    for(un y=borderWidth; y<gameSizeY;y+=10)
    {
        for(un x=borderWidth; x<gameSizeX;x+=14)
        {
            borderLine.set(x,y,point);
        }
    }
    return borderLine;
}


void Map::clear(Area area)
{

    for(un y=area.y; y<area.y+area.h;y++)
    {
        for(un x=area.x; x<area.x+area.w;x++)
        {
            if (space.get(x,y).type!=Cell::BORDER && space.get(x,y).type != Cell::EMPTY)
                space.set(x,y,empty);
        }
    }
}


void Map::setObject(DynArry<Cell> &arr, un xPos, un yPos, Area area)
{
    un xStart;
    un xEnd;
    un yStart;
    un yEnd;
    (area.x<xPos) ?  xStart=xPos :  xStart = area.x;
    (area.x+area.w > xPos+arr.sizeX) ? xEnd=xPos+arr.sizeX : xEnd=area.x+area.w;
    (area.y<yPos) ?  yStart=yPos :  yStart = area.y;
    (area.y+area.h > yPos+arr.sizeY) ? yEnd=yPos+arr.sizeY : yEnd=area.y+area.h;

    for(un y=yStart;y<yEnd;y++)
    {
        for(un x=xStart; x<xEnd;x++)
        {
            un type = arr.get(x-xPos,y-yPos).type;
            if(type !=Cell::EMPTY && type != Cell::SENSOR_F && type != Cell::SENSOR_B ) space.set(x,y,arr.get(x-xPos,y-yPos));
        }
    }
}


DynArry<Cell> Map::getFragment(Area area)
{
   DynArry<Cell>fragment(area.w, area.h, empty);
   for (un y=0; y<area.h; y++)
   {
       for(un x=0; x<area.w; x++)fragment.set(x,y,space.get(x+un(area.x), y+un(area.y)));
   }
   return fragment;
}


DynArry<Cell> Map::getMaze()
{
    DynArry<Cell>borderLine = getBorder();

    //borderLine.setRectangle(borderWidth,borderWidth, borderLine.sizeX-2*borderWidth, borderLine.sizeY-2*borderWidth,empty,empty);
    borderLine.setRectangle(borderWidth,borderWidth, gameSizeX, gameSizeY, empty, empty);
    un lineWidth = 15;
    un x = borderLine.sizeX/2 - lineWidth/2;
    un y = borderLine.sizeY - borderWidth - 50;
    Cell bild = Cell(Cell::BILDING,char(177),0);
    Cell food = Cell(Cell::FOOD, '+', 0);
    enum WAY{UP, DOWN, RIGHT, LEFT};
    srand( un(time(nullptr)) );
    for(un n=0;n<sizeX;n++)
    {
        int way = rand() % 4;
        int distance = rand()%40+10;
        if(way==UP)
        {
            for(int i=0;i<distance;i++)
            {
                //std::flush(std::cout<<x<<" "<<y<<" "<<way<<"\n");
                if(borderLine.get(x,y-1).type == Cell::BORDER)break;
                borderLine.setRectangle(x,y,lineWidth,lineWidth,empty,empty);
                borderLine.set(x,y,bild);
                y--;
            }
            if(distance>42)borderLine.set(x+lineWidth/2,y+lineWidth+1,food);
        }
        if(way==DOWN)
        {
            for(int i=0;i<distance;i++)
            {
                //std::flush(std::cout<<x<<" "<<y<<" "<<way<<"\n");
                if(borderLine.get(x,y+lineWidth+1).type == Cell::BORDER)break;
                borderLine.setRectangle(x,y,lineWidth,lineWidth,empty,empty);
                borderLine.set(x,y,bild);
                y++;
            }
            //borderLine.set(x+lineWidth/2,y-1,food);
        }
        if(way==RIGHT)
        {
            for(int i=0;i<distance;i++)
            {
                //std::flush(std::cout<<x<<" "<<y<<" "<<way<<"\n");
                if(borderLine.get(x+lineWidth+1,y).type == Cell::BORDER)break;
                borderLine.setRectangle(x,y,lineWidth,lineWidth,empty,empty);
                borderLine.set(x,y,bild);
                x++;
            }
            //borderLine.set(x-1,y+lineWidth/2,food);
        }
        if(way==LEFT)
        {
            for(int i=0;i<distance;i++)
            {
                //std::flush(std::cout<<x<<" "<<y<<" "<<way<<"\n");
                if(borderLine.get(x-1,y).type == Cell::BORDER)break;
                borderLine.setRectangle(x,y,lineWidth,lineWidth,empty,empty);
                borderLine.set(x,y,bild);
                x--;
            }
            //borderLine.set(x+lineWidth+1,y+lineWidth/2,food);
        }

    }

    borderLine.setRectangle(borderLine.sizeX/2-lineWidth/2, borderLine.sizeY-borderWidth-50,20,20,empty,empty);//start rect

    for(un y=0;y<borderLine.sizeY;y++)
    {
        for(un x=0;x<borderLine.sizeX;x++)
        {
            if (borderLine.get(x,y).type == Cell::FOOD)
            {
                space.set(x+padding,y+padding,food);
                borderLine.set(x,y,empty);
            }
        }
    }
    Cell point(Cell::DECOR,'.',0);
    for(un y=borderWidth; y<gameSizeY;y+=10)
    {
        for(un x=borderWidth; x<gameSizeX;x+=14)
        {
            if(borderLine.get(x,y)==empty)borderLine.set(x,y,point);
        }
    }
    return borderLine;
}


