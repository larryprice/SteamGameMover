#ifndef STEAMAPPDATATRANSFERER_H
#define STEAMAPPDATATRANSFERER_H

#include <QObject>

class SteamAppDataTransferer : public QObject
{
    Q_OBJECT
public:
    SteamAppDataTransferer(QObject *parent = 0);
    virtual ~SteamAppDataTransferer();
};

#endif // STEAMAPPDATATRANSFERER_H
