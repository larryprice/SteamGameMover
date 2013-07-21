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
    void closeEvent(QCloseEvent* e);

private slots:
    void Abort();
    
private:
    Ui::TransferProgressDialog *ui;
};

#endif // TRANSFER_PROGRESS_DIALOG_H
