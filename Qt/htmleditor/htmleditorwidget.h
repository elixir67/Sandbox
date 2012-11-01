#ifndef HTMLEDITORWIDGET_H
#define HTMLEDITORWIDGET_H

#include <QWidget>
#include <QToolBar>

namespace Ui {
class HtmlEditorWidget;
}
class QUrl;

class HtmlEditorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit HtmlEditorWidget(QWidget *parent = 0);
    ~HtmlEditorWidget();
    
    void execCommand(const QString&);
    void setCurrentFileName(const QString &fileName);
    void execCommand(const QString &cmd, const QString &arg);
    bool queryCommandState(const QString&);


private slots:
    void formatStrikeThrough();
    void formatAlignLeft();
    void formatAlignCenter();
    void formatAlignRight();
    void formatAlignJustify();
    void formatIncreaseIndent();
    void formatDecreaseIndent();
    void formatNumberedList();
    void formatBulletedList();
    void formatFontName();
    void formatFontSize();
    void formatTextColor();
    void formatBackgroundColor();
    void insertImage();
    void createLink();

    void openLink(const QUrl&);

    void changeTab(int);
    void adjustActions();
    void adjustSource();

private:
    Ui::HtmlEditorWidget *ui;

     bool sourceDirty;
     QToolBar *m_toolbar;
};

#endif // HTMLEDITORWIDGET_H
