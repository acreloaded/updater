#include "downloader.h"

Downloader::Downloader(QString url, QString file) :
    QObject()
{
    //wait for event processing to be ready (I hope ;)
    filename = file;
    request.setUrl(QUrl::fromEncoded(url.toAscii()));
    connect(&nam, SIGNAL(finished(QNetworkReply*)),
                SLOT(ready(QNetworkReply*)));
    nam.get(request);
    qDebug("start");
}

Downloader::~Downloader() { }

void Downloader::ready(QNetworkReply* reply)
{
    qDebug("finish");
    QByteArray result = reply->readAll();
    QFile f(filename);
    f.open(QIODevice::WriteOnly | QIODevice::Truncate);
    f.write(result);
    f.close();
    emit ready();
}



