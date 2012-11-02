#ifndef SSLNETWORKACCESSMANAGER_H
#define SSLNETWORKACCESSMANAGER_H

#include <QNetworkAccessManager>

class SslNetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT
public:
    SslNetworkAccessManager();

protected:
    QNetworkReply* createRequest(Operation op, const QNetworkRequest & req, QIODevice * outgoingData = 0);
};

#endif // SSLNETWORKACCESSMANAGER_H
