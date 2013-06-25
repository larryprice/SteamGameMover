#ifndef STEAM_APP_LIST_ITEM_H
#define STEAM_APP_LIST_ITEM_H

#include <QObject>
#include <QSharedPointer>

class SteamAppManifestParser;

class SteamAppListItem : public QObject
{
    Q_OBJECT
public:
    SteamAppListItem(const QString &manifestName, QObject *parent = 0);

    QString GetName() const;

private:
    QSharedPointer<SteamAppManifestParser> ManifestParser;
};

#endif // STEAM_APP_LIST_ITEM_H
