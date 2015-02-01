#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mw = new MainWorker();
    connect(mw, SIGNAL(modListDownloader_isReady()), this, SLOT(on_ready_to_fill_modlist()));
    ui->statusBar->showMessage(mw->loadData());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}

//Starting the game and the server
void MainWindow::on_pB_start_client_clicked()
{
    ui->statusBar->clearMessage();
    ui->statusBar->showMessage("Game started...");
    QMessageBox::information(this, "ACR Launcher", mw->runClient(), QMessageBox::Ok);
    ui->statusBar->clearMessage();
    ui->statusBar->showMessage("Done");
}

void MainWindow::on_pB_start_server_clicked()
{
    ui->statusBar->clearMessage();
    ui->statusBar->showMessage(mw->runServer(true), 3000);
}

//Mod manager
void MainWindow::on_ready_to_fill_modlist()
{
    ui->list_aviable_mods->setEnabled(true);
    ui->list_aviable_mods->clear();
    ui->list_aviable_mods->addItems(mw->avialableMods());

    ui->list_installed_mods->setEnabled(true);
    ui->list_installed_mods->clear();
    ui->list_installed_mods->addItems(mw->installedMods());
}

void MainWindow::on_list_aviable_mods_itemDoubleClicked(QListWidgetItem *item)
{
    ModInstallDialog md(mw->getModInfos(item->text()));
    md.exec();
    if(md.result() != 0) {
        connect(mw, SIGNAL(installerReady(QString)), this, SLOT(on_MainWorker_installerReady(QString)));
        QMessageBox::information(this, "ACR Launcher", mw->installMod(item->text()), QMessageBox::Ok);

    }
}

void MainWindow::on_MainWorker_installerReady(QString message) {
    QMessageBox::information(this, "ACR Launcher", message, QMessageBox::Ok);
}

void MainWindow::on_list_installed_mods_itemDoubleClicked(QListWidgetItem *item)
{
    if(QMessageBox::question(this, "ACR Launcher", "Do you _really_ want to remove " + item->text() + " ?", QMessageBox::Yes, QMessageBox::No)) {
        //TODO remove mod
    }
}

//Updates
void MainWindow::on_pB_upd_acrUpdates_clicked()
{
    QMessageBox::information(this, "ACR Launcher", "Not yet implemented (WIP!).", QMessageBox::Ok);
    mw->updateGame();
}

void MainWindow::on_pB_upd_createBackup_clicked()
{
    this->setEnabled((false));
    QMessageBox::information(this, "ACR Launcher", mw->createBackup(), QMessageBox::Ok);
    this->setEnabled(true);
}

void MainWindow::on_pB_upd_installBackup_clicked()
{
    QString f = QFileDialog::getOpenFileName(this, "Choose Backup File...", "", "Zipfiles (*.zip)");
    if(!f.isNull()) {
        if(QMessageBox::question(this, "ACR Launcher", "Are you shure you want to install a backup?\nThis could destroy working things...", QMessageBox::Ok, QMessageBox::Abort) == QMessageBox::Ok) {
            mw->installBackup(f);
        }
    } else {
        QMessageBox::information(this, "ACR Launcher", "You must select a file.", QMessageBox::Ok);
    }

}

