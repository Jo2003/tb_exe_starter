#include "RunDosbox.h"
#include "ui_RunDosbox.h"
#include <QTimer>
#include <QApplication>
#include <QMessageBox>
#include <QDir>
#include <QFile>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    m_sBaseFolder = QApplication::applicationDirPath();

    QTimer::singleShot(250, this, SLOT(scanForFiles()));
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::createIconTab()
{
    QFile   fCss(":/text/table.css");
    QString sCss;

    if (fCss.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        sCss = QString("<style type='text/css'>\n%1\n</style>\n").arg(QString(fCss.readAll()));
        fCss.close();
    }

    QString html = QString("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n"
                   "<html xmlns='http://www.w3.org/1999/xhtml'>\n"
                   "<head>\n"
                   "<title>TB EXE Viever</title>\n"
                   "<meta http-equiv='content-type' content='text/html; charset=UTF-8' />\n"
                   "<meta name='qrichtext' content='1' />\n"
                   "%1"
                   "</head>\n"
                   "<body><div class='main'><table width='100%' border='0' cellspacing='1'>\n").arg(sCss);

    for (int i = 0; i < m_slTbFiles.size(); i++)
    {
        if (!(i % 2))
        {
            html += "<tr>";
        }

        html += "<td align='center'>";
        html += QString("<a href='?name=%1'><img src=':/icons/exe' width='64' height='64' alt='icon' /><br />").arg(QString(QUrl::toPercentEncoding(m_slTbFiles.at(i))));
        html += m_slTbFiles.at(i) + "</a></td>";

        if (i % 2)
        {
            html += "</tr>\n";
        }
    }

    if (m_slTbFiles.size() % 2)
    {
        html += "<td>&nbsp;</td></tr>\n";
    }

    html += "</table></div></body></html>";

    ui->textBrowser->setHtml(html);
    return html;
}

void Dialog::on_textBrowser_anchorClicked(const QUrl &arg1)
{
    QString fName = QString("%1/%2%3").arg(m_sBaseFolder).arg(DOS_EXE_FILES).arg(QString(arg1.encodedQueryItemValue("name")));
#if (defined _WIN32 || defined _WIN64)
    QString cmd   = QString("%1/%2").arg(m_sBaseFolder).arg(QString(DOS_BOX_CMD).arg(fName));
#else
    QString cmd   = QString(DOS_BOX_CMD).arg(fName);
#endif

    QProcess::execute(cmd);
}

void Dialog::scanForFiles()
{
    QString     path = QString("%1/%2").arg(m_sBaseFolder).arg(DOS_EXE_FILES);
    QStringList filters;
    QDir        baseDir(path);

    filters << "*.exe" << "*.EXE";
    baseDir.setNameFilters(filters);
    m_slTbFiles = baseDir.entryList();

    createIconTab();
}
