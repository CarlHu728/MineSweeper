/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionEasy;
    QAction *actionMedium;
    QAction *actionHard;
    QAction *actionCustom;
    QAction *actionAbout;
    QWidget *centralwidget;
    QPushButton *RestartButton;
    QLabel *RemainMineLabel;
    QLabel *TimeCountLabel;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(300, 350);
        MainWindow->setMinimumSize(QSize(300, 350));
        MainWindow->setMaximumSize(QSize(300, 350));
        MainWindow->setAnimated(true);
        actionEasy = new QAction(MainWindow);
        actionEasy->setObjectName("actionEasy");
        actionEasy->setCheckable(true);
        actionMedium = new QAction(MainWindow);
        actionMedium->setObjectName("actionMedium");
        actionMedium->setCheckable(true);
        actionHard = new QAction(MainWindow);
        actionHard->setObjectName("actionHard");
        actionHard->setCheckable(true);
        actionCustom = new QAction(MainWindow);
        actionCustom->setObjectName("actionCustom");
        actionCustom->setCheckable(true);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        RestartButton = new QPushButton(centralwidget);
        RestartButton->setObjectName("RestartButton");
        RestartButton->setGeometry(QRect(130, 10, 30, 30));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RestartButton->sizePolicy().hasHeightForWidth());
        RestartButton->setSizePolicy(sizePolicy);
        RemainMineLabel = new QLabel(centralwidget);
        RemainMineLabel->setObjectName("RemainMineLabel");
        RemainMineLabel->setGeometry(QRect(30, 20, 49, 21));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial Black")});
        font.setPointSize(16);
        font.setBold(true);
        RemainMineLabel->setFont(font);
        RemainMineLabel->setAlignment(Qt::AlignCenter);
        TimeCountLabel = new QLabel(centralwidget);
        TimeCountLabel->setObjectName("TimeCountLabel");
        TimeCountLabel->setGeometry(QRect(210, 20, 49, 16));
        TimeCountLabel->setFont(font);
        TimeCountLabel->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 300, 21));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu->addAction(actionEasy);
        menu->addAction(actionMedium);
        menu->addAction(actionHard);
        menu->addAction(actionCustom);
        menu->addSeparator();
        menu_2->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Mine Sweeper", nullptr));
        actionEasy->setText(QCoreApplication::translate("MainWindow", "Easy", nullptr));
        actionMedium->setText(QCoreApplication::translate("MainWindow", "Medium", nullptr));
        actionHard->setText(QCoreApplication::translate("MainWindow", "Hard", nullptr));
        actionCustom->setText(QCoreApplication::translate("MainWindow", "Custom", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        RestartButton->setText(QCoreApplication::translate("MainWindow", ": )", nullptr));
        RemainMineLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        TimeCountLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "Game", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
