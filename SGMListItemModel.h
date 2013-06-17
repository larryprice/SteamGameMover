#ifndef SGMLISTITEMMODEL_H
#define SGMLISTITEMMODEL_H

#include <QAbstractListModel>
#include <QStringList>

class SGMListItemModel : public QAbstractListModel
{
    Q_OBJECT
public:
    SGMListItemModel(QStringList stringList, QObject *parent = 0);
    virtual ~SGMListItemModel() {}

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    
signals:
    
public slots:
    
private:
    QStringList Items;
};

#endif // SGMLISTITEMMODEL_H
