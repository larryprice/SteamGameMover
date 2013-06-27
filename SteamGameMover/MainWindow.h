#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>

class SteamAppDirectorySelector;
class SteamAppDataTransferer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow* Ui;
    QScopedPointer<SteamAppDirectorySelector> LeftDirectorySelector;
    QScopedPointer<SteamAppDirectorySelector> RightDirectorySelector;
    QScopedPointer<SteamAppDataTransferer> DataTransferer;
};

#endif // MAINWINDOW_H
