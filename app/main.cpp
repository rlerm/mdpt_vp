#include "mdptvp/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mdptvp::MainWindow w;
    w.show();

    return a.exec();
}
