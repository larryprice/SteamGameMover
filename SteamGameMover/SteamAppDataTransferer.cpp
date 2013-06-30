#include "SteamAppDataTransferer.h"
#include "SteamAppListItem.h"
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
    MoveApps(apps, RightDir);
}

void SteamAppDataTransferer::MoveAppsRightToLeft(const QList<QSharedPointer<SteamAppListItem> >& apps)
{
    MoveApps(apps, LeftDir);
}
#include <QDebug>
void SteamAppDataTransferer::MoveFilesRecursively(const QDir& sourceDir, const QString& destBasePath) const
{
    QString sourceBasePath = sourceDir.absolutePath();
    QDirIterator iterator(sourceDir.absolutePath(), QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        iterator.next();
        if (!iterator.fileInfo().isDir())
        {
             QString sourceFile = iterator.filePath();
             QString destFile = iterator.fileInfo().absoluteFilePath().replace(sourceBasePath, destBasePath);
             qDebug() << destFile;
//             QFile::copy(sourceFile, destFile);
        }
    }
}

void SteamAppDataTransferer::MoveApps(const QList<QSharedPointer<SteamAppListItem> >& apps, const QString &destination) const
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
            MoveFilesRecursively(installDir, destination);
        }
    }
}
