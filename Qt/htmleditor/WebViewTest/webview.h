#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebView>

class WebView : public QWebView
{
    Q_OBJECT
public:
    explicit WebView(QWidget *parent = 0);
    
signals:
    
public slots:
    void handleSslErrors(QNetworkReply * reply, const QList<QSslError> & errors);
    void provideAuthentication(QNetworkReply *reply,QAuthenticator *auth);
    void httpReply(QNetworkReply * reply);
    
};

#endif // WEBVIEW_H
