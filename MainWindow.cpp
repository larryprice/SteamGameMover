#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SGMDirectorySelector.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    Ui(new Ui::MainWindow),
    LeftDirectorySelector(),
    RightDirectorySelector()
{
    Ui->setupUi(this);

    LeftDirectorySelector.reset(new SGMDirectorySelector(Ui->SteamAppLocationLeftText,
                                                         Ui->AppsLeftListBox,
                                                         this));
    RightDirectorySelector.reset(new SGMDirectorySelector(Ui->SteamAppLocationRightText,
                                                          Ui->AppsRightListBox,
                                                          this));

    connect(Ui->BrowseLeftBtn, SIGNAL(clicked()), LeftDirectorySelector.data(), SLOT(OpenFileDialog()));
    connect(Ui->RefreshBtn, SIGNAL(clicked()), LeftDirectorySelector.data(), SLOT(Refresh()));

    connect(Ui->BrowseRightBtn, SIGNAL(clicked()), RightDirectorySelector.data(), SLOT(OpenFileDialog()));
    connect(Ui->RefreshBtn, SIGNAL(clicked()), RightDirectorySelector.data(), SLOT(Refresh()));
}

MainWindow::~MainWindow()
{
    delete Ui;
    Ui = NULL;
}
