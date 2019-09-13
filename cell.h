#ifndef CELL_H
#define CELL_H
typedef unsigned int un;

class Cell
{
public:
    enum CELLTYPE {BORDER, PLAYER, BILDING, ENEMY, EMPTY, SENSOR_F, SENSOR_B, DECOR, FOOD};
    Cell(un type, char symbol, un id);
    Cell();
    bool operator ==(const Cell &other);

    char symbol;
    un color;
    un bgColor;
    un type;
    un id;

};

#endif // CELL_H
