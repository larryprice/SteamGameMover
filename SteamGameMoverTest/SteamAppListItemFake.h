#ifndef STEAMAPPLISTITEMFAKE_H
#define STEAMAPPLISTITEMFAKE_H

#include "../SteamGameMover/SteamAppListItem.h"

#include <QString>

class SteamAppListItemFake : public SteamAppListItem
{
public:
    SteamAppListItemFake(QString manifestName = "")
        : SteamAppListItem(manifestName),
          ManifestName(manifestName)
    {}

    SteamAppListItemFake(const SteamAppListItemFake& rhs)
        : SteamAppListItem(rhs.ManifestName),
          Name(rhs.Name),
          InstallDir(rhs.InstallDir),
          ManifestName(rhs.ManifestName)
    {}

    QString GetName() const { return Name; }
    QString GetInstallDir() const { return InstallDir; }

    void SetName(const QString& name) { Name = name; }
    void SetInstallDir(const QString& installDir) { InstallDir = installDir; }
    void SubInstallDir(const QString& oldDir, const QString& replaceDir)
    {
        InstallDir = SteamAppListItem::GetInstallDir().replace(oldDir, replaceDir);
    }

private:
    QString Name;
    QString InstallDir;
    QString ManifestName;
};

#endif // STEAMAPPLISTITEMFAKE_H
