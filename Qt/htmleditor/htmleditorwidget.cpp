#include "htmleditorwidget.h"
#include "ui_htmleditorwidget.h"
#include <QtGui>
#include <QtWebKit>

#define FORWARD_ACTION(action1, action2) \
    connect(action1, SIGNAL(triggered()), \
            ui->theWebView->pageAction(action2), SLOT(trigger())); \
    connect(ui->theWebView->pageAction(action2), \
            SIGNAL(changed()), SLOT(adjustActions()));


HtmlEditorWidget::HtmlEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HtmlEditorWidget),
    sourceDirty(true),
    m_toolbar(NULL)
{
    ui->setupUi(this);

    connect(ui->actionInsertImage, SIGNAL(triggered()), SLOT(insertImage()));
    connect(ui->actionCreateLink, SIGNAL(triggered()), SLOT(createLink()));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), SLOT(changeTab(int)));
    //connect(ui->actionInsertHtml, SIGNAL(triggered()), SLOT(insertHtml()));

    // these are forward to internal QWebView
//    FORWARD_ACTION(ui->actionEditUndo, QWebPage::Undo);
//    FORWARD_ACTION(ui->actionEditRedo, QWebPage::Redo);
//    FORWARD_ACTION(ui->actionEditCut, QWebPage::Cut);
//    FORWARD_ACTION(ui->actionEditCopy, QWebPage::Copy);
//    FORWARD_ACTION(ui->actionEditPaste, QWebPage::Paste);
    FORWARD_ACTION(ui->actionFormatBold, QWebPage::ToggleBold);
    FORWARD_ACTION(ui->actionFormatItalic, QWebPage::ToggleItalic);
    FORWARD_ACTION(ui->actionFormatUnderline, QWebPage::ToggleUnderline);


    // no page action exists yet for these, so use execCommand trick
    connect(ui->actionFormatStrikethrough, SIGNAL(triggered()), SLOT(formatStrikeThrough()));
    connect(ui->actionFormatAlignLeft, SIGNAL(triggered()), SLOT(formatAlignLeft()));
    connect(ui->actionFormatAlignCenter, SIGNAL(triggered()), SLOT(formatAlignCenter()));
    connect(ui->actionFormatAlignRight, SIGNAL(triggered()), SLOT(formatAlignRight()));
    connect(ui->actionFormatAlignJustify, SIGNAL(triggered()), SLOT(formatAlignJustify()));
    connect(ui->actionFormatDecreaseIndent, SIGNAL(triggered()), SLOT(formatDecreaseIndent()));
    connect(ui->actionFormatIncreaseIndent, SIGNAL(triggered()), SLOT(formatIncreaseIndent()));
    connect(ui->actionFormatNumberedList, SIGNAL(triggered()), SLOT(formatNumberedList()));
    connect(ui->actionFormatBulletedList, SIGNAL(triggered()), SLOT(formatBulletedList()));

//    ui->btnBold->setDefaultAction(ui->actionFormatBold);
//    ui->btnItalic->setDefaultAction(ui->actionFormatItalic);
//    ui->btnUnderline->setDefaultAction(ui->actionFormatUnderline);
//    ui->btnStrikethrough->setDefaultAction(ui->actionFormatStrikethrough);
//    ui->btnAlignLeft->setDefaultAction(ui->actionFormatAlignLeft);
//    ui->btnAlignCenter->setDefaultAction(ui->actionFormatAlignCenter);
//    ui->btnAlignRight->setDefaultAction(ui->actionFormatAlignRight);
//    ui->btnAlignJustify->setDefaultAction(ui->actionFormatAlignJustify);

