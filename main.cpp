#include "spheregui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SphereGui w;
    w.show();

    return a.exec();
}
