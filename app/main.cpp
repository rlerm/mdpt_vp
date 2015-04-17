#include "mdptvp/mainwindow.h"

#include <QtCore/QCoreApplication>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("MDPT");
    QCoreApplication::setApplicationName("MDPT Video Player");

    QApplication a(argc, argv);
    mdptvp::MainWindow w;
    w.show();

    return a.exec();
}
