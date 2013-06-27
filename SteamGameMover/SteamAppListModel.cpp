#include "SteamAppListModel.h"
#include "SteamAppListItem.h"

SteamAppListModel::SteamAppListModel(const QList<QSharedPointer<SteamAppListItem> >& apps, QObject *parent) :
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
    QVariant data;
    if (index.isValid() && index.row() < Apps.count() && role == Qt::DisplayRole)
    {
        data = Apps.at(index.row())->GetName();
    }

    return data;
}

QSharedPointer<SteamAppListItem> SteamAppListModel::app(const QModelIndex& index) const
{
    QSharedPointer<SteamAppListItem> app;
    if (index.isValid() && index.row() < Apps.count())
    {
        app = Apps.at(index.row());
    }

    return app;
}

QVariant SteamAppListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return role != Qt::DisplayRole ?
                (orientation == Qt::Horizontal
                 ? QString("Column %1").arg(section)
                 : QString("Row %1").arg(section))
              : QVariant();
}
