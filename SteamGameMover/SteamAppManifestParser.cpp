#include "SteamAppManifestParser.h"
#include <QFile>
#include <QStringList>
#include <QTextStream>

SteamAppManifestParser::SteamAppManifestParser(const QString& filePath)
    : AppManifestFilePath(filePath)
{
}

SteamAppManifestParser::~SteamAppManifestParser()
{
}

QString SteamAppManifestParser::GetAppName()
{
    if (AppName.isNull())
    {
        QFile manifest(AppManifestFilePath);
        if (manifest.open(QIODevice::ReadOnly))
        {
            QTextStream manifestStream(&manifest);
            while (!manifestStream.atEnd())
            {
                QStringList lines = manifestStream.readLine().simplified().split("\" \"");
                if (lines.count() == 2 && lines.first() == "\"name")
                {
                    AppName = lines.last();
                    AppName.chop(1);
                    break;
                }
            }
            manifest.close();
        }
    }

    return AppName;
}
