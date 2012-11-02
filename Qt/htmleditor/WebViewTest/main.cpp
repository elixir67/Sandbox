#include <QApplication>
#include <QtGui>
#include <QtWebKit>
#include "webview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WebView b;
    b.show();

    b.load(QUrl("http://www.baidu.com/img/baidu_sylogo1.gif")); // works
    return a.exec();
}
