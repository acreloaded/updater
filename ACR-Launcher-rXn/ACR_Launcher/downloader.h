#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QString>
#include <QTimer>

class Downloader : public QObject
{
    Q_OBJECT
public:
    Downloader(QString url, QString file);
    void waitForFinished();
    virtual ~Downloader();
private slots:
    void ready(QNetworkReply* pReply);
signals:
    void ready();
private:
    QNetworkAccessManager nam;
    QString filename;
    QNetworkRequest request;
};


#endif // DOWNLOADER_H
