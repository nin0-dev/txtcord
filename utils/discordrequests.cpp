#include "discordrequests.h"

DiscordRequests::DiscordRequests() {}

QNetworkRequest DiscordRequests::buildRequest(QString endpoint, bool authenticated, bool json) {
    QNetworkRequest request(QUrl("https://discord.com/api/v7/" + endpoint));
    // set superprops/agent on Windows Chrome 122 to avoid raising flags
    request.setRawHeader("X-Super-Properties", "eyJvcyI6IldpbmRvd3MiLCJicm93c2VyIjoiQ2hyb21lIiwiZGV2aWNlIjoiIiwic3lzdGVtX2xvY2FsZSI6ImVuLUdCIiwiYnJvd3Nlcl91c2VyX2FnZW50IjoiTW96aWxsYS81LjAgKFdpbmRvd3MgTlQgMTAuMDsgV2luNjQ7IHg2NCkgQXBwbGVXZWJLaXQvNTM3LjM2IChLSFRNTCwgbGlrZSBHZWNrbykgQ2hyb21lLzEyMi4wLjAuMCBTYWZhcmkvNTM3LjM2IiwiYnJvd3Nlcl92ZXJzaW9uIjoiMTIyLjAuMC4wIiwib3NfdmVyc2lvbiI6IjEwIiwicmVmZXJyZXIiOiIiLCJyZWZlcnJpbmdfZG9tYWluIjoiIiwicmVmZXJyZXJfY3VycmVudCI6IiIsInJlZmVycmluZ19kb21haW5fY3VycmVudCI6IiIsInJlbGVhc2VfY2hhbm5lbCI6InN0YWJsZSIsImNsaWVudF9idWlsZF9udW1iZXIiOjMxODM2MSwiY2xpZW50X2V2ZW50X3NvdXJjZSI6bnVsbH0=");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/122.0.0.0 Safari/537.36");
    // love ripping off headers from my own session :blobcatcozy:
    request.setRawHeader("X-Discord-Locale", "en-GB");
    request.setRawHeader("X-Discord-Timezone", "America/New_York");
    if(json) request.setRawHeader("Content-Type", "application/json");
    return request;
}
