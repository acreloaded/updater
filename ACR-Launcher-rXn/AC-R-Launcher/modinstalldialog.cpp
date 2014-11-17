#include "modinstalldialog.h"
#include "ui_modinstalldialog.h"

ModInstallDialog::ModInstallDialog(QStringList infos, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModInstallDialog)
{
    ui->setupUi(this);
    ui->tBrowser_ModDetails->setFontItalic(true);
    ui->tBrowser_ModDetails->append("Do you want to install the following mod?\n");
    ui->tBrowser_ModDetails->setFontItalic(false);
    ui->tBrowser_ModDetails->setFontUnderline(true);
    ui->tBrowser_ModDetails->append(infos[0]);
    ui->tBrowser_ModDetails->setFontUnderline(false);
    for (int i = 1; i < infos.length(); i++) {
        ui->tBrowser_ModDetails->append(infos[i]);
    }
}

ModInstallDialog::~ModInstallDialog()
{
    delete ui;
}
