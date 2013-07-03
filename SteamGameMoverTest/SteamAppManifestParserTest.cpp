#include "AutoTest.h"

#include "../SteamGameMover/SteamAppManifestParser.h"

#include <QFile>

class SteamAppManifestParserTest: public QObject
{
    Q_OBJECT
private slots:
    void GetAppManifestPathReturnsAppManifestFilePath();
    void GetAppNameReturnsNameOfApp();
    void GetAppNameReturnsEmptyStringWhenFileDoesNotExist();
    void GetSizeReturnsZeroWhenFileDoesNotExist();
    void GetSizeReturnsSizeOnDisk();
    void GetInstallDirReturnsEmptyStringWhenFileDoesNotExist();
    void GetInstallDirReturnsAppInstallDir();
};

void SteamAppManifestParserTest::GetAppManifestPathReturnsAppManifestFilePath()
{
    QString filePath("TestData/appmanifest_225260.acf");
    SteamAppManifestParser parser(filePath);
    QCOMPARE(parser.GetManifestFilePath(), filePath);
}

void SteamAppManifestParserTest::GetAppNameReturnsNameOfApp()
{
    QString filePath("TestData/appmanifest_225260.acf");
    QVERIFY2(QFile::exists(filePath), "Test file does not exist!");
    SteamAppManifestParser parser(filePath);
    QCOMPARE(parser.GetAppName(), QString("Brütal Legend"));
}

void SteamAppManifestParserTest::GetAppNameReturnsEmptyStringWhenFileDoesNotExist()
{
    QString filePath("TestData/herp_derp");
    QVERIFY2(!QFile::exists(filePath), "Test file should not exist!");
    SteamAppManifestParser parser(filePath);
    QCOMPARE(parser.GetAppName(), QString());
}

void SteamAppManifestParserTest::GetSizeReturnsZeroWhenFileDoesNotExist()
{
    QString filePath("TestData/herp_derp");
    QVERIFY2(!QFile::exists(filePath), "Test file should not exist!");
    SteamAppManifestParser parser(filePath);
    QCOMPARE(parser.GetSize(), (qulonglong)0);
}

void SteamAppManifestParserTest::GetSizeReturnsSizeOnDisk()
{
    QString filePath("TestData/appmanifest_225260.acf");
    QVERIFY2(QFile::exists(filePath), "Test file does not exist!");
    SteamAppManifestParser parser(filePath);
    QCOMPARE(parser.GetSize(), (qulonglong)8998762563);
}

void SteamAppManifestParserTest::GetInstallDirReturnsAppInstallDir()
{
    QString filePath("TestData/appmanifest_225260.acf");
    QVERIFY2(QFile::exists(filePath), "Test file does not exist!");
    SteamAppManifestParser parser(filePath);
    QCOMPARE(parser.GetInstallDir(), QString("/home/lrp/Projects/2013/SteamGameMover/build-SteamGameMoverTest/TestData/common/BrutalLegend"));
}

void SteamAppManifestParserTest::GetInstallDirReturnsEmptyStringWhenFileDoesNotExist()
{
    QString filePath("TestData/herp_derp");
    QVERIFY2(!QFile::exists(filePath), "Test file should not exist!");
    SteamAppManifestParser parser(filePath);
    QCOMPARE(parser.GetInstallDir(), QString());
}

DECLARE_TEST(SteamAppManifestParserTest)
#include "SteamAppManifestParserTest.moc"