//    ui->btnDecIndent->setDefaultAction(ui->actionFormatDecreaseIndent);
//    ui->btnIncIndent->setDefaultAction(ui->actionFormatIncreaseIndent);
//    ui->btnNumberedList->setDefaultAction(ui->actionFormatNumberedList);
//    ui->btnInsertImg->setDefaultAction(ui->actionInsertImage);
//    ui->btnCreateLink->setDefaultAction(ui->actionCreateLink);

    m_toolbar = new QToolBar();
    m_toolbar->setMovable(false);
    m_toolbar->addAction(ui->actionFormatBold);
    m_toolbar->addAction(ui->actionFormatItalic);
    m_toolbar->addAction(ui->actionFormatUnderline);
    m_toolbar->addAction(ui->actionFormatStrikethrough);
    m_toolbar->addAction(ui->actionFormatAlignLeft);
    m_toolbar->addAction(ui->actionFormatAlignCenter);

    m_toolbar->addAction(ui->actionFormatAlignRight);
    m_toolbar->addAction(ui->actionFormatAlignJustify);
    m_toolbar->addAction(ui->actionFormatDecreaseIndent);
    m_toolbar->addAction(ui->actionFormatIncreaseIndent);

    m_toolbar->addAction(ui->actionFormatNumberedList);
    m_toolbar->addAction(ui->actionFormatBulletedList);
    m_toolbar->addAction(ui->actionInsertImage);
    m_toolbar->addAction(ui->actionCreateLink);
    ui->verticalLayout->insertWidget(0, m_toolbar);

    connect(ui->theWebView, SIGNAL(linkClicked(QUrl)), SLOT(openLink(QUrl)));

    // necessary to sync our actions
    connect(ui->theWebView->page(), SIGNAL(selectionChanged()), SLOT(adjustActions()));

    connect(ui->theWebView->page(), SIGNAL(contentsChanged()), SLOT(adjustSource()));

    ui->theWebView->setContent("<script src='H:/devbox/html/test.js'></script><body contenteditable='true' oninput='listener()'><textarea rows='10 cols='50'' id='log'></textarea></body>", "text/html");
    ui->theWebView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    ui->theWebView->page()->setContentEditable(true);

    QStringList wordList;
    wordList << "alpha" << "omega" << "omicron" << "zeta";

    QCompleter *completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
//    ui->theWebView->setcom

    ui->theWebView->setFocus();

    setCurrentFileName(QString());

    adjustActions();
    adjustSource();
}

void HtmlEditorWidget::setCurrentFileName(const QString &fileName)
{
    QString shownName;
    if (fileName.isEmpty())
        shownName = "untitled";
    else
        shownName = QFileInfo(fileName).fileName();

    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("HTML Editor")));
    setWindowModified(false);}

HtmlEditorWidget::~HtmlEditorWidget()
{
    delete ui;
}

void HtmlEditorWidget::formatStrikeThrough()
{
    execCommand("strikeThrough");
}

void HtmlEditorWidget::formatAlignLeft()
{
    execCommand("justifyLeft");
}

void HtmlEditorWidget::formatAlignCenter()
{
    execCommand("justifyCenter");
}

void HtmlEditorWidget::formatAlignRight()
{
    execCommand("justifyRight");
}

void HtmlEditorWidget::formatAlignJustify()
{
    execCommand("justifyFull");
}

void HtmlEditorWidget::formatIncreaseIndent()
{
    execCommand("indent");
}

void HtmlEditorWidget::formatDecreaseIndent()
{
    execCommand("outdent");
}

void HtmlEditorWidget::formatNumberedList()
{
    execCommand("insertOrderedList");
}

void HtmlEditorWidget::formatBulletedList()
{
    execCommand("insertUnorderedList");
}

void HtmlEditorWidget::formatFontName()
{
    QStringList families = QFontDatabase().families();
    bool ok = false;
    QString family = QInputDialog::getItem(this, tr("Font"), tr("Select font:"),
                                           families, 0, false, &ok);

    if (ok)
        execCommand("fontName", family);
}

void HtmlEditorWidget::formatFontSize()
{
    QStringList sizes;
    sizes << "xx-small";
    sizes << "x-small";
    sizes << "small";
    sizes << "medium";
    sizes << "large";
    sizes << "x-large";
    sizes << "xx-large";

    bool ok = false;
    QString size = QInputDialog::getItem(this, tr("Font Size"), tr("Select font size:"),
                                        sizes, sizes.indexOf("medium"), false, &ok);

    if (ok)
        execCommand("fontSize", QString::number(sizes.indexOf(size)));
}

void HtmlEditorWidget::formatTextColor()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if (color.isValid())
        execCommand("foreColor", color.name());
}


void HtmlEditorWidget::formatBackgroundColor()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    if (color.isValid())
        execCommand("hiliteColor", color.name());
}

// shamelessly copied from Qt Demo Browser
static QUrl guessUrlFromString(const QString &string)
{
    QString urlStr = string.trimmed();
    QRegExp test(QLatin1String("^[a-zA-Z]+\\:.*"));

    // Check if it looks like a qualified URL. Try parsing it and see.
    bool hasSchema = test.exactMatch(urlStr);
    if (hasSchema) {
        QUrl url(urlStr, QUrl::TolerantMode);
        if (url.isValid())
            return url;
    }

    // Might be a file.
    if (QFile::exists(urlStr))
        return QUrl::fromLocalFile(urlStr);

    // Might be a shorturl - try to detect the schema.
    if (!hasSchema) {
        int dotIndex = urlStr.indexOf(QLatin1Char('.'));
        if (dotIndex != -1) {
            QString prefix = urlStr.left(dotIndex).toLower();
            QString schema = (prefix == QLatin1String("ftp")) ? prefix : QLatin1String("http");
            QUrl url(schema + QLatin1String("://") + urlStr, QUrl::TolerantMode);
            if (url.isValid())
                return url;
        }
    }

    // Fall back to QUrl's own tolerant parser.
    return QUrl(string, QUrl::TolerantMode);
}


