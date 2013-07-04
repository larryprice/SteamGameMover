#include "SteamAppManifestParser.h"
#include <QFile>
#include <QStringList>
#include <QTextStream>

SteamAppManifestParser::SteamAppManifestParser(const QString& filePath)
    : AppManifestFilePath(filePath),
      AppName(),
      SizeOnDisk(0),
      InstallDir()
{
}

SteamAppManifestParser::~SteamAppManifestParser()
{
}

QString SteamAppManifestParser::GetAppName()
{
    if (AppName.isNull())
    {
        AppName = FindField("name");
    }

    return AppName;
}

QString SteamAppManifestParser::GetManifestFilePath() const
{
    return AppManifestFilePath;
}

qulonglong SteamAppManifestParser::GetSize()
{
    if (0 == SizeOnDisk)
    {
        SizeOnDisk = FindField("SizeOnDisk").toULongLong();
    }

    return SizeOnDisk;
}

QString SteamAppManifestParser::GetInstallDir()
{
    if (InstallDir.isNull())
    {
        InstallDir = FindField("appinstalldir");
    }

    return InstallDir;
}

#include <QDebug>
bool SteamAppManifestParser::SetInstallDir(const QString& newDir)
{
    QFile manifest(AppManifestFilePath);
    if (manifest.open(QIODevice::ReadOnly))
    {
        QStringList linesToWrite;
        QTextStream manifestStream(&manifest);
        while (!manifestStream.atEnd())
        {
            QString line = manifestStream.readLine();
            QStringList lines = line.simplified().split("\" \"");
            QString preparedField = QString("\"%1").arg("appinstalldir");
            if (lines.count() == 2 && lines.first() == preparedField)
            {
                lines[1].chop(1);
                line.replace(lines[1], newDir);
            }
            linesToWrite << line;
        }
        manifest.close();
        if (manifest.open(QIODevice::WriteOnly))
        {
            QTextStream manifestStream(&manifest);
            foreach(const QString& line, linesToWrite)
            {
                manifestStream << line << endl;
            }
        }
        manifest.close();
    }
    return false;
}

QString SteamAppManifestParser::FindField(const QString& field)
{
    QString value;
    QFile manifest(AppManifestFilePath);
    if (manifest.open(QIODevice::ReadOnly))
    {
        QTextStream manifestStream(&manifest);
        while (!manifestStream.atEnd())
        {
            QStringList lines = manifestStream.readLine().simplified().split("\" \"");
            QString preparedField = QString("\"%1").arg(field);
            if (lines.count() == 2 && lines.first() == preparedField)
            {
                value = lines.last();
                value.chop(1);
                break;
            }
        }
        manifest.close();
    }

    return value;
}
