#ifndef TRANSFER_ERROR_DIALOG_H
#define TRANSFER_ERROR_DIALOG_H

#include <QDialog>

namespace Ui {
class TransferErrorDialog;
}

class AppTransferError;

class TransferErrorDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit TransferErrorDialog(QWidget *parent = 0);
    ~TransferErrorDialog();

public slots:
    void Show(const QList<AppTransferError>&);
    
private:
    Ui::TransferErrorDialog *ui;
};

#endif // TRANSFER_ERROR_DIALOG_H
