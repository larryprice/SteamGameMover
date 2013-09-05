#include "SteamAppDataTransferer.h"
#include "SteamAppListItem.h"
#include "SteamAppManifestParser.h"
#include "AppTransferError.h"

#include <QDirIterator>
#include <QSharedPointer>
#include <QThread>

SteamAppDataTransferer::SteamAppDataTransferer(QObject *parent)
    : QObject(parent),
      LeftDir(),
      RightDir(),
      PreviousTransfer(None),
      Abort(false),
      PercentComplete(0.0)
{
    qRegisterMetaType<QList<AppTransferError> >("QList<AppTransferError>");
}

SteamAppDataTransferer::SteamAppDataTransferer(const SteamAppDataTransferer& rhs)
    : QObject(rhs.parent()),
      LeftDir(rhs.LeftDir),
      RightDir(rhs.RightDir),
      PreviousTransfer(rhs.PreviousTransfer),
      Abort(false),
      PercentComplete(0.0)
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

void SteamAppDataTransferer::UpdateProgress(float amount, const QString& message)
{
    PercentComplete += amount;
    if (100.0 < PercentComplete)
    {
        PercentComplete = 100.0;
    }

    emit TransferProgress(QString("%1\%... %2").arg(QString::number(PercentComplete, 'f', 2)).arg(message), PercentComplete);
}

void SteamAppDataTransferer::MoveApps(const QList<QSharedPointer<SteamAppListItem> >& apps, const QString& source, const QString &destination)
{
    Abort = false;
    PercentComplete = 0.0;
    emit TransferBeginning(apps.count());

    quint16 appNum = 0;
    quint16 numApps = apps.count();
    float share = 100.0 / numApps;
    QList<AppTransferError> errors;
    foreach (const QSharedPointer<SteamAppListItem>& app, apps)
    {
        emit SingleTransferStarting();
        UpdateProgress(0, QString("%1: Beginning transfer").arg(app->GetName()));

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

        if (!CopyFilesRecursively(installDir, source, destination, share))
        {
            errors << AppTransferError(app, "Copy failed");
            continue;
        }

        UpdateProgress(0, QString("%1: Copying manifest file").arg(app->GetName()));
        QString newAppFilePath = app->GetManifestFilePath().replace(source, destination);
        if (!QFile::copy(app->GetManifestFilePath(), newAppFilePath))
        {
            errors << AppTransferError(app, "Copy of manifest failed");
            continue;
        }

        UpdateProgress(0, QString("%1: Editing manifest file").arg(app->GetName()));
        SteamAppManifestParser parser(newAppFilePath);
        if (!parser.SetInstallDir(installPath.replace(source, destination)))
        {
            errors << AppTransferError(app, "Edit of manifest failed");
            continue;
        }

        UpdateProgress(0, QString("%1: Deleting old install files").arg(app->GetName()));
        if (!installDir.removeRecursively())
        {
            errors << AppTransferError(app, "Removal of old files failed");
            continue;
        }

        UpdateProgress(0, QString("%1: Deleting old manifest file").arg(app->GetName()));
        QFile appManifest(app->GetManifestFilePath());
        if (!appManifest.remove())
        {
            errors << AppTransferError(app, "Removal of old manifest failed");
            continue;
        }

        PercentComplete = (++appNum * 100) / numApps;
        UpdateProgress(0, QString("%1: Transfer complete").arg(app->GetName()));

        if (Abort)
        {
            UpdateProgress(0, QString("Transfer aborted!"));
            Abort = false;
            break;
        }
    }

    if (!errors.empty())
    {
        UpdateProgress(0, QString("Errors during transfer."));
        emit ErrorsDuringTransfer(errors);
    }

    emit TransferComplete();
}

bool SteamAppDataTransferer::CopyFilesRecursively(const QDir& sourceDir, const QString& sourceBasePath, const QString& destBasePath, float share)
{
    bool success = true;
    quint64 numTotal = 0;

    QDirIterator iterator1(sourceDir.absolutePath(), QDirIterator::Subdirectories);
    while (iterator1.hasNext())
    {
        iterator1.next();
        if (!iterator1.fileInfo().isDir())
        {
            numTotal++;
        }
    }

    int numCopied = 0;
    float sharePerFile = share / numTotal;

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

            UpdateProgress(sharePerFile, QString("Copied %1 of %2 files").arg(++numCopied).arg(numTotal));
        }

        if (Abort)
        {
            break;
        }
    }

    return success;
}

void SteamAppDataTransferer::AbortTransfer()
{
    Abort = true;
}
