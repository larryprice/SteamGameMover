#ifndef APP_TRANSFER_ERROR_H
#define APP_TRANSFER_ERROR_H

#include <QString>
#include <QSharedPointer>

class SteamAppListItem;

class AppTransferError
{
public:
    AppTransferError(const QSharedPointer<SteamAppListItem> &app, const QString& error);
    AppTransferError(const AppTransferError& rhs);
    virtual ~AppTransferError();

    QSharedPointer<SteamAppListItem> GetApp() const;
    QString GetErrorMessage() const;

private:

    QSharedPointer<SteamAppListItem> App;
    QString Error;
};

#endif // APP_TRANSFER_ERROR_H
