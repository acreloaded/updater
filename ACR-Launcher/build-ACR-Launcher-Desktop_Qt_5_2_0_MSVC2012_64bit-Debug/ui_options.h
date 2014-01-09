/********************************************************************************
** Form generated from reading UI file 'options.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONS_H
#define UI_OPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Options
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *Close;

    void setupUi(QDialog *Options)
    {
        if (Options->objectName().isEmpty())
            Options->setObjectName(QStringLiteral("Options"));
        Options->resize(199, 351);
        Options->setMinimumSize(QSize(199, 351));
        Options->setMaximumSize(QSize(199, 351));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Images/Resources/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Options->setWindowIcon(icon);
        pushButton = new QPushButton(Options);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 10, 181, 31));
        pushButton_2 = new QPushButton(Options);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 50, 181, 31));
        pushButton_3 = new QPushButton(Options);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(10, 90, 181, 31));
        pushButton_4 = new QPushButton(Options);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(10, 130, 181, 31));
        pushButton_5 = new QPushButton(Options);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(10, 180, 181, 31));
        pushButton_6 = new QPushButton(Options);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(10, 220, 181, 31));
        pushButton_7 = new QPushButton(Options);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(10, 260, 181, 31));
        Close = new QPushButton(Options);
        Close->setObjectName(QStringLiteral("Close"));
        Close->setGeometry(QRect(10, 310, 181, 31));

        retranslateUi(Options);

        QMetaObject::connectSlotsByName(Options);
    } // setupUi

    void retranslateUi(QDialog *Options)
    {
        Options->setWindowTitle(QApplication::translate("Options", "Options", 0));
        pushButton->setText(QApplication::translate("Options", "Clear Server Logs", 0));
        pushButton_2->setText(QApplication::translate("Options", "Reset Data", 0));
        pushButton_3->setText(QApplication::translate("Options", "Reinstall", 0));
        pushButton_4->setText(QApplication::translate("Options", "Uninstall", 0));
        pushButton_5->setText(QApplication::translate("Options", "About", 0));
        pushButton_6->setText(QApplication::translate("Options", "Changes", 0));
        pushButton_7->setText(QApplication::translate("Options", "Change Nickname", 0));
        Close->setText(QApplication::translate("Options", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class Options: public Ui_Options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONS_H
