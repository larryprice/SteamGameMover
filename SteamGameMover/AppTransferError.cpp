#include "AppTransferError.h"
#include "SteamAppListItem.h"

AppTransferError::AppTransferError(const QSharedPointer<SteamAppListItem>& app, const QString &error) :
    App(app),
    Error(error)
{
}

AppTransferError::AppTransferError(const AppTransferError& rhs) :
    App(rhs.App),
    Error(rhs.Error)
{
}

AppTransferError::~AppTransferError()
{
}

QSharedPointer<SteamAppListItem> AppTransferError::GetApp() const
{
    return App;
}

QString AppTransferError::GetErrorMessage() const
{
    return QString("%1: %2").arg(App->GetName()).arg(Error);
}
