#include "AutoTest.h"

class SteamAppManifestParserTest: public QObject
{
    Q_OBJECT
private slots:
    void GetAppNameReturnsNameOfApp();
};

void SteamAppManifestParserTest::GetAppNameReturnsNameOfApp()
{
    QFAIL("Test this!");
}

DECLARE_TEST(SteamAppManifestParserTest)
#include "SteamAppManifestParserTest.moc"
