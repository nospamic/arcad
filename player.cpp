#include "player.h"



Player::Player(un posX, un posY, un sizeX, un sizeY, int hp)
{
    this->posX = posX;
    this->posY = posY;
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->hp = hp;
    this->speedX = 0;
    this->speedY = 0;
    this->angle = 0;
    blockF = false;
    blockB = false;
    piece = Cell(Cell::EMPTY, ' ', 0);
    POINT p;
    p.x = 600;
    p.y = 100;
    animateTimer = clock();
    animate =  'o';
    SetCursorPos(1,100);
    refresh();



}

Player::Player()
{

}

Player::~Player()
{

}

void Player::refresh()
{
    body = DynArry<Cell> (sizeX, sizeY, piece);
    Cell cell = Cell(Cell::PLAYER,'#',0);
    body.setRectangle(3,3,sizeX-6,sizeY-6,cell,piece);
    cell.symbol = '0';
    body.set(4,2,cell);
    body.set(sizeX-5,2,cell);
    Cell sensorF(Cell::SENSOR_F,'.',0);
    Cell sensorB(Cell::SENSOR_B,'.',0);
    for(un x=3;x<sizeX-3;x++)
    {
        body.set(x,1,sensorF);
        if(x>3 && x<sizeX-4)body.set(x,4,sensorF);
        body.set(x,sizeY-2,sensorB);
    }
    setView();
}

COORD Player::getMouse()
{

            COORD coord;
            POINT p;
            GetCursorPos(&p);
            //std::cout<<p.x<<"  ";
            coord.X = short(p.x);
            coord.Y = short(p.y);
            if (coord.X==0)SetCursorPos(360*3,coord.Y);
            if (coord.X>360*3)SetCursorPos(0,coord.Y);
            return coord;

}


void Player::move()
{
    if (speedY < -0.1F || speedY > 0.1F)
    {

        if(blockF && speedY < 0){
            speedY=(-speedY);
            Beep(300,50);
        }
        blockB?speedY=-0.3F:true;
        float alpha = (float(angle)+90) * 3.1415F / 180;
        posX += float(cos(double(alpha))) * float(speedY);
        posY += float(sin(double(alpha))) * float(speedY);

    }
}

void Player::live()
{
    control();
    animation();
    setView();
    move();
}

void Player::animation()
{
    if (clock()-animateTimer>200)
    {
        animateTimer = clock();
        switch (animate)
        {
        case 'o': animate = '0'; break;
        case '0': animate = 'O'; break;
        case 'O': animate = 'o'; break;
        }
        Cell cell = Cell(Cell::PLAYER,animate,0);
        body.set(4,2,cell);
        body.set(sizeX-5,2,cell);
    }
}

void Player::death()
{

}


void Player::control()
{

    angle = (getMouse().X)/3;
    if(GetKeyState(VK_RIGHT)&0x80){ angle+=3.0F; SetCursorPos(int(angle*3),100);}
    if(GetKeyState(VK_LEFT)&0x80) {angle-=3.0F; SetCursorPos(int(angle*3),100);}
    if(GetKeyState(VK_DOWN)&0x80 && !blockB && speedY<1) {speedY +=0.2F;}
    else if(GetKeyState(VK_UP)&0x80 && !blockF && speedY>-1){speedY -=0.2F;}
    else
    {
        speedY>0?speedY -= 0.1F:true;
        speedY<0?speedY +=0.1F:true;
    }

}




