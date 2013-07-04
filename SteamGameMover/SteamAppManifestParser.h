#ifndef STEAM_APP_MANIFEST_PARSER_H
#define STEAM_APP_MANIFEST_PARSER_H

#include <QString>
#include <QSharedPointer>

class SteamAppManifestParser
{
public:
    SteamAppManifestParser(const QString& filePath);
    virtual ~SteamAppManifestParser();

    QString GetManifestFilePath() const;

    QString GetAppName();
    qulonglong GetSize();
    QString GetInstallDir();
    bool SetInstallDir(const QString &newDir);
private:
    bool WriteManifest(const QStringList& lines) const;
    QString FindField(const QString& field);

    QString AppManifestFilePath;

    QString AppName;
    qulonglong SizeOnDisk;
    QString InstallDir;
};

#endif // STEAM_APP_MANIFEST_PARSER_H
