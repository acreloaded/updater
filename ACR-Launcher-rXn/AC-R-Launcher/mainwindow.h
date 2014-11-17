#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QStringList>
#include <QIcon>
#include <QMessageBox>
#include <QFileDialog>
#include <QListWidget>

#include "mainworker.h"
#include "serverconsole.h"
#include "modinstalldialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //UI slots
    void on_pushButton_clicked();

    void on_pB_start_client_clicked();

    void on_pB_start_server_clicked();

    void on_pB_upd_acrUpdates_clicked();

    void on_pB_upd_createBackup_clicked();

    void on_pB_upd_installBackup_clicked();

    void on_list_aviable_mods_itemDoubleClicked(QListWidgetItem *item);

    void on_list_installed_mods_itemDoubleClicked(QListWidgetItem *item);

    //Slot for filling mod lists
    void on_ready_to_fill_modlist();

    //Slot for installing mods
    void on_MainWorker_installerReady(QString message);

private:
    Ui::MainWindow *ui;
    MainWorker *mw;
};

#endif // MAINWINDOW_H
