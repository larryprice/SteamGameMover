#include "TransferProgressDialog.h"
#include "ui_TransferProgressDialog.h"

#include <QCloseEvent>
#include <QKeyEvent>
#include <QPushButton>

TransferProgressDialog::TransferProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransferProgressDialog),
    TotalNumApps(0),
    CurrentAppNum(0)
{
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    ui->setupUi(this);

    connect(ui->abortButton, SIGNAL(clicked()), this, SLOT(Abort()));
}

TransferProgressDialog::~TransferProgressDialog()
{
    delete ui;
}

void TransferProgressDialog::Show(int numApps)
{
    TotalNumApps = numApps;
    CurrentAppNum = 0;

    UpdateTransferLabel();
    ui->messages->clear();
    UpdateProgress(QString("Transferring %1 apps").arg(TotalNumApps), 0);

    show();
}

void TransferProgressDialog::UpdateTransferLabel()
{
    ui->transferLabel->setText(QString("Transferring %1 of %2 games...").arg(CurrentAppNum).arg(TotalNumApps));
}

void TransferProgressDialog::Abort()
{
    // do nothing
}

void TransferProgressDialog::NewTransferStarted()
{
    ++CurrentAppNum;
    UpdateTransferLabel();
}

void TransferProgressDialog::UpdateProgress(const QString& msg, int percentage)
{
    ui->messages->append(msg);
    ui->progressBar->setValue(percentage);
}

void TransferProgressDialog::closeEvent(QCloseEvent* e)
{
    e->ignore();
}

void TransferProgressDialog::keyPressEvent(QKeyEvent* e)
{
    if (Qt::Key_Escape == e->key())
    {
        e->ignore();
    }
}
