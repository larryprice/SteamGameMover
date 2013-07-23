#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "AboutDialog.h"
#include "SteamAppDirectorySelector.h"
#include "SteamAppDataTransferer.h"
#include "TransferErrorDialog.h"
#include "TransferProgressDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    Ui(new Ui::MainWindow),
    LeftDirectorySelector(),
    RightDirectorySelector(),
    DataTransferer(new SteamAppDataTransferer()),
    Error(new TransferErrorDialog(parent)),
    Progress(new TransferProgressDialog(parent)),
    About(new AboutDialog(parent)),
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

    connect(Ui->actionAbout, SIGNAL(triggered()), About.data(), SLOT(show()));

    SetupTransferer();
}

void MainWindow::SetupTransferer()
{
    connect(LeftDirectorySelector.data(), SIGNAL(AppDirChanged(QString)), DataTransferer.data(), SLOT(SetLeftDir(QString)));
    connect(RightDirectorySelector.data(), SIGNAL(AppDirChanged(QString)), DataTransferer.data(), SLOT(SetRightDir(QString)));

    connect(LeftDirectorySelector.data(), SIGNAL(MoveApps(QList<QSharedPointer<SteamAppListItem> >)), DataTransferer.data(), SLOT(MoveAppsLeftToRight(QList<QSharedPointer<SteamAppListItem> >)));
    connect(RightDirectorySelector.data(), SIGNAL(MoveApps(QList<QSharedPointer<SteamAppListItem> >)), DataTransferer.data(), SLOT(MoveAppsRightToLeft(QList<QSharedPointer<SteamAppListItem> >)));

    connect(DataTransferer.data(), SIGNAL(TransferComplete()), LeftDirectorySelector.data(), SLOT(Refresh()));
    connect(DataTransferer.data(), SIGNAL(TransferComplete()), RightDirectorySelector.data(), SLOT(Refresh()));

    connect(DataTransferer.data(), SIGNAL(ErrorsDuringTransfer(QList<AppTransferError>)), Error.data(), SLOT(Show(QList<AppTransferError>)));
    connect(Error.data(), SIGNAL(RetryTransfer(QList<QSharedPointer<SteamAppListItem> >)), DataTransferer.data(), SLOT(RetryPreviousTransfer(QList<QSharedPointer<SteamAppListItem> >)));

    connect(DataTransferer.data(), SIGNAL(TransferBeginning(int)), Progress.data(), SLOT(Show(int)));
    connect(DataTransferer.data(), SIGNAL(TransferComplete()), Progress.data(), SLOT(Hide()));

    connect(DataTransferer.data(), SIGNAL(SingleTransferStarting()), Progress.data(), SLOT(NewTransferStarted()));
    connect(DataTransferer.data(), SIGNAL(TransferProgress(QString,int)), Progress.data(), SLOT(UpdateProgress(QString,int)));

    connect(Progress.data(), SIGNAL(Abort()), this, SLOT(AbortTransfer()));

    DataTransferer->moveToThread(&TransferThread);
    TransferThread.start();
}

void MainWindow::AbortTransfer()
{
    DataTransferer->AbortTransfer();
}

MainWindow::~MainWindow()
{
    TransferThread.quit();
    TransferThread.wait(1000);

    delete Ui;
    Ui = NULL;
}
