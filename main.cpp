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
    w.setMinimumSize(400, 300);

    w.show();
    return a.exec();
}
