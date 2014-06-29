#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mw = new MainWorker();
    connect(mw, SIGNAL(messageToDisplay()), SLOT(displayMessage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayMessage() {
    QMessageBox::information(this, "ACR Launcher", mw->getMsg(), QMessageBox::Ok);
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}

void MainWindow::on_pB_start_client_clicked()
{
    mw->parseCmd("runclient");
}

void MainWindow::on_pB_start_server_clicked()
{
    mw->parseCmd("runserver");
}

void MainWindow::on_tW_mainTabs_selected(const QString &arg1)
{
    if(!mw->installedMods(false).isEmpty()) {
        ui->list_installed_mods->setEnabled(true);
        ui->list_installed_mods->clear();
        ui->list_installed_mods->addItems(mw->installedMods(false));
    } else {
       /* foreach (QListWidgetItem *i, ui->list_installed_) {
            ui->list_installed_mods->removeItemWidget(i);
        }*/
        ui->list_installed_mods->setEnabled(false);
        ui->list_installed_mods->addItem("No installed mods...");
    }
}
