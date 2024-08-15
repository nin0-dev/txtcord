#ifndef DISCORDREQUESTS_H
#define DISCORDREQUESTS_H

#include <QNetworkRequest>
class DiscordRequests
{
public:
    DiscordRequests();
    static QNetworkRequest buildRequest(QString endpoint, bool authenticated = true, bool json = false);
};

#endif // DISCORDREQUESTS_H
