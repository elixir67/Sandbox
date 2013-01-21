#include <QApplication>
#include <QtGui>
#include <QtWebKit>
#include "webview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WebView b;


    b.load(QUrl("http://www.massculturalcouncil.org/facilities/images/Sargent_House.jpg")); // works
    b.show();


    QSize s = b.sizeHint();
    QSizePolicy p = b.sizePolicy();
    b.setBaseSize(100, 100);

    //p.setHorizontalPolicy(QSizePolicy::ShrinkFlag);
    b.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    return a.exec();
}
