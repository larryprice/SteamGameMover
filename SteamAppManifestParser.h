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
private:
    QString AppManifestFilePath;

    QSharedPointer<QString> AppName;
};

#endif // STEAM_APP_MANIFEST_PARSER_H
