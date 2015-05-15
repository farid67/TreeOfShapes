/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *FileSelection;
    QLabel *ImageLabel;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QCheckBox *Article_version;
    QCheckBox *modif_version;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QCheckBox *connex4;
    QCheckBox *connex8;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLabel *NodeProportion;
    QSlider *horizontalSlider;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QLabel *InfoLabel;
    QPushButton *ComputeTOS;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(362, 732);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 341, 201));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        FileSelection = new QPushButton(gridLayoutWidget);
        FileSelection->setObjectName(QStringLiteral("FileSelection"));

        gridLayout->addWidget(FileSelection, 0, 0, 1, 1);

        ImageLabel = new QLabel(gridLayoutWidget);
        ImageLabel->setObjectName(QStringLiteral("ImageLabel"));
        ImageLabel->setEnabled(true);
        ImageLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(ImageLabel, 1, 0, 1, 1);

        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(9, 229, 341, 261));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(gridLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        Article_version = new QCheckBox(gridLayoutWidget_2);
        Article_version->setObjectName(QStringLiteral("Article_version"));

        verticalLayout_2->addWidget(Article_version);

        modif_version = new QCheckBox(gridLayoutWidget_2);
        modif_version->setObjectName(QStringLiteral("modif_version"));
        modif_version->setChecked(true);

        verticalLayout_2->addWidget(modif_version);


        gridLayout_2->addLayout(verticalLayout_2, 1, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_3 = new QLabel(gridLayoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_3->addWidget(label_3);

        connex4 = new QCheckBox(gridLayoutWidget_2);
        connex4->setObjectName(QStringLiteral("connex4"));

        verticalLayout_3->addWidget(connex4);

        connex8 = new QCheckBox(gridLayoutWidget_2);
        connex8->setObjectName(QStringLiteral("connex8"));
        connex8->setChecked(true);

        verticalLayout_3->addWidget(connex8);


        gridLayout_2->addLayout(verticalLayout_3, 3, 0, 1, 1);

        label = new QLabel(gridLayoutWidget_2);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(false);
        label->setMaximumSize(QSize(16777215, 20));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_4 = new QLabel(gridLayoutWidget_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setLayoutDirection(Qt::LeftToRight);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_4);

        NodeProportion = new QLabel(gridLayoutWidget_2);
        NodeProportion->setObjectName(QStringLiteral("NodeProportion"));

        horizontalLayout->addWidget(NodeProportion);


        verticalLayout->addLayout(horizontalLayout);

        horizontalSlider = new QSlider(gridLayoutWidget_2);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(100);
        horizontalSlider->setPageStep(5);
        horizontalSlider->setValue(5);
        horizontalSlider->setSliderPosition(5);
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider);


        gridLayout_2->addLayout(verticalLayout, 4, 0, 1, 1);

        gridLayoutWidget_3 = new QWidget(centralwidget);
        gridLayoutWidget_3->setObjectName(QStringLiteral("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(10, 500, 341, 201));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        InfoLabel = new QLabel(gridLayoutWidget_3);
        InfoLabel->setObjectName(QStringLiteral("InfoLabel"));
        InfoLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(InfoLabel, 1, 0, 1, 1);

        ComputeTOS = new QPushButton(gridLayoutWidget_3);
        ComputeTOS->setObjectName(QStringLiteral("ComputeTOS"));
        ComputeTOS->setEnabled(false);

        gridLayout_3->addWidget(ComputeTOS, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        FileSelection->setText(QApplication::translate("MainWindow", "Click to select an Image", 0));
        ImageLabel->setText(QApplication::translate("MainWindow", "Aucune image s\303\251l\303\251ctionn\303\251e pour le moment.", 0));
        label_2->setText(QApplication::translate("MainWindow", "Version :", 0));
        Article_version->setText(QApplication::translate("MainWindow", "Article version (not really stable...)", 0));
        modif_version->setText(QApplication::translate("MainWindow", "Modified version", 0));
        label_3->setText(QApplication::translate("MainWindow", "Connexit\303\251 :", 0));
        connex4->setText(QApplication::translate("MainWindow", "4-connexit\303\251", 0));
        connex8->setText(QApplication::translate("MainWindow", "8-connexit\303\251", 0));
        label->setText(QApplication::translate("MainWindow", "Computation choices :", 0));
        label_4->setText(QApplication::translate("MainWindow", "Minimal node proportion :", 0));
        NodeProportion->setText(QApplication::translate("MainWindow", "5\342\200\260", 0));
        InfoLabel->setText(QApplication::translate("MainWindow", "Evolution des calculs :", 0));
        ComputeTOS->setText(QApplication::translate("MainWindow", "Compute Tree Of Shapes", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
