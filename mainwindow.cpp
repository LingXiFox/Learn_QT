#include <iostream>
#include <string>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "base64.h"
#include "haxi.h"

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QStandardItemModel>
#include <QStandardItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //全局设置
    ui->OutputBox_Base64->setReadOnly(true);
    ui->OutputBox_Haxi->setReadOnly(true);
    int index = 1;
    QStandardItemModel *model = qobject_cast<QStandardItemModel *>(ui->ChoiceMode_Haxi->model());
    if (model) {
        QStandardItem *item = model->item(index);
        if (item) {
            item->setEnabled(false);
        }
    }

    //base64启动信号
    connect(ui->ActionButton_Base64, &QPushButton::clicked, this, [this](){
        QString CurrentChoice = ui->ChoiceMode_Base64->currentText();
        QString inputname_Base64 = ui->InputBox_Base64->toPlainText();
        std::string InputName_Base64 = inputname_Base64.toStdString();
        if(CurrentChoice == "Base64编码")
        {
            std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(InputName_Base64.data()), InputName_Base64.size());
            QString encodeString = QString::fromUtf8(encoded.c_str());
            ui->OutputBox_Base64->setPlainText(encodeString);
        }
        else
        {
            auto decoded = base64_decode(InputName_Base64);
            std::string decodestring(decoded.begin(), decoded.end());
            QString decodeString = QString::fromUtf8(decodestring.c_str());
            ui->OutputBox_Base64->setPlainText(decodeString);
        }
    });

    //Haxi启动信号
    connect(ui->ActionButton_Haxi, &QPushButton::clicked, this, [this](){
        QString CurrentHaxiMode = ui->ChoiceMode_Haxi->currentText();
        std::string Current_Haxi_Mode = CurrentHaxiMode.toStdString();
        QString CurrentHaxiSalt = ui->ChoiceSalt_Haxi->currentText();
        std::string Current_Haxi_Salt = CurrentHaxiSalt.toStdString();
        std::size_t Current_Haxi_Salt_T = static_cast<std::size_t>(std::stoull(Current_Haxi_Salt));
        QString inputname_Haxi = ui->InputBox_Haxi->toPlainText();
        std::string InputName_Haxi = inputname_Haxi.toStdString();
        haxi::HashType t;
        if(!haxi::from_string(Current_Haxi_Mode, t))
        {
            std::cerr << "未知错误";
            return;
        }
        std::string salt_hex;
        std::string digest = haxi::hash_with_new_salt_hex(InputName_Haxi, t, Current_Haxi_Salt_T, &salt_hex);
        std::string result = haxi::pack_result(t, salt_hex, digest);
        QString result_T = QString::fromUtf8(result.c_str());
        ui->OutputBox_Haxi->setPlainText(result_T);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
