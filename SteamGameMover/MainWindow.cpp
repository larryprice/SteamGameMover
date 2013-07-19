#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "SteamAppDirectorySelector.h"
#include "SteamAppDataTransferer.h"
#include "TransferErrorDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    Ui(new Ui::MainWindow),
    LeftDirectorySelector(),
    RightDirectorySelector(),
    DataTransferer(new SteamAppDataTransferer()),
    Error(new TransferErrorDialog(parent))
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
    connect(DataTransferer.data(), SIGNAL(CopyFinished()), LeftDirectorySelector.data(), SLOT(Refresh()));

    connect(Ui->BrowseRightBtn, SIGNAL(clicked()), RightDirectorySelector.data(), SLOT(OpenFileDialog()));
    connect(Ui->RefreshBtn, SIGNAL(clicked()), RightDirectorySelector.data(), SLOT(Refresh()));
    connect(DataTransferer.data(), SIGNAL(CopyFinished()), RightDirectorySelector.data(), SLOT(Refresh()));

    connect(LeftDirectorySelector.data(), SIGNAL(AppDirChanged(QString)), DataTransferer.data(), SLOT(SetLeftDir(QString)));
    connect(RightDirectorySelector.data(), SIGNAL(AppDirChanged(QString)), DataTransferer.data(), SLOT(SetRightDir(QString)));

    connect(Ui->MoveSelectedRightBtn, SIGNAL(clicked()), LeftDirectorySelector.data(), SLOT(MoveSelectedApps()));
    connect(Ui->MoveSelectedLeftBtn, SIGNAL(clicked()), RightDirectorySelector.data(), SLOT(MoveSelectedApps()));

    connect(Ui->MoveAllRightBtn, SIGNAL(clicked()), LeftDirectorySelector.data(), SLOT(MoveAllApps()));
    connect(Ui->MoveAllLeftBtn, SIGNAL(clicked()), RightDirectorySelector.data(), SLOT(MoveAllApps()));

    connect(LeftDirectorySelector.data(), SIGNAL(MoveApps(QList<QSharedPointer<SteamAppListItem> >)), DataTransferer.data(), SLOT(MoveAppsLeftToRight(QList<QSharedPointer<SteamAppListItem> >)));
    connect(RightDirectorySelector.data(), SIGNAL(MoveApps(QList<QSharedPointer<SteamAppListItem> >)), DataTransferer.data(), SLOT(MoveAppsRightToLeft(QList<QSharedPointer<SteamAppListItem> >)));

    connect(DataTransferer.data(), SIGNAL(ErrorsDuringTransfer(QList<AppTransferError>)), Error.data(), SLOT(Show(QList<AppTransferError>)));
}

MainWindow::~MainWindow()
{
    delete Ui;
    Ui = NULL;
}
