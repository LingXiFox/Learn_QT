#include <iostream>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString text = ui->ChoiceMode->currentText();
    if(text == QStringLiteral("Base64解码"))
    {
        std::cout << "First" << std::endl;
    }
    else
    {
        std::cout << "Second" << std::endl;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
