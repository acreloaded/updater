#include "options.h"
#include "ui_options.h"

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowFlags(Qt::CustomizeWindowHint);
}

Options::~Options()
{
    delete ui;
}

void Options::on_Close_clicked()
{
   Options::hide();
}
