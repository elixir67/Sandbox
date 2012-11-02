#include <QApplication>
#include <QtGui>
#include <QtWebKit>
#include "webview.h"

void sslErrors(QNetworkReply* reply,const QList<QSslError> &errors)
{
    // show list of all ssl errors
    foreach (QSslError err, errors)
        qDebug() << "ssl error: " << err;

    reply->ignoreSslErrors();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WebView b;
    b.show();

    b.load(QUrl("https://www.google.com")); // works
    return a.exec();
}
