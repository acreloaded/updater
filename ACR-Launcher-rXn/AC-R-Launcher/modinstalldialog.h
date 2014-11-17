#ifndef MODINSTALLDIALOG_H
#define MODINSTALLDIALOG_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class ModInstallDialog;
}

class ModInstallDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModInstallDialog(QStringList infos, QWidget *parent = 0);
    ~ModInstallDialog();

private:
    Ui::ModInstallDialog *ui;
};

#endif // MODINSTALLDIALOG_H
