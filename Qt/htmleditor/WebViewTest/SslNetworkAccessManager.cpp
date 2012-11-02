#include "SslNetworkAccessManager.h"

#include "qsslconfiguration.h"

//SslNetworkAccessManager::SslNetworkAccessManager(QObject *parent) :
//    QNetworkAccessManager(parent)
//{
//}
#include <qnetworkreply.h>

SslNetworkAccessManager::SslNetworkAccessManager()
    : QNetworkAccessManager()
{
}

QNetworkReply* SslNetworkAccessManager::createRequest(Operation op, const QNetworkRequest& req, QIODevice* outgoingData)
{
//    QNetworkReply* reply = QNetworkAccessManager::createRequest(op, req, outgoingData);
//    reply->ignoreSslErrors();
//    return reply;
    QSslConfiguration config = req.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1);
    QNetworkRequest request(req);
    request.setSslConfiguration(config);
    return QNetworkAccessManager::createRequest(op, request, outgoingData);
}
