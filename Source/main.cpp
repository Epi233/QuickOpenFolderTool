#include <QApplication>
#include "QuickOpenWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QuickOpenWindow w;
    w.show();
    return a.exec();
}
