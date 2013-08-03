#include "HelpDialog.h"
#include "ui_HelpDialog.h"

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
}

HelpDialog::~HelpDialog()
{
    delete ui;
}

void HelpDialog::resizeEvent(QResizeEvent *)
{
    QSize tabSize = ui->tabWidget->currentWidget()->size();

    ui->moveOneGameInstructions->resize(tabSize);
    ui->moveSomeGamesInstructions->resize(tabSize);
    ui->moveAllGamesInstructions->resize(tabSize);
}
