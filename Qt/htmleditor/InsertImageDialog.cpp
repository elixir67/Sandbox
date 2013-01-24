#include "InsertImageDialog.h"
#include "ui_insertimagedialog.h"
#include <QUrl>
#include <QDesktopServices>
#include <QFileDialog>

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

static bool isValidImageURL(const QString & string)
{
    QString urlStr = string.trimmed();
    QRegExp rx(QLatin1String("^[a-zA-Z].*(.png|.jpg|.jpeg|.jpe|.gif|.ico|.bmp|.tif|.tiff|.dib)$"),
                 Qt::CaseInsensitive);
    return rx.exactMatch(urlStr);
}

InsertImageDialog::InsertImageDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::InsertImageDialog)
{
    m_ui->setupUi(this);

    setWindowFlags( windowFlags() & (~Qt::WindowContextHelpButtonHint) );

    m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    m_ui->urlTextInput->setFocus();

    connect(m_ui->browserBtn, SIGNAL(clicked()), SLOT(GoToBrowser()));
    connect(m_ui->urlTextInput, SIGNAL(textEdited(const QString&)), SLOT(URLEdit(const QString&)));
}

InsertImageDialog::~InsertImageDialog()
{
    delete m_ui;
}

void InsertImageDialog::GoToBrowser()
{
    //if(!QDesktopServices::openUrl(QUrl(m_url)))
        //QDesktopServices::openUrl(QUrl("www.google.com"));
    QDesktopServices::openUrl(QUrl(m_url));
}

void InsertImageDialog::ChooseLocalImage()
{
    QString filters;
    filters += tr("Common Graphics (*.png *.jpg *.jpeg *.gif);;");
    filters += tr("Portable Network Graphics (PNG) (*.png);;");
    filters += tr("JPEG (*.jpg *.jpeg);;");
    filters += tr("Graphics Interchange Format (*.gif);;");
    filters += tr("All Files (*)");

    QString fn = QFileDialog::getOpenFileName(this, tr("Open image..."),
                 QString(), filters);
    if (fn.isEmpty())
        return;
    if (!QFile::exists(fn))
        return;

    QUrl url = QUrl::fromLocalFile(fn);
    m_url = url.toString();
    ActivateOKButton();
}

void InsertImageDialog::URLEdit(const QString& text)
{
    //    if(!link.isEmpty()){
    //        QUrl url = guessUrlFromString(link);
    //        if(url.isValid())
    //            execCommand("insertImage", url.toString());
    //    }
    // m_url = guessUrlFromString('text').toString();
    m_url = text;
    ActivateOKButton();
}

void InsertImageDialog::ActivateOKButton()
{
    QString urlStr = m_url.trimmed();
//    QUrl url(urlStr);
//    m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(url.isValid());
    // QRegExp rx(QLatin1String("^((http|https|ftp):\/\/|www\\.).*\\.(png|jpg|jpeg|jpe|gif|ico|bmp|tif|tiff|dib)$"),
               // /
//    QRegExp rx(QLatin1String("^((http|https|ftp|file):\/\/|www\\.)(\/|\/([\w#!:.?+=&%@!\-\/]))?"),
//                 Qt::CaseInsensitive);
    QRegExp rx(QLatin1String("^(ht|f)tp(s?)\:\/\/[0-9a-zA-Z]([-.\w]*[0-9a-zA-Z])*(:(0-9)*)*(\/?)([a-zA-Z0-9\-\.\?\,\'\/\\\+&amp;%\$#_]*)?$"),
               Qt::CaseInsensitive);
    m_ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(rx.exactMatch(urlStr));
     //QUrl(urlStr).isValid()
}

QString InsertImageDialog::url() const
{
   return m_url;
}



