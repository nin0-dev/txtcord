#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QVBoxLayout *m_layout;
    QPushButton *m_button;
    QProgressBar *m_bar;
    QSlider *m_slider;
};
#endif // MAINWINDOW_H
