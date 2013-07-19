#include "TransferErrorDialog.h"
#include "ui_TransferErrorDialog.h"

#include "AppTransferError.h"

#include <QDialogButtonBox>
#include <QPushButton>

TransferErrorDialog::TransferErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransferErrorDialog),
    Errors()
{
    ui->setupUi(this);

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(ClearErrors()));
    connect(ui->buttonBox->button(QDialogButtonBox::Retry), SIGNAL(clicked()), this, SLOT(Retry()));
}

TransferErrorDialog::~TransferErrorDialog()
{
    delete ui;
}

void TransferErrorDialog::Show(const QList<AppTransferError> & errors)
{
    Errors = errors;

    ui->textBrowser->clear();
    foreach(const AppTransferError& error, errors)
    {
        ui->textBrowser->append(error.GetErrorMessage());
    }

    show();
}

void TransferErrorDialog::ClearErrors()
{
    Errors.clear();
}

void TransferErrorDialog::Retry()
{
    QList<QSharedPointer<SteamAppListItem> > apps;
    foreach(const AppTransferError& error, Errors)
    {
        apps << error.GetApp();
    }

    ClearErrors();

    emit RetryTransfer(apps);
}
