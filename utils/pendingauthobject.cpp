#include "pendingauthobject.h"

PendingAuthObject::PendingAuthObject(QString email, QString password, QString token) {
    this->email = email;
    this->password = password;
    this->twofaToken = token;
}

QString PendingAuthObject::getEmail() {
    return email;
}
QString PendingAuthObject::getPassword() {
    return password;
}
QString PendingAuthObject::get2faToken() {
    return twofaToken;
}
void PendingAuthObject::setEmail(QString email) {
    this->email = email;
}
void PendingAuthObject::setPassword(QString password) {
    this->password = password;
}
void PendingAuthObject::set2faToken(QString token) {
    this->twofaToken = token;
}
