#include "DeliverNow.h"
#include <QtWidgets/QApplication>
#include "BigApp.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BigApp A{};
    return a.exec();
}
