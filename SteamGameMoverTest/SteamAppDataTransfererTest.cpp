#include "AutoTest.h"

#include "../SteamGameMover/SteamAppDataTransferer.h"

#include <QFile>

class SteamAppDataTransfererTest: public QObject
{
    Q_OBJECT
private slots:
    void SetsLeftDir();
    void SetsRightDir();
};

void SteamAppDataTransfererTest::SetsLeftDir()
{
    SteamAppDataTransferer transferer;
    QString testDirName = "test1";
    QVERIFY(testDirName != transferer.GetLeftDir());

    transferer.SetLeftDir(testDirName);
    QCOMPARE(transferer.GetLeftDir(), testDirName);
}

void SteamAppDataTransfererTest::SetsRightDir()
{
    SteamAppDataTransferer transferer;
    QString testDirName = "test1";
    QVERIFY(testDirName != transferer.GetRightDir());

    transferer.SetRightDir(testDirName);
    QCOMPARE(transferer.GetRightDir(), testDirName);
}

DECLARE_TEST(SteamAppDataTransfererTest)
#include "SteamAppDataTransfererTest.moc"
