#include "AutoTest.h"

#include "../SteamGameMover/SteamAppListItem.h"

#include <QFile>

class SteamAppListItemTest: public QObject
{
    Q_OBJECT
private slots:
    void GetAppManifestPathReturnsAppManifestFilePath();
    void GetNameReturnsNameOfApp();
    void GetNameReturnsEmptyStringWhenFileDoesNotExist();
    void GetSizeReturnsZeroWhenFileDoesNotExist();
    void GetSizeReturnsSizeOnDisk();
    void GetInstallDirReturnsEmptyStringWhenFileDoesNotExist();
    void GetInstallDirReturnsAppInstallDir();
};

void SteamAppListItemTest::GetAppManifestPathReturnsAppManifestFilePath()
{
    QString filePath("TestData/appmanifest_225260.acf");
    SteamAppListItem item(filePath);
    QCOMPARE(item.GetManifestFilePath(), filePath);
}

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

void SteamAppListItemTest::GetSizeReturnsZeroWhenFileDoesNotExist()
{
    QString filePath("TestData/herp_derp");
    QVERIFY2(!QFile::exists(filePath), "Test file should not exist!");
    SteamAppListItem item(filePath);
    QCOMPARE(item.GetSize(), (qulonglong)0);
}

void SteamAppListItemTest::GetSizeReturnsSizeOnDisk()
{
    QString filePath("TestData/appmanifest_225260.acf");
    QVERIFY2(QFile::exists(filePath), "Test file does not exist!");
    SteamAppListItem item(filePath);
    QCOMPARE(item.GetSize(), (qulonglong)8998762563);
}

void SteamAppListItemTest::GetInstallDirReturnsAppInstallDir()
{
    QString filePath("TestData/appmanifest_225260.acf");
    QVERIFY2(QFile::exists(filePath), "Test file does not exist!");
    SteamAppListItem item(filePath);
    QCOMPARE(item.GetInstallDir(), QString("/home/lrp/Projects/2013/SteamGameMover/build-SteamGameMoverTest/TestData/common/BrutalLegend"));
}

void SteamAppListItemTest::GetInstallDirReturnsEmptyStringWhenFileDoesNotExist()
{
    QString filePath("TestData/herp_derp");
    QVERIFY2(!QFile::exists(filePath), "Test file should not exist!");
    SteamAppListItem item(filePath);
    QCOMPARE(item.GetInstallDir(), QString());
}

DECLARE_TEST(SteamAppListItemTest)
#include "SteamAppListItemTest.moc"
