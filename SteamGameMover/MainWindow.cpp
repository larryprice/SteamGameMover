#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "SteamAppDirectorySelector.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    Ui(new Ui::MainWindow),
    LeftDirectorySelector(),
    RightDirectorySelector(),
    DataTransferer(),
    Error(this),
    Progress(this),
    About(this),
    Help(this),
    TransferThread()
{
    Ui->setupUi(this);

    LeftDirectorySelector.reset(new SteamAppDirectorySelector(Ui->SteamAppLocationLeftText,
                                                         Ui->AppsLeftListBox,
                                                         this));
    RightDirectorySelector.reset(new SteamAppDirectorySelector(Ui->SteamAppLocationRightText,
                                                          Ui->AppsRightListBox,
                                                          this));

    connect(Ui->BrowseLeftBtn, SIGNAL(clicked()), LeftDirectorySelector.data(), SLOT(OpenFileDialog()));
    connect(Ui->RefreshBtn, SIGNAL(clicked()), LeftDirectorySelector.data(), SLOT(Refresh()));

    connect(Ui->BrowseRightBtn, SIGNAL(clicked()), RightDirectorySelector.data(), SLOT(OpenFileDialog()));
    connect(Ui->RefreshBtn, SIGNAL(clicked()), RightDirectorySelector.data(), SLOT(Refresh()));

    connect(Ui->MoveSelectedRightBtn, SIGNAL(clicked()), LeftDirectorySelector.data(), SLOT(MoveSelectedApps()));
    connect(Ui->MoveSelectedLeftBtn, SIGNAL(clicked()), RightDirectorySelector.data(), SLOT(MoveSelectedApps()));

    connect(Ui->MoveAllRightBtn, SIGNAL(clicked()), LeftDirectorySelector.data(), SLOT(MoveAllApps()));
    connect(Ui->MoveAllLeftBtn, SIGNAL(clicked()), RightDirectorySelector.data(), SLOT(MoveAllApps()));

    connect(Ui->actionAbout, SIGNAL(triggered()), &About, SLOT(show()));
    connect(Ui->actionHelp, SIGNAL(triggered()), &Help, SLOT(show()));

    SetupTransferer();
}

void MainWindow::SetupTransferer()
{
    connect(LeftDirectorySelector.data(), SIGNAL(AppDirChanged(QString)), &DataTransferer, SLOT(SetLeftDir(QString)));
    connect(RightDirectorySelector.data(), SIGNAL(AppDirChanged(QString)), &DataTransferer, SLOT(SetRightDir(QString)));

    connect(LeftDirectorySelector.data(), SIGNAL(MoveApps(QList<QSharedPointer<SteamAppListItem> >)), &DataTransferer, SLOT(MoveAppsLeftToRight(QList<QSharedPointer<SteamAppListItem> >)));
    connect(RightDirectorySelector.data(), SIGNAL(MoveApps(QList<QSharedPointer<SteamAppListItem> >)), &DataTransferer, SLOT(MoveAppsRightToLeft(QList<QSharedPointer<SteamAppListItem> >)));

    connect(&DataTransferer, SIGNAL(TransferComplete()), LeftDirectorySelector.data(), SLOT(Refresh()));
    connect(&DataTransferer, SIGNAL(TransferComplete()), RightDirectorySelector.data(), SLOT(Refresh()));

    connect(&DataTransferer, SIGNAL(ErrorsDuringTransfer(QList<AppTransferError>)), &Error, SLOT(Show(QList<AppTransferError>)));
    connect(&Error, SIGNAL(RetryTransfer(QList<QSharedPointer<SteamAppListItem> >)), &DataTransferer, SLOT(RetryPreviousTransfer(QList<QSharedPointer<SteamAppListItem> >)));

    connect(&DataTransferer, SIGNAL(TransferBeginning(int)), &Progress, SLOT(Show(int)));
    connect(&DataTransferer, SIGNAL(TransferComplete()), &Progress, SLOT(Hide()));

    connect(&DataTransferer, SIGNAL(SingleTransferStarting()), &Progress, SLOT(NewTransferStarted()));
    connect(&DataTransferer, SIGNAL(TransferProgress(QString,int)), &Progress, SLOT(UpdateProgress(QString,int)));

    connect(&Progress, SIGNAL(Abort()), this, SLOT(AbortTransfer()));

    DataTransferer.moveToThread(&TransferThread);
    TransferThread.start();

    LeftDirectorySelector->Refresh();
    RightDirectorySelector->Refresh();
}

void MainWindow::AbortTransfer()
{
    DataTransferer.AbortTransfer();
}

MainWindow::~MainWindow()
{
    TransferThread.quit();
    TransferThread.wait(1000);

    delete Ui;
    Ui = NULL;
}
