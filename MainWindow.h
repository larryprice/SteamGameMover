#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>

class SGMDirectorySelector;

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
    QScopedPointer<SGMDirectorySelector> LeftDirectorySelector;
    QScopedPointer<SGMDirectorySelector> RightDirectorySelector;
};

#endif // MAINWINDOW_H
