#include "SGMListItemModel.h"

SGMListItemModel::SGMListItemModel(QStringList stringList, QObject *parent) :
    QAbstractListModel(parent),
    Items(stringList)
{
}

int SGMListItemModel::rowCount(const QModelIndex& /*parent*/) const
{
    return Items.count();
}

QVariant SGMListItemModel::data(const QModelIndex& index, int role ) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() >= Items.count())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        return Items.at(index.row());
    }
    else
    {
        return QVariant();
    }
}

QVariant SGMListItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return role != Qt::DisplayRole ?
                (orientation == Qt::Horizontal
                 ? QString("Column %1").arg(section)
                 : QString("Row %1").arg(section))
              : QVariant();
}
