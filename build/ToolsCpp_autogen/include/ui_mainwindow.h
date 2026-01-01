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
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
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
    QAction *actionSave;
    QAction *actionOpen;
    QAction *actionExit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *TabBase64;
    QPushButton *ActionButton_Base64;
    QComboBox *ChoiceMode_Base64;
    QTextEdit *InputBox_Base64;
    QTextEdit *OutputBox_Base64;
    QLabel *label;
    QWidget *TabHaxi;
    QTextEdit *InputBox_Haxi;
    QTextEdit *OutputBox_Haxi;
    QLabel *label_2;
    QPushButton *ActionButton_Haxi;
    QComboBox *ChoiceMode_Haxi;
    QComboBox *ChoiceSalt_Haxi;
    QWidget *TabNcm;
    QLineEdit *LimeView_ncm;
    QListWidget *ListShow_ncm;
    QPushButton *InputButton_ncm;
    QPushButton *ActionButton_ncm;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 570);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        TabBase64 = new QWidget();
        TabBase64->setObjectName("TabBase64");
        ActionButton_Base64 = new QPushButton(TabBase64);
        ActionButton_Base64->setObjectName("ActionButton_Base64");
        ActionButton_Base64->setGeometry(QRect(320, 400, 131, 51));
        ChoiceMode_Base64 = new QComboBox(TabBase64);
        ChoiceMode_Base64->addItem(QString());
        ChoiceMode_Base64->addItem(QString());
        ChoiceMode_Base64->setObjectName("ChoiceMode_Base64");
        ChoiceMode_Base64->setGeometry(QRect(0, 0, 151, 51));
        InputBox_Base64 = new QTextEdit(TabBase64);
        InputBox_Base64->setObjectName("InputBox_Base64");
        InputBox_Base64->setGeometry(QRect(10, 50, 341, 331));
        OutputBox_Base64 = new QTextEdit(TabBase64);
        OutputBox_Base64->setObjectName("OutputBox_Base64");
        OutputBox_Base64->setGeometry(QRect(420, 50, 341, 331));
        label = new QLabel(TabBase64);
        label->setObjectName("label");
        label->setGeometry(QRect(370, 200, 58, 16));
        tabWidget->addTab(TabBase64, QString());
        TabHaxi = new QWidget();
        TabHaxi->setObjectName("TabHaxi");
        InputBox_Haxi = new QTextEdit(TabHaxi);
        InputBox_Haxi->setObjectName("InputBox_Haxi");
        InputBox_Haxi->setGeometry(QRect(10, 40, 341, 301));
        OutputBox_Haxi = new QTextEdit(TabHaxi);
        OutputBox_Haxi->setObjectName("OutputBox_Haxi");
        OutputBox_Haxi->setGeometry(QRect(420, 40, 341, 301));
        label_2 = new QLabel(TabHaxi);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(370, 180, 58, 16));
        ActionButton_Haxi = new QPushButton(TabHaxi);
        ActionButton_Haxi->setObjectName("ActionButton_Haxi");
        ActionButton_Haxi->setGeometry(QRect(320, 370, 131, 51));
        ChoiceMode_Haxi = new QComboBox(TabHaxi);
        ChoiceMode_Haxi->addItem(QString());
        ChoiceMode_Haxi->addItem(QString());
        ChoiceMode_Haxi->addItem(QString());
        ChoiceMode_Haxi->setObjectName("ChoiceMode_Haxi");
        ChoiceMode_Haxi->setGeometry(QRect(10, 0, 151, 51));
        ChoiceSalt_Haxi = new QComboBox(TabHaxi);
        ChoiceSalt_Haxi->addItem(QString());
        ChoiceSalt_Haxi->addItem(QString());
        ChoiceSalt_Haxi->addItem(QString());
        ChoiceSalt_Haxi->addItem(QString());
        ChoiceSalt_Haxi->addItem(QString());
        ChoiceSalt_Haxi->addItem(QString());
        ChoiceSalt_Haxi->addItem(QString());
        ChoiceSalt_Haxi->addItem(QString());
        ChoiceSalt_Haxi->addItem(QString());
        ChoiceSalt_Haxi->addItem(QString());
        ChoiceSalt_Haxi->addItem(QString());
        ChoiceSalt_Haxi->addItem(QString());
        ChoiceSalt_Haxi->addItem(QString());
        ChoiceSalt_Haxi->addItem(QString());
        ChoiceSalt_Haxi->addItem(QString());
        ChoiceSalt_Haxi->addItem(QString());
        ChoiceSalt_Haxi->setObjectName("ChoiceSalt_Haxi");
        ChoiceSalt_Haxi->setGeometry(QRect(180, 0, 151, 51));
        tabWidget->addTab(TabHaxi, QString());
        TabNcm = new QWidget();
        TabNcm->setObjectName("TabNcm");
        LimeView_ncm = new QLineEdit(TabNcm);
        LimeView_ncm->setObjectName("LimeView_ncm");
        LimeView_ncm->setGeometry(QRect(20, 20, 731, 31));
        ListShow_ncm = new QListWidget(TabNcm);
        ListShow_ncm->setObjectName("ListShow_ncm");
        ListShow_ncm->setGeometry(QRect(20, 70, 731, 311));
        InputButton_ncm = new QPushButton(TabNcm);
        InputButton_ncm->setObjectName("InputButton_ncm");
        InputButton_ncm->setGeometry(QRect(60, 390, 151, 61));
        ActionButton_ncm = new QPushButton(TabNcm);
        ActionButton_ncm->setObjectName("ActionButton_ncm");
        ActionButton_ncm->setGeometry(QRect(230, 390, 151, 61));
        tabWidget->addTab(TabNcm, QString());

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

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        ActionButton_Base64->setText(QCoreApplication::translate("MainWindow", "\350\277\220\350\241\214", nullptr));
        ChoiceMode_Base64->setItemText(0, QCoreApplication::translate("MainWindow", "Base64\347\274\226\347\240\201", nullptr));
        ChoiceMode_Base64->setItemText(1, QCoreApplication::translate("MainWindow", "Base64\350\247\243\347\240\201", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "\342\200\224\342\200\224>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(TabBase64), QCoreApplication::translate("MainWindow", "Base64", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\342\200\224\342\200\224>", nullptr));
        ActionButton_Haxi->setText(QCoreApplication::translate("MainWindow", "\350\277\220\350\241\214", nullptr));
        ChoiceMode_Haxi->setItemText(0, QCoreApplication::translate("MainWindow", "SHA256", nullptr));
        ChoiceMode_Haxi->setItemText(1, QCoreApplication::translate("MainWindow", "MD5(\350\277\207\346\227\266\347\232\204)", nullptr));
        ChoiceMode_Haxi->setItemText(2, QCoreApplication::translate("MainWindow", "FNV1A64", nullptr));

        ChoiceSalt_Haxi->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        ChoiceSalt_Haxi->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));
        ChoiceSalt_Haxi->setItemText(2, QCoreApplication::translate("MainWindow", "3", nullptr));
        ChoiceSalt_Haxi->setItemText(3, QCoreApplication::translate("MainWindow", "4", nullptr));
        ChoiceSalt_Haxi->setItemText(4, QCoreApplication::translate("MainWindow", "5", nullptr));
        ChoiceSalt_Haxi->setItemText(5, QCoreApplication::translate("MainWindow", "6", nullptr));
        ChoiceSalt_Haxi->setItemText(6, QCoreApplication::translate("MainWindow", "7", nullptr));
        ChoiceSalt_Haxi->setItemText(7, QCoreApplication::translate("MainWindow", "8", nullptr));
        ChoiceSalt_Haxi->setItemText(8, QCoreApplication::translate("MainWindow", "9", nullptr));
        ChoiceSalt_Haxi->setItemText(9, QCoreApplication::translate("MainWindow", "10", nullptr));
        ChoiceSalt_Haxi->setItemText(10, QCoreApplication::translate("MainWindow", "11", nullptr));
        ChoiceSalt_Haxi->setItemText(11, QCoreApplication::translate("MainWindow", "12", nullptr));
        ChoiceSalt_Haxi->setItemText(12, QCoreApplication::translate("MainWindow", "13", nullptr));
        ChoiceSalt_Haxi->setItemText(13, QCoreApplication::translate("MainWindow", "14", nullptr));
        ChoiceSalt_Haxi->setItemText(14, QCoreApplication::translate("MainWindow", "15", nullptr));
        ChoiceSalt_Haxi->setItemText(15, QCoreApplication::translate("MainWindow", "16", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(TabHaxi), QCoreApplication::translate("MainWindow", "HaXi", nullptr));
        LimeView_ncm->setText(QString());
        InputButton_ncm->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245", nullptr));
        ActionButton_ncm->setText(QCoreApplication::translate("MainWindow", "\350\277\220\350\241\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(TabNcm), QCoreApplication::translate("MainWindow", "NCM", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
