/********************************************************************************
** Form generated from reading UI file 'launcher.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAUNCHER_H
#define UI_LAUNCHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Launcher
{
public:
    QWidget *centralWidget;
    QLabel *image;
    QPushButton *Play;
    QPushButton *Server;
    QPushButton *Options;
    QLabel *news;

    void setupUi(QMainWindow *Launcher)
    {
        if (Launcher->objectName().isEmpty())
            Launcher->setObjectName(QStringLiteral("Launcher"));
        Launcher->resize(323, 250);
        Launcher->setMinimumSize(QSize(323, 250));
        Launcher->setMaximumSize(QSize(323, 250));
        Launcher->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Images/Resources/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Launcher->setWindowIcon(icon);
        centralWidget = new QWidget(Launcher);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        image = new QLabel(centralWidget);
        image->setObjectName(QStringLiteral("image"));
        image->setGeometry(QRect(20, 20, 281, 111));
        image->setPixmap(QPixmap(QString::fromUtf8(":/Images/Resources/logo.png")));
        image->setScaledContents(true);
        Play = new QPushButton(centralWidget);
        Play->setObjectName(QStringLiteral("Play"));
        Play->setGeometry(QRect(10, 160, 101, 41));
        Server = new QPushButton(centralWidget);
        Server->setObjectName(QStringLiteral("Server"));
        Server->setGeometry(QRect(210, 160, 101, 41));
        Options = new QPushButton(centralWidget);
        Options->setObjectName(QStringLiteral("Options"));
        Options->setGeometry(QRect(140, 170, 51, 21));
        news = new QLabel(centralWidget);
        news->setObjectName(QStringLiteral("news"));
        news->setGeometry(QRect(10, 210, 46, 13));
        Launcher->setCentralWidget(centralWidget);

        retranslateUi(Launcher);

        QMetaObject::connectSlotsByName(Launcher);
    } // setupUi

    void retranslateUi(QMainWindow *Launcher)
    {
        Launcher->setWindowTitle(QApplication::translate("Launcher", "ACR Launcher", 0));
        image->setText(QString());
        Play->setText(QApplication::translate("Launcher", "Play Game!", 0));
        Server->setText(QApplication::translate("Launcher", "Start Server!", 0));
        Options->setText(QApplication::translate("Launcher", "Options", 0));
        news->setText(QApplication::translate("Launcher", "News:", 0));
    } // retranslateUi

};

namespace Ui {
    class Launcher: public Ui_Launcher {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAUNCHER_H
