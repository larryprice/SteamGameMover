#include "SteamAppDataTransferer.h"
#include "SteamAppListItem.h"
#include "SteamAppManifestParser.h"
#include <QDirIterator>
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
    MoveApps(apps, LeftDir, RightDir);
    emit CopyFinished();
}

void SteamAppDataTransferer::MoveAppsRightToLeft(const QList<QSharedPointer<SteamAppListItem> >& apps)
{
    MoveApps(apps, RightDir, LeftDir);
    emit CopyFinished();
}

#include <QDebug>
void SteamAppDataTransferer::MoveApps(const QList<QSharedPointer<SteamAppListItem> >& apps, const QString& source, const QString &destination) const
{
    foreach (const QSharedPointer<SteamAppListItem>& app, apps)
    {
        QString installPath = app->GetInstallDir();
        QDir installDir(installPath);
        if (!installDir.exists())
        {
            // sometimes on Linux, Steam puts "steamapps" as the appinstalldir even though it should be "SteamApps"
            installPath.replace("steamapps", "SteamApps");
            installDir.setPath(installPath);

            if (!installDir.exists())
            {
                qDebug() << "Could not find install dir";
                continue;
            }
        }

        if (!CopyFilesRecursively(installDir, source, destination))
        {
            qDebug() << "Copy failed";
            continue;
        }

        QString newAppFilePath = app->GetManifestFilePath().replace(source, destination);
        if (!QFile::copy(app->GetManifestFilePath(), newAppFilePath))
        {
            qDebug() << "Failed to copy manifest.";
            continue;
        }

        SteamAppManifestParser parser(newAppFilePath);
        if (!parser.SetInstallDir(installPath.replace(source, destination)))
        {
            qDebug() << "Failed to edit manifest";
            continue;
        }

        if (!installDir.removeRecursively())
        {
            qDebug() << "Failed to delete original files";
            continue;
        }

        QFile appManifest(app->GetManifestFilePath());
        if (!appManifest.remove())
        {
            qDebug() << "Failed to delete original manifest";
            continue;
        }
    }
}

bool SteamAppDataTransferer::CopyFilesRecursively(const QDir& sourceDir, const QString& sourceBasePath, const QString& destBasePath) const
{
    bool success = true;

    QDirIterator iterator(sourceDir.absolutePath(), QDirIterator::Subdirectories);
    while (iterator.hasNext())
    {
        iterator.next();
        if (!iterator.fileInfo().isDir())
        {
            QFileInfo fileInfo = iterator.fileInfo();
            QString relevantPath = fileInfo.absolutePath().replace(sourceBasePath, destBasePath);
            QString destFile = fileInfo.absoluteFilePath().replace(sourceBasePath, destBasePath);

            if (!sourceDir.mkpath(relevantPath) || !QFile::copy(fileInfo.absoluteFilePath(), destFile))
            {
                success = false;
                break;
            }
        }
    }

    return success;
}
