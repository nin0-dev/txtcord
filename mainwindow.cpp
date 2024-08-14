#include "mainwindow.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>

void MainWindow::handleOutput() {
    QString content = m_box->text();
    m_box->setText("");
    switch(state) {
    case Unauthed:
        if(!content.startsWith("/login ")) {
            addMessage("You are currently unauthenticated, you can't send messages or use commands!", Error);
            return;
        }
        m_box->setEchoMode(QLineEdit::NoEcho);
        m_box->setPlaceholderText("Enter your password");
        state = PendingPassword;
        addMessage(QString("Logging in as <b>%1</b>. Enter your password then press Enter. (you won't be able to see any characters)").arg(content.replace("/login ", "")), System);
        break;
    case Unauthed:
        if(!content.startsWith("/login ")) {
            addMessage("You are currently unauthenticated, you can't send messages or use commands!", Error);
            return;
        }
        m_box->setEchoMode(QLineEdit::NoEcho);
    m_box->setPlaceholderText("Enter your password");
    state = PendingPassword;
    addMessage(QString("Logging in as <b>%1</b>. Enter your password then press Enter. (you won't be able to see any characters)").arg(content.replace("/login ", "")), System);
    break;
}
}

void MainWindow::addMessage(QString content, MainWindow::MessageType type) {
    if(type == Normal) {
        m_chatlog->append(content);
    }
    if(type == System) {
        m_chatlog->append(QString("<span style=\"color:#00FFE5;\">[Sys] %1</p>").arg(content));
    }
    if(type == Error) {
        m_chatlog->append(QString("<span style=\"color:#ff2222;\">Error: %1</p>").arg(content));
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    m_layout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);
    // init chatlog
    m_chatlog = new QTextEdit();
    m_chatlog->setReadOnly(true);
    m_chatlog->append("<b style=\"color:#00FFE5;\">Welcome to txtcord, the minimal Discord client.</b>");
    addMessage("No accounts are saved. Use the /login [email/phone] command to sign in to your Discord account.", System);
    m_layout->addWidget(m_chatlog);
    // init chatbox
    QWidget *chatboxWidget = new QWidget();
    QHBoxLayout *chatboxLayout = new QHBoxLayout();
    m_box = new QLineEdit();
    m_box->setPlaceholderText("Message (or /command)");
    chatboxLayout->addWidget(m_box);
    m_send = new QPushButton();
    m_send->setText("Send");
    chatboxLayout->addWidget(m_send);
    chatboxWidget->setLayout(chatboxLayout);
    m_layout->addWidget(chatboxWidget);
    connect(m_box, SIGNAL(returnPressed()), this, SLOT(handleOutput()));
}

MainWindow::~MainWindow() {

}
