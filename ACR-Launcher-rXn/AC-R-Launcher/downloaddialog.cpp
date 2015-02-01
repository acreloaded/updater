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
    qna = new QNetworkAccessManager(this);
    qnreq = new QNetworkRequest(QUrl(url));
    qnreply = qna->get(*qnreq);
    connect(qna, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleFinished(QNetworkReply*)));
    connect(qnreply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(handleError(QNetworkReply::NetworkError)));
    connect(qnreply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(handleProgress(qint64,qint64)));
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
    if(!reply->isReadable()) {
        ui->tBrowser_Download->append("Error downloading the file!");
        return;
    }
    emit downloadReady(reply->readAll());
    ui->bBox_Close->setEnabled(true);
    ui->tBrowser_Download->append("Ready! Please press \"Close\"!");
}

void DownloadDialog::handleProgress(qint64 rec, qint64 total) {
    //Give a nice feedback
    if(total > 0) {
        QString percent;
        percent.setNum(rec/total *100);
        percent += "%";
        QString ofTotal;
        ofTotal.setNum((int)(total/1024));
        ofTotal.prepend(" of total ");
        ofTotal.append(" KiB");
        ui->tBrowser_Download->setText(percent + ofTotal);
    }
}

void DownloadDialog::handleError(QNetworkReply::NetworkError error) {
    ui->tBrowser_Download->append("Error:" + error);
}
