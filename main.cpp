#include "myclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyClient Client("localhost", 2323);
    Client.show();
    return a.exec();
}
