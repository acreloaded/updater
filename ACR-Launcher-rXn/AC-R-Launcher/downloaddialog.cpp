#include "downloaddialog.h"
#include "ui_downloaddialog.h"

//TODO
#include <QDebug>

DownloadDialog::DownloadDialog(QString url, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DownloadDialog)
{
    ui->setupUi(this);
    ui->bBox_Close->setEnabled(false);
    text = "";
    qna = new QNetworkAccessManager(this);
    qnreq = new QNetworkRequest(QUrl("file://home/malte/"));
    qnreply = qna->get(*qnreq);
    connect(qnreply, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleFinished(QNetworkReply*)));
    connect(qnreply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(handleProgress(qint64,qint64)));
    qDebug() << url;
    qDebug() << qnreply->isReadable();
    qDebug() << qnreply->readAll();
    qDebug() << qnreply->error();
}

DownloadDialog::~DownloadDialog()
{
    delete ui;
}

void DownloadDialog::on_bBox_Close_clicked(QAbstractButton *button)
{
    this->close();
}

void DownloadDialog::handleFinished(QNetworkReply *reply) {
    qDebug("test");
    if(!reply->isReadable()) {
        ui->tBrowser_Download->append("Error downloading the file!");
        return;
    }
    emit downloadReady(reply->readAll());
    ui->bBox_Close->setEnabled(true);
    ui->tBrowser_Download->append("Ready! Please press \"Close\"!");
}

void DownloadDialog::handleProgress(qint64 rec, qint64 total) {
    qDebug("progress");
    text += ".";
    qDebug() << qnreply->readAll();
    qDebug() << qnreply->error();
    ui->tBrowser_Download->setText(text);
}
