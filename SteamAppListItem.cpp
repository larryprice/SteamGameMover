#include "SteamAppListItem.h"

SteamAppListItem::SteamAppListItem(QString name, QObject *parent)
    : QObject(parent),
    Name(name)
{
}

QString SteamAppListItem::GetName() const
{
    return Name;
}
