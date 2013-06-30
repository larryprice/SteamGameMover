#ifndef STEAMAPPDATATRANSFERER_H
#define STEAMAPPDATATRANSFERER_H

#include <QDir>
#include <QObject>

class SteamAppListItem;

class SteamAppDataTransferer : public QObject
{
    Q_OBJECT
public:
    SteamAppDataTransferer(QObject *parent = 0);
    virtual ~SteamAppDataTransferer();

    QString GetLeftDir() const;
    QString GetRightDir() const;

public slots:
    void SetLeftDir(const QString& dirName);
    void SetRightDir(const QString& dirName);
    void MoveAppsLeftToRight(const QList<QSharedPointer<SteamAppListItem> >& apps);
    void MoveAppsRightToLeft(const QList<QSharedPointer<SteamAppListItem> >& apps);

private:
    void MoveFilesRecursively(const QDir &sourceDir, const QString &destBasePath) const;
    void MoveApps(const QList<QSharedPointer<SteamAppListItem> > &apps, const QString& destination) const;

    QString LeftDir;
    QString RightDir;
};

#endif // STEAMAPPDATATRANSFERER_H