void HtmlEditorWidget::insertImage()
{
//    QString filters;
//    filters += tr("Common Graphics (*.png *.jpg *.jpeg *.gif);;");
//    filters += tr("Portable Network Graphics (PNG) (*.png);;");
//    filters += tr("JPEG (*.jpg *.jpeg);;");
//    filters += tr("Graphics Interchange Format (*.gif);;");
//    filters += tr("All Files (*)");

//    QString fn = QFileDialog::getOpenFileName(this, tr("Open image..."),
//                 QString(), filters);
//    if (fn.isEmpty())
//        return;
//    if (!QFile::exists(fn))
//        return;

//    QUrl url = QUrl::fromLocalFile(fn);
//    execCommand("insertImage", url.toString());

    QString link = QInputDialog::getText(this, tr("Insert website image"),
                                         "Enter URL");
    if(!link.isEmpty()){
        QUrl url = guessUrlFromString(link);
        if(url.isValid())
            execCommand("insertImage", url.toString());
    }
}


void HtmlEditorWidget::createLink()
{
    QString link = QInputDialog::getText(this, tr("Create link"),
                                         "Enter URL");
    if (!link.isEmpty()) {
        QUrl url = guessUrlFromString(link);
        if (url.isValid())
            execCommand("createLink", url.toString());
    }
}

void HtmlEditorWidget::openLink(const QUrl &url)
{
    QString msg = QString(tr("Open %1 ?")).arg(url.toString());
    if (QMessageBox::question(this, tr("Open link"), msg,
                              QMessageBox::Open | QMessageBox::Cancel) ==
            QMessageBox::Open)
        QDesktopServices::openUrl(url);
}


void HtmlEditorWidget::execCommand(const QString &cmd)
{
    QWebFrame *frame = ui->theWebView->page()->mainFrame();
    QString js = QString("document.execCommand(\"%1\", false, null)").arg(cmd);
    frame->evaluateJavaScript(js);
}

void HtmlEditorWidget::execCommand(const QString &cmd, const QString &arg)
{
    QWebFrame *frame = ui->theWebView->page()->mainFrame();
    QString js = QString("document.execCommand(\"%1\", false, \"%2\")").arg(cmd).arg(arg);
    frame->evaluateJavaScript(js);
}

bool HtmlEditorWidget::queryCommandState(const QString &cmd)
{
    QWebFrame *frame = ui->theWebView->page()->mainFrame();
    QString js = QString("document.queryCommandState(\"%1\", false, null)").arg(cmd);
    QVariant result = frame->evaluateJavaScript(js);
    return result.toString().simplified().toLower() == "true";
}

#define FOLLOW_ENABLE(a1, a2) a1->setEnabled(ui->theWebView->pageAction(a2)->isEnabled())
#define FOLLOW_CHECK(a1, a2) a1->setChecked(ui->theWebView->pageAction(a2)->isChecked())

void HtmlEditorWidget::adjustActions()
{
//    FOLLOW_ENABLE(ui->actionEditUndo, QWebPage::Undo);
//    FOLLOW_ENABLE(ui->actionEditRedo, QWebPage::Redo);
//    FOLLOW_ENABLE(ui->actionEditCut, QWebPage::Cut);
//    FOLLOW_ENABLE(ui->actionEditCopy, QWebPage::Copy);
//    FOLLOW_ENABLE(ui->actionEditPaste, QWebPage::Paste);
    FOLLOW_CHECK(ui->actionFormatBold, QWebPage::ToggleBold);
    FOLLOW_CHECK(ui->actionFormatItalic, QWebPage::ToggleItalic);
    FOLLOW_CHECK(ui->actionFormatUnderline, QWebPage::ToggleUnderline);

    ui->actionFormatStrikethrough->setChecked(queryCommandState("strikeThrough"));
    ui->actionFormatNumberedList->setChecked(queryCommandState("insertOrderedList"));
    ui->actionFormatBulletedList->setChecked(queryCommandState("insertUnorderedList"));
}

void HtmlEditorWidget::adjustSource()
{
    setWindowModified(true);
    sourceDirty = true;

    if (ui->tabWidget->currentIndex() == 1)
        changeTab(1);
}
void HtmlEditorWidget::changeTab(int index)
{
    if (sourceDirty && (index == 1)) {
        QString content = ui->theWebView->page()->mainFrame()->toHtml();
        ui->thePlainTextEdit->setPlainText(content);
        sourceDirty = false;
    }
}
