#ifndef TRANSFER_ERROR_DIALOG_H
#define TRANSFER_ERROR_DIALOG_H

#include <QDialog>

namespace Ui {
class TransferErrorDialog;
}

class AppTransferError;
class SteamAppListItem;

class TransferErrorDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit TransferErrorDialog(QWidget *parent = 0);
    ~TransferErrorDialog();

signals:
    void RetryTransfer(const QList<QSharedPointer<SteamAppListItem> >&);

public slots:
    void Show(const QList<AppTransferError>&);
    void Retry();

private slots:
    void ClearErrors();
    
private:
    Ui::TransferErrorDialog *ui;
    QList<AppTransferError> Errors;
};

#endif // TRANSFER_ERROR_DIALOG_H
