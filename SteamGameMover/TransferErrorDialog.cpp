#include "TransferErrorDialog.h"
#include "ui_TransferErrorDialog.h"

#include "AppTransferError.h"

TransferErrorDialog::TransferErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransferErrorDialog)
{
    ui->setupUi(this);
}

TransferErrorDialog::~TransferErrorDialog()
{
    delete ui;
}

void TransferErrorDialog::Show(const QList<AppTransferError> & errors)
{
    ui->textBrowser->clear();
    foreach(const AppTransferError& error, errors)
    {
        ui->textBrowser->append(error.GetErrorMessage());
    }
    show();
}
