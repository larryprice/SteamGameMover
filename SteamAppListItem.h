#ifndef STEAM_APP_LIST_ITEM_H
#define STEAM_APP_LIST_ITEM_H

#include <QObject>

class SteamAppListItem : public QObject
{
    Q_OBJECT
public:
    SteamAppListItem(QString manifestName, QObject *parent = 0);

    QString GetName() const;

private:
    QString AppManifestFilePath;
    QString Name;
};

#endif // STEAM_APP_LIST_ITEM_H
