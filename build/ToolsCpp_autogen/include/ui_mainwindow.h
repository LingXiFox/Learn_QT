/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *TabBase64;
    QPushButton *ActionButton;
    QComboBox *ChoiceMode;
    QTextEdit *InputBox;
    QTextEdit *OutputBox;
    QLabel *label;
    QWidget *TabHaxi;
    QWidget *TabNcm;
    QWidget *TabSet;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        TabBase64 = new QWidget();
        TabBase64->setObjectName("TabBase64");
        ActionButton = new QPushButton(TabBase64);
        ActionButton->setObjectName("ActionButton");
        ActionButton->setGeometry(QRect(20, 370, 131, 51));
        ChoiceMode = new QComboBox(TabBase64);
        ChoiceMode->addItem(QString());
        ChoiceMode->addItem(QString());
        ChoiceMode->setObjectName("ChoiceMode");
        ChoiceMode->setGeometry(QRect(0, 0, 151, 51));
        InputBox = new QTextEdit(TabBase64);
        InputBox->setObjectName("InputBox");
        InputBox->setGeometry(QRect(10, 50, 341, 301));
        OutputBox = new QTextEdit(TabBase64);
        OutputBox->setObjectName("OutputBox");
        OutputBox->setGeometry(QRect(420, 50, 341, 301));
        label = new QLabel(TabBase64);
        label->setObjectName("label");
        label->setGeometry(QRect(370, 200, 58, 16));
        tabWidget->addTab(TabBase64, QString());
        TabHaxi = new QWidget();
        TabHaxi->setObjectName("TabHaxi");
        tabWidget->addTab(TabHaxi, QString());
        TabNcm = new QWidget();
        TabNcm->setObjectName("TabNcm");
        tabWidget->addTab(TabNcm, QString());
        TabSet = new QWidget();
        TabSet->setObjectName("TabSet");
        tabWidget->addTab(TabSet, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 30));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        ActionButton->setText(QCoreApplication::translate("MainWindow", "\350\277\220\350\241\214", nullptr));
        ChoiceMode->setItemText(0, QCoreApplication::translate("MainWindow", "Base64\347\274\226\347\240\201", nullptr));
        ChoiceMode->setItemText(1, QCoreApplication::translate("MainWindow", "Base64\350\247\243\347\240\201", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "\342\200\224\342\200\224>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(TabBase64), QCoreApplication::translate("MainWindow", "Base64", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(TabHaxi), QCoreApplication::translate("MainWindow", "HaXi", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(TabNcm), QCoreApplication::translate("MainWindow", "NCM", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(TabSet), QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
