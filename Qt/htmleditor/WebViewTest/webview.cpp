#include "webview.h"
#include <QNetworkReply>
#include <QtDebug>
#include <QSslError>
#include <QAuthenticator>
#include "SslNetworkAccessManager.h"

WebView::WebView(QWidget *parent) :
    QWebView(parent)
{
    //load(QUrl("http://www.baidu.com/img/baidu_sylogo1.gif"));
    SslNetworkAccessManager * pAM = new SslNetworkAccessManager();
    page()->setNetworkAccessManager(pAM);
    //QNetworkAccessManager * pAM = page()->networkAccessManager();

    connect(pAM,
            SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)),
            this,
            SLOT(handleSslErrors(QNetworkReply*,QList<QSslError>)));

    connect(pAM, SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)),
            SLOT(provideAuthentication(QNetworkReply *,QAuthenticator *)));
    connect(pAM, SIGNAL(finished(QNetworkReply*)),  SLOT(httpReply(QNetworkReply*)));
    // connect(pAM, SIGNAL(sslErrors(QNetworkReply*,const QList<QSslError>&)),SLOT(sslErrors(QNetworkReply*,const QList<QSslError>&)));

}

void WebView::handleSslErrors(QNetworkReply* reply, const QList<QSslError> &errors)
{
    qDebug() << "handleSslErrors: ";
    foreach (QSslError e, errors)
    {
        qDebug() << "ssl error: " << e;
    }

    reply->ignoreSslErrors();
}

void WebView::provideAuthentication(QNetworkReply *reply,QAuthenticator *auth)
{
    qDebug() << reply->readAll(); // this is just to see what we received
    auth->setUser("ads\\lind");
    auth->setPassword("Furture673");
}

void WebView::httpReply(QNetworkReply *reply)
{
    QUrl url = reply->url();
    QNetworkReply::NetworkError error = reply->error();
    QString strError = reply->errorString();
    if (!reply->error()) {
        qDebug() << reply->readAll();
        QByteArray bytes(reply->readAll());
        QString string(bytes);
        //ui->webView->setHtml(string);
        //QByteArray response(reply->readAll());
    }
    else {
        qDebug() << "//////////////////////////\n";
        qDebug() << "//////////////////////////\n";
        qDebug() << "////HTTP GET Error" << reply->error() <<"\n";
        qDebug() << "////HTTP GET Error" << reply->errorString() <<"\n";
    }

    reply->deleteLater();
}
