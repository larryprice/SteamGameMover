#include "SteamAppListItem.h"
#include "SteamAppManifestParser.h"

SteamAppListItem::SteamAppListItem(const QString& manifestName, QObject *parent)
    : QObject(parent),
    ManifestParser(new SteamAppManifestParser(manifestName))
{
}

SteamAppListItem::~SteamAppListItem() {}

QString SteamAppListItem::GetName() const
{
    return ManifestParser->GetAppName();
}

qulonglong SteamAppListItem::GetSize() const
{
    return ManifestParser->GetSize();
}

QString SteamAppListItem::GetInstallDir() const
{
    return ManifestParser->GetInstallDir();
}
