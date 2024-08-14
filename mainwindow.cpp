#include "mainwindow.h"

#include <QApplication>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    m_layout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {

}
