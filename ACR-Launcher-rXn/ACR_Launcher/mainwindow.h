#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QStringList>
#include <QIcon>

#include "mainworker.h"

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

    void on_pushButton_clicked();

    void on_pB_start_client_clicked();

    void on_pB_start_server_clicked();

    //No GUI Events:
    void displayMessage();

    void on_tW_mainTabs_selected(const QString &arg1);

private:
    Ui::MainWindow *ui;
    MainWorker *mw;
};

#endif // MAINWINDOW_H
