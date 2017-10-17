/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoadFile;
    QWidget *centralWidget;
    QToolButton *toolButton;
    QPushButton *pushButton;
    QSpinBox *spinRules;
    QPushButton *pushButton_2;
    QLabel *label;
    QDoubleSpinBox *doubleDa;
    QDoubleSpinBox *doubleDb;
    QDoubleSpinBox *doubleDc;
    QSpinBox *spinWeights;
    QLabel *label_2;
    QDoubleSpinBox *doubleDa_2;
    QCustomPlot *widget;
    QSpinBox *spinShowWeight;
    QSpinBox *spinBox;
    QLabel *label_3;
    QSpinBox *spinPercentage;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QLabel *label_5;
    QSpinBox *positOfClass;
    QSpinBox *redundant;
    QLabel *label_6;
    QLabel *label_7;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1014, 710);
        actionLoadFile = new QAction(MainWindow);
        actionLoadFile->setObjectName(QStringLiteral("actionLoadFile"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        toolButton = new QToolButton(centralWidget);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(40, 530, 231, 20));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(280, 530, 93, 21));
        spinRules = new QSpinBox(centralWidget);
        spinRules->setObjectName(QStringLiteral("spinRules"));
        spinRules->setGeometry(QRect(400, 470, 51, 22));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(spinRules->sizePolicy().hasHeightForWidth());
        spinRules->setSizePolicy(sizePolicy);
        spinRules->setMinimum(5);
        spinRules->setMaximum(80);
        spinRules->setValue(5);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(650, 480, 93, 21));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(400, 500, 55, 16));
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignCenter);
        doubleDa = new QDoubleSpinBox(centralWidget);
        doubleDa->setObjectName(QStringLiteral("doubleDa"));
        doubleDa->setGeometry(QRect(510, 510, 62, 22));
        doubleDa->setMinimum(0.01);
        doubleDa->setMaximum(1.99);
        doubleDa->setSingleStep(0.01);
        doubleDb = new QDoubleSpinBox(centralWidget);
        doubleDb->setObjectName(QStringLiteral("doubleDb"));
        doubleDb->setGeometry(QRect(510, 540, 62, 22));
        doubleDb->setMinimum(0.01);
        doubleDb->setMaximum(1.99);
        doubleDb->setSingleStep(0.01);
        doubleDc = new QDoubleSpinBox(centralWidget);
        doubleDc->setObjectName(QStringLiteral("doubleDc"));
        doubleDc->setGeometry(QRect(510, 570, 62, 22));
        doubleDc->setMinimum(0.01);
        doubleDc->setMaximum(1.99);
        doubleDc->setSingleStep(0.01);
        spinWeights = new QSpinBox(centralWidget);
        spinWeights->setObjectName(QStringLiteral("spinWeights"));
        spinWeights->setGeometry(QRect(400, 530, 51, 22));
        sizePolicy.setHeightForWidth(spinWeights->sizePolicy().hasHeightForWidth());
        spinWeights->setSizePolicy(sizePolicy);
        spinWeights->setMinimum(2);
        spinWeights->setMaximum(80);
        spinWeights->setValue(2);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(400, 570, 55, 16));
        label_2->setTextFormat(Qt::AutoText);
        label_2->setAlignment(Qt::AlignCenter);
        doubleDa_2 = new QDoubleSpinBox(centralWidget);
        doubleDa_2->setObjectName(QStringLiteral("doubleDa_2"));
        doubleDa_2->setGeometry(QRect(510, 480, 62, 22));
        doubleDa_2->setMinimum(0);
        doubleDa_2->setMaximum(1.99);
        doubleDa_2->setSingleStep(0.05);
        doubleDa_2->setValue(0);
        widget = new QCustomPlot(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(19, 19, 911, 431));
        spinShowWeight = new QSpinBox(centralWidget);
        spinShowWeight->setObjectName(QStringLiteral("spinShowWeight"));
        spinShowWeight->setGeometry(QRect(760, 480, 42, 22));
        spinShowWeight->setMaximum(0);
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(320, 470, 42, 22));
        spinBox->setMinimum(4);
        spinBox->setMaximum(500);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(320, 500, 55, 16));
        label_3->setTextFormat(Qt::AutoText);
        label_3->setAlignment(Qt::AlignCenter);
        spinPercentage = new QSpinBox(centralWidget);
        spinPercentage->setObjectName(QStringLiteral("spinPercentage"));
        spinPercentage->setGeometry(QRect(210, 470, 42, 22));
        spinPercentage->setMinimum(1);
        spinPercentage->setMaximum(99);
        spinPercentage->setValue(90);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(190, 490, 71, 20));
        label_4->setTextFormat(Qt::AutoText);
        label_4->setAlignment(Qt::AlignCenter);
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(150, 470, 41, 22));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(150, 490, 41, 20));
        label_5->setTextFormat(Qt::AutoText);
        label_5->setAlignment(Qt::AlignCenter);
        positOfClass = new QSpinBox(centralWidget);
        positOfClass->setObjectName(QStringLiteral("positOfClass"));
        positOfClass->setGeometry(QRect(90, 470, 51, 22));
        sizePolicy.setHeightForWidth(positOfClass->sizePolicy().hasHeightForWidth());
        positOfClass->setSizePolicy(sizePolicy);
        positOfClass->setMinimum(0);
        positOfClass->setMaximum(80);
        redundant = new QSpinBox(centralWidget);
        redundant->setObjectName(QStringLiteral("redundant"));
        redundant->setGeometry(QRect(30, 470, 51, 22));
        sizePolicy.setHeightForWidth(redundant->sizePolicy().hasHeightForWidth());
        redundant->setSizePolicy(sizePolicy);
        redundant->setMinimum(0);
        redundant->setMaximum(80);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(90, 490, 41, 20));
        label_6->setTextFormat(Qt::AutoText);
        label_6->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(30, 490, 41, 20));
        label_7->setTextFormat(Qt::AutoText);
        label_7->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1014, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        MainWindow->insertToolBarBreak(toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionLoadFile->setText(QApplication::translate("MainWindow", "loadFile", 0));
        toolButton->setText(QApplication::translate("MainWindow", "loadTrainset", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Train", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "showWeights", 0));
        label->setText(QApplication::translate("MainWindow", "rules", 0));
        doubleDa->setSuffix(QApplication::translate("MainWindow", "da", 0));
        doubleDb->setSuffix(QApplication::translate("MainWindow", "db", 0));
        doubleDc->setSuffix(QApplication::translate("MainWindow", "dc", 0));
        label_2->setText(QApplication::translate("MainWindow", "weights", 0));
        doubleDa_2->setSuffix(QApplication::translate("MainWindow", "c", 0));
        label_3->setText(QApplication::translate("MainWindow", "iterations", 0));
        label_4->setText(QApplication::translate("MainWindow", "percentage", 0));
        lineEdit->setText(QApplication::translate("MainWindow", "\\t", 0));
        label_5->setText(QApplication::translate("MainWindow", "delim", 0));
        label_6->setText(QApplication::translate("MainWindow", "class", 0));
        label_7->setText(QApplication::translate("MainWindow", "id", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
