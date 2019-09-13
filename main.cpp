#include <QCoreApplication>
#include "level.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    while(true){
        Level level1;
        level1.play();
    }




    return a.exec();
}
