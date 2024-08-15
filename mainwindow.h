#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QNetworkReply>
#include <QProgressBar>
#include <QPushButton>
#include <QSlider>
#include <QTextEdit>
#include <QVBoxLayout>

#include <utils/pendingauthobject.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum MessageType {Normal, System, Error};
    enum AppState {Unauthed, NonConnected, Sane, PendingPassword, PendingOTP};
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void handleOutput();
    void handleHttpReply(QNetworkReply* reply);
private:
    AppState state = Unauthed;
    PendingAuthObject m_pendingAuthObject;
    QVBoxLayout *m_layout;
    QTextEdit *m_chatlog;
    QLineEdit *m_box;
    QPushButton *m_send;
    QNetworkAccessManager *m_netmgr;
    void addMessage(QString content, MainWindow::MessageType type = Normal);
};
#endif // MAINWINDOW_H
