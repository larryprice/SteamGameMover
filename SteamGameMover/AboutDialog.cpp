#include "AboutDialog.h"
#include "ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

    ui->setupUi(this);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
