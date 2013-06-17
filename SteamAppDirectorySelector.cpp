#include "SteamAppDirectorySelector.h"
#include "SteamAppListItem.h"
#include "SteamAppListModel.h"
#include <QFileDialog>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QWidget>

SteamAppDirectorySelector::SteamAppDirectorySelector(QLineEdit* text, QListView* list, QWidget* parent)
    : Parent(parent),
      AppDir(text),
      ListView(list)
{
}

SteamAppDirectorySelector::~SteamAppDirectorySelector()
{
    Parent = NULL;
    AppDir = NULL;
    ListView = NULL;
}

void SteamAppDirectorySelector::OpenFileDialog()
{
    if (NULL != AppDir && NULL != ListView)
    {
        QString appDirName = QFileDialog::getExistingDirectory(Parent, tr("Open Directory"), QString(),
                                                        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        AppDir->setText(appDirName);

        Refresh();
    }
}

void SteamAppDirectorySelector::Refresh()
{
//    QStringList gameList = GetGameList();
//    QAbstractItemModel* itemModel = ListView->model();
//    for (int i = 0; i < itemModel->rowCount(); i++)
//    {
//        itemModel->
//    }

    ListView->setModel(new SteamAppListModel(GetGameList(), Parent));
}

QList<QSharedPointer<SteamAppListItem> > SteamAppDirectorySelector::GetGameList()
{
    QList<QSharedPointer<SteamAppListItem> > gameList;
    if (NULL != AppDir && !AppDir->text().isEmpty())
    {
        QDir appDir(AppDir->text());
        foreach(QString appName, appDir.entryList(QStringList("appmanifest_*.acf")))
        {
            gameList << QSharedPointer<SteamAppListItem>(new SteamAppListItem(appName));
        }
    }
    return gameList;
}
