#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QHBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

#include <QRegularExpression>
#include <QSettings>
#include <QVBoxLayout>

#include <utils/discordrequests.h>

void MainWindow::handleOutput() {
    QString content = m_box->text();
    m_box->setText("");
    switch(state) {
    case Unauthed: {
        if(!content.startsWith("/login ")) {
            addMessage("You are currently unauthenticated, you can't send messages or use commands!", Error);
            return;
        }
        m_box->setEchoMode(QLineEdit::NoEcho);
        m_box->setPlaceholderText("Enter your password");
        state = PendingPassword;
        m_pendingAuthObject.setEmail(content.replace("/login ", ""));
        addMessage(QString("Logging in as <b>%1</b>. Enter your password then press Enter. (you won't be able to see any characters)").arg(content.replace("/login ", "")), System);
        addMessage("If you'd like to cancel at any time, type 'cancel'.", System);
        break;
    }
    case PendingPassword: {
        m_box->setEchoMode(QLineEdit::Normal);
        m_box->setPlaceholderText("Message (or /command)");
        state = Unauthed;
        if(content == "cancel") {
            addMessage("Cancelled.", System);
            break;
        }
        addMessage("Logging in, please be patient...", System);
        QNetworkRequest request = DiscordRequests::buildRequest("auth/login", false, true);
        QJsonObject data;
        data["undelete"] = true;
        data["email"] = m_pendingAuthObject.getEmail();
        data["password"] = content;
        m_netmgr->post(request, QJsonDocument(data).toJson());
        break;
    }
    case PendingOTP: {
        if(content == "cancel") {
            addMessage("Cancelled.", System);
            break;
        }
        static QRegularExpression re("\\d*");
        if(!re.match(content).hasMatch() || content.length() > 8 || content.length() < 6 || content.length() == 7) {
            addMessage("A valid TOTP or backup code is required. Else, enter 'sms' to use SMS auth.", Error);
            break;
        }
        if(content.length() == 6) {
            QNetworkRequest request = DiscordRequests::buildRequest("auth/mfa/totp", false, true);
            QJsonObject data;
            data["ticket"] = m_pendingAuthObject.get2faToken();
            data["code"] = content;
            m_netmgr->post(request, QJsonDocument(data).toJson());
        }
        if(content.length() == 8) {
            QNetworkRequest request = DiscordRequests::buildRequest("auth/mfa/backup", false, true);
            QJsonObject data;
            data["ticket"] = m_pendingAuthObject.get2faToken();
            data["code"] = content;
            m_netmgr->post(request, QJsonDocument(data).toJson());
        }
        break;
    }
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

void MainWindow::handleHttpReply(QNetworkReply* reply) {
    QJsonDocument data = QJsonDocument::fromJson(reply->readAll());
    if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) != 200) {
        addMessage("Something happened", Error);
        return;
    }
    // == AUTH == //
    if(data["mfa"].toBool() && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200) {
        m_pendingAuthObject.set2faToken(data["ticket"].toString());
        m_box->setPlaceholderText("Enter your code (or sms)");
        state = PendingOTP;
        if(data["sms"].toBool()) {
            addMessage("2FA is required to login to this account. Available options: authenticator app, backup codes, SMS auth", System);
            addMessage("To use TOTP/backup auth, simply enter your 6-8 digit code. For SMS auth, type 'sms'.", System);
        }
        else {
            addMessage("2FA is required to login to this account. Available options: authenticator app, backup codes", System);
            addMessage("Enter your 6-8 digit code.", System);
        }
    }
    if(data["token"].toString() != "") {
        QSettings settings;
        settings.setValue("token", data["token"].toString());
        addMessage("Auth done!", System);
    }
    // == END AUTH == //
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QCoreApplication::setOrganizationName("nin0dev");
    QCoreApplication::setApplicationName("txtcord");
    QSettings settings;
    QWidget *centralWidget = new QWidget(this);
    m_layout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);
    // init network manager
    m_pendingAuthObject = PendingAuthObject();
    m_netmgr = new QNetworkAccessManager(this);
    connect(m_netmgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleHttpReply(QNetworkReply*)));
    // init chatlog
    m_chatlog = new QTextEdit();
    m_chatlog->setReadOnly(true);
    m_chatlog->append("<b style=\"color:#00FFE5;\">Welcome to txtcord, the minimal Discord client.</b>");
    if(settings.value("token").isNull()) {
        addMessage("No accounts are saved. Use the /login [email/phone] command to sign in to your Discord account.", System);
    }
    else {
        addMessage("You are logged in, connecting to the Gateway... (soon)", System);
        state = NonConnected;
    }
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
