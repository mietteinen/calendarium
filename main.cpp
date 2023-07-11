#include "src/mainwindow/mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/fonts/Karla-SemiBold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/fonts/Inconsolata-Medium.ttf");

    MainWindow w;
    w.show();
    return a.exec();
}
