#ifndef DYNARRY_H
#define DYNARRY_H

#include <vector>
#include <iostream>
#include <QDebug>
#include <math.h>
#include <thread>
typedef unsigned int un;
const float PI=3.141593F;

template <typename T>
class DynArry
{
public:
    DynArry(un sizeX, un sizeY, T fill);
    DynArry();
    T get(un xPos, un yPos);
    void set(un xPos, un yPos, T);
    void fillArr();
    void fillArr(T val);
    void rotate(int centerX, int centerY, float alpha);

    void setCircle(un posX, un posY, un radius, T brush);
    void setLine(un posX, un posY, int sizeX, int sizeY, T brush);
    void setRectangle(un posX, un posY, un sizeX, un sizeY, T brush, T fill);
    un sizeX, sizeY;

private:
    T fill;
    std::vector<T>base;

    //Rotate/////////////////////////////////////////////////////////////
    int round(float a);
    int rotateX(float x, float y, int centerX, int centerY, float fi);
    int rotateY(float x, float y, int centerX, int centerY, float fi);
    float radius(float x, float y, int centerX, int centerY);

    //------------------------------------------------------------------
};


template <typename T>
DynArry<T>::DynArry(un sizeX, un sizeY, T fill)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->fill = fill;
    this->fillArr();
}

template <typename T>
DynArry<T>::DynArry()
{
    this->sizeX = 0;
    this->sizeY = 0;
}

template <typename T>
void DynArry<T>::fillArr()
{
    base.resize(sizeX * sizeY);
    for (un y = 0; y < base.size(); y++) base[y] = fill;
}


template <typename T>
void DynArry<T>::fillArr(T val)
{
     base.resize(sizeX * sizeY);
     int insertPosition = 0;
     for (un y = 0; y < sizeY; y++)
     {
         for (un x = 0; x < sizeX; x++)
         {
             base[insertPosition] = val;
             insertPosition++;
         }
     }
}


template <typename T>
T DynArry<T>::get(un xPos, un yPos)
{
    try {
        if(!(sizeX*yPos + xPos < base.size()))throw 1;
        return base[sizeX*yPos + xPos];
    } catch (int i) {
        std::flush(std::cout<<i<<" Out of area!");
        system("pause");
    }

}


template <typename T>
void DynArry<T>::set(un xPos, un yPos, T value)
{
    if(sizeX*yPos + xPos < base.size())base[sizeX*yPos + xPos] = value;
}

template<typename T>
void DynArry<T>::setCircle(un posX, un posY, un radius, T brush)
{
    int xStart = int(posX+radius);
    int yStart = int(posY);
    //set(xStart,yStart,brush);
    for(un n=0; n<360;n++)
    {

        un x = rotateX(xStart, yStart, posX+radius, posY+radius, n);
        un y = rotateY(xStart, yStart, posX+radius, posY+radius, n);
        if(x>=0 && x<sizeX && y>=0 && y<sizeY)set(x,y,brush);
    }
}



template<typename T>
void DynArry<T>::setLine(un posX, un posY, int sizeX, int sizeY, T brush)
{
    float x=posX;
    float y=posY;
    float dx, dy;

    int length = int(radius(float(sizeX), float(sizeY), 0,0));//int(x), int(y)));

    dx = float(sizeX)/float(length);
    dy = float(sizeY)/float(length);
    for(int n = 0; n<length; n++)
    {
        //std::cout<<"n="<<n<<" x="<<x<<" y="<<y<<"\n";
        if(x>=0 && round(x)<int(this->sizeX) && y>=0 && round(y)<int(this->sizeY))
        set(round(x),round(y),brush);
        x+=dx;
        y+=dy;
    }
}


template<typename T>
void DynArry<T>::setRectangle(un posX, un posY, un sizeX, un sizeY, T brush, T fill)
{
    for(un y=posY; y<posY+sizeY; y++)\
    {
        for(un x=posX; x<posX+sizeX; x++)
        {
            if(x>posX && x<posX+sizeX-1 && y>posY && y<posY+sizeY-1)
            {set(x,y,fill);}
            else
            {set(x,y,brush);}
        }
    }
}



template<typename T>
void DynArry<T>::rotate(int centerX, int centerY, float alpha)
{
    std::vector <T> temp(sizeX*sizeY);
    for(un n=0;n<temp.size();n++) temp[n]=fill;
    for(un y=0;y<sizeY;y++)
    {
        for(un x=0;x<sizeX;x++)
        {
            if (!(base[x+sizeX*y]==fill))
            {
                int x1=rotateX(float(x),float(y), centerX, centerY, alpha);
                int y1=rotateY(float(x),float(y), centerX, centerY, alpha);
                if (x1<int(sizeX) && y1<int(sizeY) && x1>=0 && y1>=0){temp[x1+sizeX*y1]=base[x+sizeX*y];}
            }
        }
    }

    for(un y=0; y<sizeY; y++)
    {
        for (un x=0; x<sizeX; x++){base[x+sizeX*y]=temp[x+sizeX*y];}
    }
}



template<typename T>
int DynArry<T>::round(float a)
{
    a=a*100;
    if(a>=0) a-int(a)>=0.5F ? a=int(a+1) : a=int(a);
    if(a<0) a-int(a)<=-0.5F ? a=int(a-1) : a=int(a);
    return int(a/100);
}



template<typename T>
float DynArry<T>::radius(float x, float y, int centerX, int centerY)
{
    float dx=abs(int(x)-centerX);
    float dy=abs(int(y)-centerY);
    float r=float(sqrt(pow(double(dx),2)+pow(double(dy),2)));
    //std::cout<<r<<"\n";
    return r;
}

template<typename T>
int DynArry<T>::rotateX(float x, float y, int centerX, int centerY, float fi)
{
    float x0 = float(centerX);
    float y0 = float(centerY);
    float alpha = (fi)*PI/180;
    float X = x0 + (x - x0) * float(cos(double(alpha))) - (y - y0) * float(sin(double(alpha)));
    return round(X);
}

template<typename T>
int DynArry<T>::rotateY(float x, float y, int centerX, int centerY, float fi)
{
    float x0 = float(centerX);
    float y0 = float(centerY);
    float alpha = (fi)*PI/180;
    float Y = y0 + (y - y0) * float(cos(double(alpha))) + (x - x0) * float(sin(double(alpha)));
    return round(Y);
}

class Area
{
public:
    int x,y;
    un w;
    un h;
    Area(){}
    Area(int x, int y, un w, un h)
    {
        this->x=x;
        this->y=y;
        this->w=w;
        this->h=h;
    }

};

#endif // DYNARRY_H

