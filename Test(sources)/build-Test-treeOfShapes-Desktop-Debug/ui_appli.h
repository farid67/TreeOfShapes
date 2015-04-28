/********************************************************************************
** Form generated from reading UI file 'appli.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLI_H
#define UI_APPLI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Appli
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Appli)
    {
        if (Appli->objectName().isEmpty())
            Appli->setObjectName(QStringLiteral("Appli"));
        Appli->resize(191, 171);
        centralwidget = new QWidget(Appli);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(100, 40, 80, 22));
        Appli->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Appli);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 191, 20));
        Appli->setMenuBar(menubar);
        statusbar = new QStatusBar(Appli);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Appli->setStatusBar(statusbar);

        retranslateUi(Appli);

        QMetaObject::connectSlotsByName(Appli);
    } // setupUi

    void retranslateUi(QMainWindow *Appli)
    {
        Appli->setWindowTitle(QApplication::translate("Appli", "MainWindow", 0));
        pushButton->setText(QApplication::translate("Appli", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class Appli: public Ui_Appli {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLI_H
