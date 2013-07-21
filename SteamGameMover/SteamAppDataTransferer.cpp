#include "SteamAppDataTransferer.h"
#include "SteamAppListItem.h"
#include "SteamAppManifestParser.h"
#include "AppTransferError.h"

#include <QDirIterator>
#include <QScopedPointer>
#include <QSharedPointer>

SteamAppDataTransferer::SteamAppDataTransferer(QObject *parent)
    : QObject(parent),
      LeftDir(),
      RightDir(),
      PreviousTransfer(None)
{
}

SteamAppDataTransferer::SteamAppDataTransferer(const SteamAppDataTransferer& rhs)
    : QObject(rhs.parent()),
      LeftDir(rhs.LeftDir),
      RightDir(rhs.RightDir),
      PreviousTransfer(rhs.PreviousTransfer)
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
    PreviousTransfer = LeftToRight;
    MoveApps(apps, LeftDir, RightDir);
}

void SteamAppDataTransferer::MoveAppsRightToLeft(const QList<QSharedPointer<SteamAppListItem> >& apps)
{
    PreviousTransfer = RightToLeft;
    MoveApps(apps, RightDir, LeftDir);
}

void SteamAppDataTransferer::RetryPreviousTransfer(const QList<QSharedPointer<SteamAppListItem> >& apps)
{
    if (LeftToRight == PreviousTransfer)
    {
        MoveAppsLeftToRight(apps);
    }
    else if (RightToLeft == PreviousTransfer)
    {
        MoveAppsRightToLeft(apps);
    }
}
#include <QThread>
void SteamAppDataTransferer::MoveApps(const QList<QSharedPointer<SteamAppListItem> >& apps, const QString& source, const QString &destination)
{
    emit TransferBeginning(apps.count());

    int percentComplete = 0;
    QList<AppTransferError> errors;
    foreach (const QSharedPointer<SteamAppListItem>& app, apps)
    {
        emit SingleTransferStarting();
        emit TransferProgress(QString("%1: %2 of %3 bytes copied").arg(app->GetName()).arg(0).arg(app->GetSize()), percentComplete);

        QThread::msleep(1000);
        QString installPath = app->GetInstallDir();
        QDir installDir(installPath);
        if (!installDir.exists())
        {
            // sometimes on Linux, Steam puts "steamapps" as the appinstalldir even though it should be "SteamApps"
            installPath.replace("steamapps", "SteamApps");
            installDir.setPath(installPath);

            if (!installDir.exists())
            {
                errors << AppTransferError(app, "Could not find install directory");
                continue;
            }
        }

        if (!CopyFilesRecursively(installDir, source, destination))
        {
            errors << AppTransferError(app, "Copy failed");
            continue;
        }

        QString newAppFilePath = app->GetManifestFilePath().replace(source, destination);
        if (!QFile::copy(app->GetManifestFilePath(), newAppFilePath))
        {
            errors << AppTransferError(app, "Copy of manifest failed");
            continue;
        }

        SteamAppManifestParser parser(newAppFilePath);
        if (!parser.SetInstallDir(installPath.replace(source, destination)))
        {
            errors << AppTransferError(app, "Edit of manifest failed");
            continue;
        }

        if (!installDir.removeRecursively())
        {
            errors << AppTransferError(app, "Removal of old files failed");
            continue;
        }

        QFile appManifest(app->GetManifestFilePath());
        if (!appManifest.remove())
        {
            errors << AppTransferError(app, "Removal of old manifest failed");
            continue;
        }

        percentComplete += 100 / apps.count();
    }

    if (!errors.empty())
    {
        emit ErrorsDuringTransfer(errors);
    }

    emit TransferComplete();
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
//            fileInfo.size()
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
