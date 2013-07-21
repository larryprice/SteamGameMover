#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>
#include <QThread>

class SteamAppDirectorySelector;
class SteamAppDataTransferer;
class TransferErrorDialog;
class TransferProgressDialog;

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
    QScopedPointer<SteamAppDataTransferer> DataTransferer;
    QScopedPointer<TransferErrorDialog> Error;
    QScopedPointer<TransferProgressDialog> Progress;

    QThread TransferThread;
};

#endif // MAINWINDOW_H
