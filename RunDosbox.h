#ifndef RUNDOSBOX_H
#define RUNDOSBOX_H

#include <QDialog>
#include <QString>
#include <QStringList>
#include <QUrl>

#define DOS_EXE_FILES "tb_files/"
#if (defined _WIN32 || defined _WIN64)
    #define DOS_BOX_CMD   "dosbox/dosbox.exe -exit -c \"keyb none 808\" \"%1\""
#else
    #define DOS_BOX_CMD   "dosbox -exit -c \"keyb none 808\" \"%1\""
#endif

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    QString createIconTab();

private slots:
    void on_textBrowser_anchorClicked(const QUrl &arg1);
    void scanForFiles();

private:
    Ui::Dialog *ui;
    QString     m_sBaseFolder;
    QStringList m_slTbFiles;
};

#endif // RUNDOSBOX_H
