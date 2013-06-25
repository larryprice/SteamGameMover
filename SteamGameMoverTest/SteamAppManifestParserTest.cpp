#include "AutoTest.h"

#include "../SteamGameMover/SteamAppManifestParser.h"

#include <QFile>

class SteamAppManifestParserTest: public QObject
{
    Q_OBJECT
private slots:
    void GetAppNameReturnsNameOfApp();
    void GetAppNameReturnsEmptyStringWhenFileDoesNotExist();
};

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

DECLARE_TEST(SteamAppManifestParserTest)
#include "SteamAppManifestParserTest.moc"
