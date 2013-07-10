#include "AutoTest.h"

#include "../SteamGameMover/SteamAppDataTransferer.h"
#include "../SteamGameMover/SteamAppListItem.h"
#include "SteamAppListItemFake.h"

#include <QDirIterator>
#include <QSignalSpy>

class SteamAppDataTransfererTest: public QObject
{
    Q_OBJECT

private:
    static const QString TEST_DIR;
    static const QString TEST_LEFTDIR;
    static const QString TEST_RIGHTDIR;

    bool CopyTestDataTo(const QString& destName) const;
    SteamAppDataTransferer CreateTransfererForMovingApps() const;

private slots:
    void SetsLeftDir();
    void SetsRightDir();
    void MoveAppsLeftToRightDoesNothingWhenAppsListIsEmpty();
    void MoveAppsLeftToRightMovesAppsInList();
    void MoveAppsRightToLeftDoesNothingWhenAppsListIsEmpty();
    void MoveAppsRightToLeftMovesAppsInList();
};

const QString SteamAppDataTransfererTest::TEST_DIR(QDir::currentPath() + "/TestData/");
const QString SteamAppDataTransfererTest::TEST_LEFTDIR(QDir::currentPath() + "/TestData/TestLeft/");
const QString SteamAppDataTransfererTest::TEST_RIGHTDIR(QDir::currentPath() + "/TestData/TestRight/");

bool SteamAppDataTransfererTest::CopyTestDataTo(const QString& destName) const
{
    bool success = true;

    QDir sourceDir(TEST_DIR);
    if (sourceDir.exists())
    {
        QDir destDir(destName);
        QDirIterator iterator(sourceDir.absolutePath(), QDirIterator::Subdirectories);
        while (iterator.hasNext())
        {
            iterator.next();
            if (!iterator.fileInfo().isDir())
            {
                QFileInfo fileInfo = iterator.fileInfo();
                QString relevantPath = fileInfo.absolutePath().replace(sourceDir.absolutePath(), destDir.absolutePath());
                QString destFile = fileInfo.absoluteFilePath().replace(sourceDir.absolutePath(), destDir.absolutePath());

                if (!sourceDir.mkpath(relevantPath) || !QFile::copy(fileInfo.absoluteFilePath(), destFile))
                {
                    success = false;
                    break;
                }
            }
        }
    }
    else
    {
        success = false;
    }

    return success;
}

SteamAppDataTransferer SteamAppDataTransfererTest::CreateTransfererForMovingApps() const
{
    SteamAppDataTransferer transferer;
    transferer.SetLeftDir(TEST_LEFTDIR);
    transferer.SetRightDir(TEST_RIGHTDIR);
    QDir leftDir(TEST_LEFTDIR);
    leftDir.removeRecursively();
    QDir rightDir(TEST_RIGHTDIR);
    rightDir.removeRecursively();

    return transferer;
}

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

void SteamAppDataTransfererTest::MoveAppsLeftToRightDoesNothingWhenAppsListIsEmpty()
{
    SteamAppDataTransferer transferer = CreateTransfererForMovingApps();
    QVERIFY2(CopyTestDataTo(TEST_LEFTDIR), "Copying TestData failed");

    QSignalSpy signalSpy(&transferer, SIGNAL(CopyFinished()));
    QVERIFY(signalSpy.isValid());
    QList<QSharedPointer<SteamAppListItem> > apps;
    transferer.MoveAppsLeftToRight(apps);

    QDir rightDir(TEST_RIGHTDIR);
    if (rightDir.exists())
    {
        QCOMPARE(2, rightDir.entryList().count());
    }
    QCOMPARE(1, signalSpy.count());
}

void SteamAppDataTransfererTest::MoveAppsLeftToRightMovesAppsInList()
{
    SteamAppDataTransferer transferer = CreateTransfererForMovingApps();
    QVERIFY2(CopyTestDataTo(TEST_LEFTDIR), "Copying TestData failed");

    QSignalSpy signalSpy(&transferer, SIGNAL(CopyFinished()));
    QVERIFY(signalSpy.isValid());

    QDir leftDir(TEST_LEFTDIR);
    QFileInfoList appFiles = leftDir.entryInfoList(QDir::Files);
    QVERIFY(2 < appFiles.count());
    SteamAppListItemFake fake1(appFiles[0].absoluteFilePath());
    fake1.SubInstallDir(TEST_DIR, TEST_LEFTDIR);
    SteamAppListItemFake fake2(appFiles[1].absoluteFilePath());
    fake2.SubInstallDir(TEST_DIR, TEST_LEFTDIR);
    QSharedPointer<SteamAppListItem> app1(new SteamAppListItemFake(fake1));
    QSharedPointer<SteamAppListItem> app2(new SteamAppListItemFake(fake2));
    QList<QSharedPointer<SteamAppListItem> > apps;
    apps << app1;
    apps << app2;
    transferer.MoveAppsLeftToRight(apps);

    QDir rightDir(TEST_RIGHTDIR);
    QCOMPARE(5, rightDir.entryList().count());
    QCOMPARE(1, signalSpy.count());
}

void SteamAppDataTransfererTest::MoveAppsRightToLeftDoesNothingWhenAppsListIsEmpty()
{
    SteamAppDataTransferer transferer = CreateTransfererForMovingApps();
    QVERIFY2(CopyTestDataTo(TEST_RIGHTDIR), "Copying TestData failed");

    QSignalSpy signalSpy(&transferer, SIGNAL(CopyFinished()));
    QVERIFY(signalSpy.isValid());
    QList<QSharedPointer<SteamAppListItem> > apps;
    transferer.MoveAppsRightToLeft(apps);

    QDir leftDir(TEST_LEFTDIR);
    if (leftDir.exists())
    {
        QCOMPARE(2, leftDir.entryList().count());
    }
    QCOMPARE(1, signalSpy.count());
}

void SteamAppDataTransfererTest::MoveAppsRightToLeftMovesAppsInList()
{
    SteamAppDataTransferer transferer = CreateTransfererForMovingApps();
    QVERIFY2(CopyTestDataTo(TEST_RIGHTDIR), "Copying TestData failed");

    QSignalSpy signalSpy(&transferer, SIGNAL(CopyFinished()));
    QVERIFY(signalSpy.isValid());

    QDir rightDir(TEST_RIGHTDIR);
    QFileInfoList appFiles = rightDir.entryInfoList(QDir::Files);
    QVERIFY(2 < appFiles.count());
    SteamAppListItemFake fake1(appFiles[0].absoluteFilePath());
    fake1.SubInstallDir(TEST_DIR, TEST_RIGHTDIR);
    SteamAppListItemFake fake2(appFiles[1].absoluteFilePath());
    fake2.SubInstallDir(TEST_DIR, TEST_RIGHTDIR);
    QSharedPointer<SteamAppListItem> app1(new SteamAppListItemFake(fake1));
    QSharedPointer<SteamAppListItem> app2(new SteamAppListItemFake(fake2));
    QList<QSharedPointer<SteamAppListItem> > apps;
    apps << app1;
    apps << app2;
    transferer.MoveAppsRightToLeft(apps);

    QDir leftDir(TEST_LEFTDIR);
    QCOMPARE(5, leftDir.entryList().count());
    QCOMPARE(1, signalSpy.count());
}

DECLARE_TEST(SteamAppDataTransfererTest)
#include "SteamAppDataTransfererTest.moc"
