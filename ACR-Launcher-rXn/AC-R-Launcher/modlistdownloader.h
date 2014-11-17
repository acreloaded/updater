#ifndef MODLISTDOWNLOADER_H
#define MODLISTDOWNLOADER_H

#include <QString>
#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

//ugly
#include "configdata.h"

class ModListDownloader : public QObject
{
    Q_OBJECT

public:
    ModListDownloader(QString url, ConfigData *data);
    QNetworkReply *getData();
public slots:
    void parseModList(QNetworkReply *list);
signals:
    void isReady();
private:
    QNetworkAccessManager *qna;
    QNetworkRequest *qnreq;
    QString file;
    ConfigData *data;
    QNetworkReply *result;
};


#endif // MODLISTDOWNLOADER_H
