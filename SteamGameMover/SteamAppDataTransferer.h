#ifndef STEAM_APP_DATA_TRANSFERER_H
#define STEAM_APP_DATA_TRANSFERER_H

#include <QDir>
#include <QObject>

class SteamAppListItem;
class AppTransferError;

class SteamAppDataTransferer : public QObject
{
    Q_OBJECT
public:
    SteamAppDataTransferer(QObject *parent = 0);
    SteamAppDataTransferer(const SteamAppDataTransferer& rhs);
    virtual ~SteamAppDataTransferer();

    QString GetLeftDir() const;
    QString GetRightDir() const;

signals:
    void CopyFinished();
    void ErrorsDuringTransfer(const QList<AppTransferError>&);

public slots:
    void SetLeftDir(const QString& dirName);
    void SetRightDir(const QString& dirName);
    void MoveAppsLeftToRight(const QList<QSharedPointer<SteamAppListItem> >& apps);
    void MoveAppsRightToLeft(const QList<QSharedPointer<SteamAppListItem> >& apps);

private:
    bool CopyFilesRecursively(const QDir &sourceDir, const QString &sourceBasePath, const QString &destBasePath) const;
    void MoveApps(const QList<QSharedPointer<SteamAppListItem> > &apps, const QString &source, const QString& destination);

    QString LeftDir;
    QString RightDir;
};

#endif // STEAM_APP_DATA_TRANSFERER_H
