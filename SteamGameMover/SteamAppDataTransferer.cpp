#include "SteamAppDataTransferer.h"
#include "SteamAppListItem.h"
#include <QSharedPointer>

SteamAppDataTransferer::SteamAppDataTransferer(QObject *parent)
    : QObject(parent),
      LeftDir(),
      RightDir()
{
}


SteamAppDataTransferer::~SteamAppDataTransferer()
{
}

void SteamAppDataTransferer::SetLeftDir(const QString& dirName)
{
    LeftDir = dirName;
}

QString SteamAppDataTransferer::GetLeftDir() const
{
    return LeftDir;
}

void SteamAppDataTransferer::SetRightDir(const QString& dirName)
{
    RightDir = dirName;
}

QString SteamAppDataTransferer::GetRightDir() const
{
    return RightDir;
}

void SteamAppDataTransferer::MoveAppsLeftToRight(const QList<QSharedPointer<SteamAppListItem> >& apps)
{
    foreach (QSharedPointer<SteamAppListItem> app, apps)
    {
        app->GetName();
    }
}

void SteamAppDataTransferer::MoveAppsRightToLeft(const QList<QSharedPointer<SteamAppListItem> >& /*apps*/)
{

}
