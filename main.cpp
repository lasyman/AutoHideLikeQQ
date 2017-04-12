#include "autohide.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AutoHide w;
    w.show();

    return a.exec();
}
