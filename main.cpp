#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QPushButton>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("txtcord");
    w.setFixedSize(640, 480);

    w.show();
    return a.exec();
}
