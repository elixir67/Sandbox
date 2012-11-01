TEMPLATE  = app
QT       += network webkit

TARGET    = htmleditor
HEADERS   = htmleditor.h highlighter.h \
    htmleditorwidget.h
SOURCES   = htmleditor.cpp main.cpp highlighter.cpp \
    htmleditorwidget.cpp
FORMS     = htmleditor.ui inserthtmldialog.ui \
    htmleditorwidget.ui
RESOURCES = htmleditor.qrc
