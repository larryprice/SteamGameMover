#ifndef TRANSFER_PROGRESS_DIALOG_H
#define TRANSFER_PROGRESS_DIALOG_H

#include <QDialog>

namespace Ui {
class TransferProgressDialog;
}

class TransferProgressDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit TransferProgressDialog(QWidget *parent = 0);
    virtual ~TransferProgressDialog();

public slots:
    virtual void closeEvent(QCloseEvent* e);
    virtual void keyPressEvent(QKeyEvent* e);

    void Show(int numApps);
    void NewTransferStarted();
    void UpdateProgress(const QString &msg, int percentage);

signals:
    void Abort();

private:
    void UpdateTransferLabel();
    
private:
    Ui::TransferProgressDialog *ui;
    int TotalNumApps;
    int CurrentAppNum;
};

#endif // TRANSFER_PROGRESS_DIALOG_H
