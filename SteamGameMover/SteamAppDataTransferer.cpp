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
    foreach (QSharedPointer<SteamAppListItem> app, apps)
    {
        QString installPath = app->GetInstallDir();
        QDir installDir(installPath);
        if (!installDir.exists())
        {
            // sometimes on Linux, Steam puts "steamapps" as the appinstalldir even though it should be SteamApps
            installPath.replace("steamapps", "SteamApps");
            installDir.setPath(installPath);
        }

        if (installDir.exists())
        {
            MoveFilesRecursively(installDir, source, destination);

            QString appFilePath(app->GetManifestFilePath());
            QString newAppFilePath = app->GetManifestFilePath().replace(source, destination);
            if (QFile::copy(appFilePath, newAppFilePath))
            {
                SteamAppManifestParser parser(newAppFilePath);
                parser.SetInstallDir(installDir.absolutePath().replace(source, destination));
            }
            else
            {
                qDebug() << "Could not copy manifest.";
            }
        }
    }
}

void SteamAppDataTransferer::MoveFilesRecursively(const QDir& sourceDir, const QString& sourceBasePath, const QString& destBasePath) const
{
    QDirIterator iterator(sourceDir.absolutePath(), QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        iterator.next();
        if (!iterator.fileInfo().isDir())
        {
            QString sourceFile = iterator.filePath();

            QFileInfo fileInfo = iterator.fileInfo();
            QString relevantPath = fileInfo.absolutePath().replace(sourceBasePath, destBasePath);
            QString destFile = fileInfo.absoluteFilePath().replace(sourceBasePath, destBasePath);

            if (!sourceDir.mkpath(relevantPath))
            {
                qDebug() << "Failed to mkPath" << relevantPath;
            }
            if (!QFile::copy(sourceFile, destFile))
            {
                qDebug() << sourceFile << "failed to copy";
            }
        }
    }
}
