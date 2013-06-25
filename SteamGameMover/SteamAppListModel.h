#ifndef STEAM_APP_LIST_MODEL_H
#define STEAM_APP_LIST_MODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QSharedPointer>
#include <QStringList>

class SteamAppListItem;

class SteamAppListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    SteamAppListModel(QList<QSharedPointer<SteamAppListItem> > apps, QObject *parent = 0);
    virtual ~SteamAppListModel() {}

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
    QList<QSharedPointer<SteamAppListItem> > Apps;
};

#endif // STEAM_APP_LIST_MODEL_H
