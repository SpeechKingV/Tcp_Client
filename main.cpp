#include "myclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug();
    MyClient Client("127.0.0.1", 2323);
    qDebug();
    Client.show();
    qDebug();
    return a.exec();
}

