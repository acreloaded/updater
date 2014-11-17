#ifndef SERVERCONSOLE_H
#define SERVERCONSOLE_H

#include <QDialog>
#include <QString>
#include <QProcess>

namespace Ui {
class ServerConsole;
}

class ServerConsole : public QDialog
{
    Q_OBJECT
    
public:
    explicit ServerConsole(QWidget *parent = 0, QString val = "");
    ~ServerConsole();
    
private slots:
    void message_to_display();
    void server_closed();

    void on_lineEdit_returnPressed();
    void on_pB_Submit_clicked();

    void on_pB_Close_clicked();

private:
    Ui::ServerConsole *ui;
    QProcess *p;
    bool updown = false;
};

#endif // SERVERCONSOLE_H
