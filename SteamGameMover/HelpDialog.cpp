#include "HelpDialog.h"
#include "ui_HelpDialog.h"

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);

    connect(ui->moveOneGameBtn, SIGNAL(clicked()), this, SLOT(ShowOneGameInstructions()));
    connect(ui->moveSomeGamesBtn, SIGNAL(clicked()), this, SLOT(ShowSomeGamesInstructions()));
    connect(ui->moveAllGamesBtn, SIGNAL(clicked()), this, SLOT(ShowAllGamesInstructions()));

    ShowOneGameInstructions();
}

HelpDialog::~HelpDialog()
{
    delete ui;
}

void HelpDialog::ShowOneGameInstructions()
{
    SwitchInstructions(ui->moveOneGameInstructions);
}

void HelpDialog::ShowSomeGamesInstructions()
{
    SwitchInstructions(ui->moveSomeGamesInstructions);
}

void HelpDialog::ShowAllGamesInstructions()
{
    SwitchInstructions(ui->moveAllGamesInstructions);
}

void HelpDialog::SwitchInstructions(QWidget *textToShow)
{
    ui->moveOneGameBtn->setChecked(false);
    ui->moveOneGameInstructions->setVisible(false);
    ui->moveSomeGamesBtn->setChecked(false);
    ui->moveSomeGamesInstructions->setVisible(false);
    ui->moveAllGamesBtn->setChecked(false);
    ui->moveAllGamesInstructions->setVisible(false);

    textToShow->setVisible(true);
}
