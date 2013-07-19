#include "SteamAppDirectorySelector.h"
#include "SteamAppListItem.h"
#include "SteamAppListModel.h"
#include <QFileDialog>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QWidget>


namespace
{
#ifdef Q_OS_LINUX
    const QString DEFAULT_DIRECTORY = QDir::homePath() + "/.steam/steam/SteamApps";

#elif defined Q_OS_WIN
    const QString DEFAULT_DIRECTORY = "C:\\Program Files\\Steam\\SteamApps\\";

#elif defined Q_OS_MAC
    const QString DEFAULT_DIRECTORY = QDir::homePath() + "/Library/Application Support/Steam/SteamApps/";

#else
    const QString DEFAULT_DIRECTORY = QDir::homePath();
#endif
}


SteamAppDirectorySelector::SteamAppDirectorySelector(QLineEdit* text, QListView* list, QWidget* parent)
    : Parent(parent),
      AppDir(text),
      ListView(list)
{
    qRegisterMetaType<QList<QSharedPointer<SteamAppListItem> > >("QList<QSharedPointer<SteamAppListItem> >");

    AppDir->setText(DEFAULT_DIRECTORY);
    Refresh();
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
        QString appDirName = QFileDialog::getExistingDirectory(Parent, tr("Open SteamApps Folder"), AppDir->text(),
                                   QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if (appDirName != AppDir->text())
        {
            AppDir->setText(appDirName);
        }
        Refresh();
    }
}

void SteamAppDirectorySelector::Refresh()
{
    ListView->setModel(new SteamAppListModel(GetGameList(), Parent));
    emit AppDirChanged(AppDir->text());
}

QList<QSharedPointer<SteamAppListItem> > SteamAppDirectorySelector::GetGameList()
{
    QList<QSharedPointer<SteamAppListItem> > gameList;
    if (NULL != AppDir && !AppDir->text().isEmpty())
    {
        QDir appDir(AppDir->text());
        foreach(const QString& appName, appDir.entryList(QStringList("appmanifest_*.acf")))
        {
            gameList << QSharedPointer<SteamAppListItem>(new SteamAppListItem(QString("%1/%2").arg(appDir.absolutePath()).arg(appName)));
        }
    }
    return gameList;
}

void SteamAppDirectorySelector::MoveSelectedApps()
{
    if (NULL != ListView->model())
    {
        MoveAppList(ListView->selectionModel()->selectedIndexes());
    }
}

void SteamAppDirectorySelector::MoveAllApps()
{
    QAbstractItemModel* model = ListView->model();
    if (NULL != model)
    {
        QModelIndexList apps;
        for (int i=0; i<model->rowCount(); ++i)
        {
            apps << model->index(i, 0);
        }

        MoveAppList(apps);
    }
}

void SteamAppDirectorySelector::MoveAppList(const QModelIndexList &indices)
{
    SteamAppListModel* model = dynamic_cast<SteamAppListModel*>(ListView->model());
    if (NULL != model)
    {
        QList<QSharedPointer<SteamAppListItem> > apps;
        foreach (const QModelIndex& idx, indices)
        {
            apps << model->app(idx);
        }

        if (!apps.empty())
        {
            emit MoveApps(apps);
        }
    }
}
