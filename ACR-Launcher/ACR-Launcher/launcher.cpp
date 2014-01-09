#include "launcher.h"
#include "ui_launcher.h"
#include "options.h"

Launcher::Launcher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Launcher)
{
    ui->setupUi(this);
}

Launcher::~Launcher()
{
    delete ui;
}

void Launcher::on_Options_clicked()
{
    Options options;
    options.setModal(true);
    options.exec();
}
