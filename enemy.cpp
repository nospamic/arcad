#include "enemy.h"

Enemy::Enemy(un sizeX, un sizeY, un posX, un posY)
{
    this->posX = posX;
    this->posY = posY;
    this->sizeX = sizeX;
    this->sizeY = sizeY;
}

Enemy::~Enemy()
{

}

void Enemy::live()
{

}

void Enemy::animation()
{

}

void Enemy::setView()
{

}

void Enemy::death()
{

}

void Enemy::control()
{

}

void Enemy::refresh()
{
    Cell sensorF(Cell::SENSOR_F,'.',0);
    Cell sensorB(Cell::SENSOR_B,'.',0);
}
