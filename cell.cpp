#include "cell.h"

Cell::Cell(un type, char symbol, un id)
{
    this->type=type;
    this->symbol=symbol;
    this->id=id;
}

Cell::Cell()
{

}

bool Cell::operator ==(const Cell &other)
{
    return (type==other.type&&symbol==other.symbol&&id==other.id);
}
