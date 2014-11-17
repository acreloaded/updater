#ifndef DOWNLOADDIALOG_H
#define DOWNLOADDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QString>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

//TODO
#include <QDebug>

namespace Ui {
class DownloadDialog;
}

class DownloadDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DownloadDialog(QString url, QWidget *parent = 0);
    ~DownloadDialog();
    
private slots:
    void on_bBox_Close_clicked(QAbstractButton *button);

    void handleFinished(QNetworkReply *reply);

    void handleProgress(qint64 rec, qint64 total);

signals:
    void downloadReady(QByteArray data);

private:
    Ui::DownloadDialog *ui;
    QNetworkReply *qnreply;
    QNetworkAccessManager *qna;
    QNetworkRequest *qnreq;
    QNetworkReply *result;
    QString text;
};

#endif // DOWNLOADDIALOG_H
