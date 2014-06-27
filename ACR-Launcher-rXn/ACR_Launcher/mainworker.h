#ifndef MAINWORKER_H
#define MAINWORKER_H

#include <QString>
#include <QList>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QBuffer>
#include <QObject>

#include <iostream>
using namespace std;

#include <downloader.h>

class MainWorker : public QObject
{
    Q_OBJECT
public:
    MainWorker(QObject *parent = 0);

    //Functions
    void pruneMod(QString badMod);
    void loadData();
    void writeClientExecutable();
    void writeServerExecutable();
    void help(QString cmd);
    void init();
    QStringList installedMods(bool console);
    void runClient();
    void runServer();
    void updateGame();
    void updateAll();
    void updateMe();

    QString getMsg();

private:
    //Data struct for config data
    struct ConfStruct {
        QString version = "0";
        QList<QString> modlist;
        const QString modserverurl = "https://ruler501git.tk/acr/mods";
    };
    ConfStruct *SavedData;
    QStringList argv;
    QTextStream msgOut;
    QString *message;
signals:
    void finished();
    void messageToDisplay();

public slots:
    void downloadFinished();
    void parseCmd(QStringList av);
    void parseCmd(QString av);
};

#endif // MAINWORKER_H
