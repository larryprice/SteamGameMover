#include "TransferProgressDialog.h"
#include "ui_TransferProgressDialog.h"

#include <QPushButton>

TransferProgressDialog::TransferProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransferProgressDialog)
{
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(Abort()));
}

TransferProgressDialog::~TransferProgressDialog()
{
    delete ui;
}

void TransferProgressDialog::Abort()
{
    // do nothing
}

#include <QCloseEvent>
void TransferProgressDialog::closeEvent(QCloseEvent* e)
{
//    e->ignore();
}
