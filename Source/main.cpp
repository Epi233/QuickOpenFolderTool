#include <QApplication>
#include "HK4EQuickOpenWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HK4EQuickOpenWindow w;
    w.show();
    return a.exec();
}
