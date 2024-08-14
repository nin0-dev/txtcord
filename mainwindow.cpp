#include "mainwindow.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>

void MainWindow::addMessage(QString content, MainWindow::MessageType type) {
    if(type == Normal) {
        m_chatlog->append(content);
    }
    if(type == System) {
        m_chatlog->append(QString("<span style=\"color:#00FFE5;\">[Sys] %1</p>").arg(content));
    }
    if(type == Error) {
        m_chatlog->append(QString("<span style=\"color:#ff0000;\">Error: %1</p>").arg(content));
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
}

MainWindow::~MainWindow() {

}
