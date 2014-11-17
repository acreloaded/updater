#include "serverconsole.h"
#include "ui_serverconsole.h"

#define CTEXTCOLOR QColor::fromRgb(230, 120, 50)

ServerConsole::ServerConsole(QWidget *parent, QString val) :
    QDialog(parent),
    ui(new Ui::ServerConsole)
{
    ui->setupUi(this);

    ui->pTE_Console->setTextColor(CTEXTCOLOR);
    ui->pTE_Console->setText(val);

    p = new QProcess(this);
    connect(p, SIGNAL(readyRead()), this, SLOT(message_to_display()));
    connect(p, SIGNAL(finished(int)), this, SLOT(server_closed()));

#ifdef Q_OS_WIN32
    p->start("Server.bat");
    p->setProcessChannelMode(QProcess::MergedChannels);
#endif
#ifdef Q_OS_UNIX
    p->start("./Server.sh");
    p->setProcessChannelMode(QProcess::MergedChannels);
#endif

    if(p->error() != QProcess::UnknownError || p->state() == QProcess::NotRunning) {
        ui->pTE_Console->setText(val + "\nAn error ocurred, maybe wrong OS?\n" + "Error: " + p->errorString() + "\nOutput (if any): " + p->readAll() + "\n");
    }

}

ServerConsole::~ServerConsole()
{
    delete ui;
}

void ServerConsole::message_to_display() {
    ui->pTE_Console->setTextColor(QColor::fromRgb(255, 255, 255));
    ui->pTE_Console->append(p->readAll());
}

void ServerConsole::server_closed() {
    ui->pTE_Console->setTextColor(CTEXTCOLOR);
    ui->pTE_Console->append("Server closed!");
}

void ServerConsole::on_lineEdit_returnPressed()
{
    //I dont understand why it works without any code here, but I wont complain :D
}

void ServerConsole::on_pB_Submit_clicked()
{
    ui->pTE_Console->setTextColor(CTEXTCOLOR);
    ui->pTE_Console->append("Sent \"" + ui->lineEdit->text() + "\" to server.");
    p->write(ui->lineEdit->text().toStdString().c_str());
}

void ServerConsole::on_pB_Close_clicked()
{
    p->terminate();
    p->deleteLater();
    this->close();
}
