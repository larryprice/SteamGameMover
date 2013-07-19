#include "AutoTest.h"

#include "../SteamGameMover/AppTransferError.h"
#include "SteamAppListItemFake.h"

class AppTransferErrorTest: public QObject
{
    Q_OBJECT
private slots:
    void GetAppReturnsApp();
    void GetErrorMessageReturnsProperlyFormedMessage();
};

void AppTransferErrorTest::GetAppReturnsApp()
{
    QSharedPointer<SteamAppListItem> app(new SteamAppListItemFake());
    AppTransferError error(app, "");

    QCOMPARE(error.GetApp(), app);
}

void AppTransferErrorTest::GetErrorMessageReturnsProperlyFormedMessage()
{
    QString appName("Test");
    QString errorString("This is a test error");
    SteamAppListItemFake* fake = new SteamAppListItemFake();
    fake->SetName(appName);
    QSharedPointer<SteamAppListItem> app(fake);

    AppTransferError error(app, errorString);

    QCOMPARE(error.GetErrorMessage(), QString("Test: This is a test error"));
}

DECLARE_TEST(AppTransferErrorTest)
#include "AppTransferErrorTest.moc"
