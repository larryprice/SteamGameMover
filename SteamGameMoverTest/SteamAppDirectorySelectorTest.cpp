#include "AutoTest.h"

class SteamAppDirectorySelectorTest: public QObject
{
    Q_OBJECT
private slots:
    void ShouldBeTested();
};

void SteamAppDirectorySelectorTest::ShouldBeTested()
{
    QFAIL("Please test me!");
}

DECLARE_TEST(SteamAppDirectorySelectorTest)
#include "SteamAppDirectorySelectorTest.moc"
