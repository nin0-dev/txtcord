#ifndef PENDINGAUTHOBJECT_H
#define PENDINGAUTHOBJECT_H

#include <QString>


class PendingAuthObject
{
public:
    PendingAuthObject(QString email = "", QString password = "", QString token = "");
    QString getEmail();
    QString getPassword();
    QString get2faToken();
    void setEmail(QString email);
    void setPassword(QString password);
    void set2faToken(QString token);
private:
    QString email;
    QString password;
    QString twofaToken;
};

#endif // PENDINGAUTHOBJECT_H
