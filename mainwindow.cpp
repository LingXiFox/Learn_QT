#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ui_untitled.h"

#include <QDialog>
#include <QDialogButtonBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->addButton, &QPushButton::clicked, this, [this]() {
        const QString text = ui->lineEditInput->text().trimmed();
        if (text.isEmpty()) {
            return;
        }
        ui->listWidget->addItem(text);
        ui->lineEditInput->clear();
        ui->lineEditInput->setFocus();
    });

    connect(ui->deleteButton, &QPushButton::clicked, this, [this]() {
        const int row = ui->listWidget->currentRow();
        if (row < 0) {
            return;
        }
        QDialog confirmDialog(this);
        Ui::Dialog confirmUi;
        confirmUi.setupUi(&confirmDialog);
        confirmDialog.setWindowTitle(tr("Confirm Deletion"));
        connect(confirmUi.buttonBox, &QDialogButtonBox::accepted, &confirmDialog, &QDialog::accept);
        connect(confirmUi.buttonBox, &QDialogButtonBox::rejected, &confirmDialog, &QDialog::reject);
        if (confirmDialog.exec() != QDialog::Accepted) {
            return;
        }
        delete ui->listWidget->takeItem(row);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
