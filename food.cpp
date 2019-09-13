#include "food.h"


void Food::setView()
{
   view = body;
}


void Food::live()
{
    if(sizeX<40){
        if(dead==true){
            sizeX--;
            sizeY--;
            refresh();
        }
        else {
           animation();
        }
        setView();
    }
}


void Food::animation()
{
    if (clock()-animateTimer>200)
    {
        animateTimer = clock();
        switch (animate)
        {
        case char(191): animate = char(217); break;
        case char(217): animate = char(192); break;
        case char(192): animate = char(218); break;
        case char(218): animate = char(191); break;
        }
        Cell cell = Cell(Cell::FOOD,animate,id);

        body.set(sizeX/2,sizeY/2,cell);

    }
}

void Food::refresh()
{
    body.fillArr();
    Cell cell(Cell::FOOD, char(219), id);
    if(dead)cell.type = Cell::DECOR;
    body.setCircle(0, 0, sizeX/2, cell);
}

Food::Food(un posX, un posY, un sizeX, un sizeY, un id)
{
    dead = false;
    this->posX = posX;
    this->posY = posY;
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->id = id;
    Cell cell(Cell::FOOD, char(219), id);
    Cell empty(Cell::EMPTY, ' ', id);
    body = DynArry<Cell>(sizeX,sizeY,empty);
    body.setCircle(0, 0, sizeX/2, cell);
    view = body;
    animateTimer = clock();
    animate = char(191);
}

Food::~Food()
{

}

void Food::death()
{
    dead = true;
}
