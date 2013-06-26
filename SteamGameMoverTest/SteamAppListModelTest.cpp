#include "AutoTest.h"

#include "../SteamGameMover/SteamAppListModel.h"
#include "../SteamGameMover/SteamAppListItem.h"

#include <QFile>

class SteamAppListModelTest: public QObject
{
    Q_OBJECT
private slots:
    void RowCountReturnsZeroForNoApps();
    void RowCountReturnsOneForOneApp();
    void RowCountReturnsTwoForTwoApps();
    void DataReturnsEmptyForInvalidIndex();
    void DataReturnsEmptyForOutOfRangeIndex();
    void DataReturnsEmptyForRoleThatIsNotDisplayRole();
    void DataReturnsExpectedData();
};

class SteamAppListItemFake : public SteamAppListItem
{
public:
    SteamAppListItemFake(QString name) : SteamAppListItem(""), Name(name) {}
    QString GetName() const { return Name; }

private:
    QString Name;
};

void SteamAppListModelTest::RowCountReturnsZeroForNoApps()
{
    QList<QSharedPointer<SteamAppListItem> > apps;
    SteamAppListModel model(apps);
    QCOMPARE(0, model.rowCount());
}

void SteamAppListModelTest::RowCountReturnsOneForOneApp()
{
    QList<QSharedPointer<SteamAppListItem> > apps;
    apps << QSharedPointer<SteamAppListItem>(new SteamAppListItem(""));
    SteamAppListModel model(apps);
    QCOMPARE(1, model.rowCount());
}

void SteamAppListModelTest::RowCountReturnsTwoForTwoApps()
{
    QList<QSharedPointer<SteamAppListItem> > apps;
    apps << QSharedPointer<SteamAppListItem>(new SteamAppListItem(""))
         << QSharedPointer<SteamAppListItem>(new SteamAppListItem(""));
    SteamAppListModel model(apps);
    QCOMPARE(2, model.rowCount());
}

void SteamAppListModelTest::DataReturnsEmptyForInvalidIndex()
{
    QList<QSharedPointer<SteamAppListItem> > apps;
    SteamAppListModel model(apps);
    QCOMPARE(0, model.rowCount());
    QModelIndex idx;
    QVERIFY(!idx.isValid());
    QVERIFY(model.data(idx).isNull());
}

void SteamAppListModelTest::DataReturnsEmptyForOutOfRangeIndex()
{
    QList<QSharedPointer<SteamAppListItem> > appsToCreateIndex;
    appsToCreateIndex << QSharedPointer<SteamAppListItem>(new SteamAppListItem(""));
    SteamAppListModel modelToCreateIndex(appsToCreateIndex);
    QCOMPARE(1, modelToCreateIndex.rowCount());
    QModelIndex idx = modelToCreateIndex.index(0);

    QList<QSharedPointer<SteamAppListItem> > apps;
    SteamAppListModel model(apps);
    QCOMPARE(0, model.rowCount());
    QVERIFY(idx.isValid());
    QVERIFY(model.data(idx).isNull());
}

void SteamAppListModelTest::DataReturnsEmptyForRoleThatIsNotDisplayRole()
{
    QList<QSharedPointer<SteamAppListItem> > apps;
    apps << QSharedPointer<SteamAppListItem>(new SteamAppListItem(""));
    SteamAppListModel model(apps);
    QCOMPARE(1, model.rowCount());
    QModelIndex idx = model.index(0);
    QVERIFY(model.data(idx, Qt::UserRole).isNull());
}

void SteamAppListModelTest::DataReturnsExpectedData()
{
    QList<QSharedPointer<SteamAppListItem> > apps;
    apps << QSharedPointer<SteamAppListItem>(new SteamAppListItemFake("Item1"))
         << QSharedPointer<SteamAppListItem>(new SteamAppListItemFake("Item2"))
         << QSharedPointer<SteamAppListItem>(new SteamAppListItemFake("Item3"));
    SteamAppListModel model(apps);
    QCOMPARE(3, model.rowCount());
    QModelIndex idx = model.index(1);

    QVariant variant = model.data(idx);
    QVERIFY(!variant.isNull());
    QCOMPARE(variant.toString(), QString("Item2"));
}

DECLARE_TEST(SteamAppListModelTest)
#include "SteamAppListModelTest.moc"
