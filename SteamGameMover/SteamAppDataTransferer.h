#ifndef STEAMAPPDATATRANSFERER_H
#define STEAMAPPDATATRANSFERER_H

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
    QString LeftDir;
    QString RightDir;
};

#endif // STEAMAPPDATATRANSFERER_H
