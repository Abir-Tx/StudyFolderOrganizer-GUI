#include "sfo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sfo w;
    w.show();
    return a.exec();
}
