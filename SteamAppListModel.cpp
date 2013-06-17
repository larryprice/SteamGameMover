#include "SteamAppListModel.h"
#include "SteamAppListItem.h"

SteamAppListModel::SteamAppListModel(QList<QSharedPointer<SteamAppListItem> > apps, QObject *parent) :
    QAbstractListModel(parent),
    Apps(apps)
{
}

int SteamAppListModel::rowCount(const QModelIndex& /*parent*/) const
{
    return Apps.count();
}

QVariant SteamAppListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() >= Apps.count())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        return Apps.at(index.row())->GetName();
    }
    else
    {
        return QVariant();
    }
}

QVariant SteamAppListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return role != Qt::DisplayRole ?
                (orientation == Qt::Horizontal
                 ? QString("Column %1").arg(section)
                 : QString("Row %1").arg(section))
              : QVariant();
}
