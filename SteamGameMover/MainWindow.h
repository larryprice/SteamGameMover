#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "AboutDialog.h"
#include "HelpDialog.h"
#include "SteamAppDataTransferer.h"
#include "TransferProgressDialog.h"
#include "TransferErrorDialog.h"

#include <QMainWindow>
#include <QScopedPointer>
#include <QThread>

class SteamAppDirectorySelector;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void SetupTransferer();

public slots:
    void AbortTransfer();
    
private:
    Ui::MainWindow* Ui;
    QScopedPointer<SteamAppDirectorySelector> LeftDirectorySelector;
    QScopedPointer<SteamAppDirectorySelector> RightDirectorySelector;
    SteamAppDataTransferer DataTransferer;
    TransferErrorDialog Error;
    TransferProgressDialog Progress;
    AboutDialog About;
    HelpDialog Help;

    QThread TransferThread;
};

#endif // MAINWINDOW_H
