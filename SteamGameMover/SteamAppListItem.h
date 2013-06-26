#ifndef STEAM_APP_LIST_ITEM_H
#define STEAM_APP_LIST_ITEM_H

#include <QObject>
#include <QScopedPointer>

class SteamAppManifestParser;

class SteamAppListItem : public QObject
{
    Q_OBJECT
public:
    SteamAppListItem(const QString &manifestName, QObject *parent = 0);
    virtual ~SteamAppListItem();

    virtual QString GetName() const;

private:
    QScopedPointer<SteamAppManifestParser> ManifestParser;
};

#endif // STEAM_APP_LIST_ITEM_H
