#ifndef STEAM_APP_MANIFEST_PARSER_H
#define STEAM_APP_MANIFEST_PARSER_H

#include <QString>
#include <QSharedPointer>

class SteamAppManifestParser
{
public:
    SteamAppManifestParser(const QString& filePath);
    virtual ~SteamAppManifestParser();

    QString GetAppName();
    qulonglong GetSize();
    QString GetInstallDir();
private:
    QString FindField(const QString& field);

    QString AppManifestFilePath;

    QString AppName;
    qulonglong SizeOnDisk;
    QString InstallDir;
};

#endif // STEAM_APP_MANIFEST_PARSER_H
