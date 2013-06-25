#include "AutoTest.h"

#include "../SteamGameMover/SteamAppListItem.h"

#include <QFile>

class SteamAppListItemTest: public QObject
{
    Q_OBJECT
private slots:
    void GetNameReturnsNameOfApp();
    void GetNameReturnsEmptyStringWhenFileDoesNotExist();
};

void SteamAppListItemTest::GetNameReturnsNameOfApp()
{
    QString filePath("TestData/appmanifest_225260.acf");
    QVERIFY2(QFile::exists(filePath), "Test file does not exist!");
    SteamAppListItem item(filePath);
    QCOMPARE(item.GetName(), QString("Brütal Legend"));
}

void SteamAppListItemTest::GetNameReturnsEmptyStringWhenFileDoesNotExist()
{
    QString filePath("TestData/herp_derp");
    QVERIFY2(!QFile::exists(filePath), "Test file should not exist!");
    SteamAppListItem item(filePath);
    QCOMPARE(item.GetName(), QString());
}

DECLARE_TEST(SteamAppListItemTest)
#include "SteamAppListItemTest.moc"
