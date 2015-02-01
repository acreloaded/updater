#ifndef MAINWORKER_H
#define MAINWORKER_H

#include <QObject>
#include <QString>
#include <QList>
#include <QStringList>
#include <QTextStream>
#include <QProcess>
#include <QObject>
#include <QDateTime>
#include <QTemporaryFile>

//TODO
#include <QDebug>

#include <QNetworkReply>

#include <iostream>
using namespace std;

#include "modlistdownloader.h"
#include "configdata.h"
#include "downloaddialog.h"
#include "serverconsole.h"

class MainWorker : public QObject
{
    Q_OBJECT

public:
    MainWorker();

    //Function for parsing command line stuff (OLD)
    void parseCmd(QStringList av);

    QStringList installedMods();
    QStringList avialableMods();

    void pruneMod(QString badMod);

    //Load stuff at startup (mods etc)
    QString loadData();

    void help(QString cmd);
    void init();

    //Starting ACR
    QString writeClientExecutable();
    QString writeServerExecutable();
    QString runClient();
    QString runServer(bool new_window);

    void updateGame();
    void updateAll();
    void updateMe();

    //Backup
    QString createBackup();
    QString installBackup(QString file);

    //Installing and showing mods
    QStringList getModInfos(QString mod);
    QString installMod(QString mod);

    QString getMsg();

public slots:
    void on_modListDownloader_isReady();

    void on_DownloadDialog_downloadReady(QByteArray data);

signals:
    void modListDownloader_isReady();
    void installerReady(QString msg);

private:
    ModListDownloader *d;
    ConfigData *SavedData;
    QStringList argv;
    QTextStream msgOut;
    QString *message;
};

#endif // MAINWORKER_H
