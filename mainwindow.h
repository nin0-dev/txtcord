#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QSlider>
#include <QTextEdit>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QVBoxLayout *m_layout;
    QTextEdit *m_chatlog;
    QLineEdit *m_box;
    QPushButton *m_send;
};
#endif // MAINWINDOW_H
