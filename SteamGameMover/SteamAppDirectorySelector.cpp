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
        QString appDirName = QFileDialog::getExistingDirectory(Parent, tr("Open SteamApps Folder"), QString(),
                                   QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if (appDirName != AppDir->text())
        {
            AppDir->setText(appDirName);
            emit AppDirChanged(appDirName);
        }
        Refresh();
    }
}

void SteamAppDirectorySelector::Refresh()
{
    ListView->setModel(new SteamAppListModel(GetGameList(), Parent));
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
#include <QDebug>
void SteamAppDirectorySelector::MoveSelectedApps()
{
    SteamAppListModel* model = dynamic_cast<SteamAppListModel*>(ListView->model());
    if (NULL != model)
    {
        foreach(const QModelIndex& idx, ListView->selectionModel()->selectedIndexes())
        {
            qDebug() << model->app(idx)->GetName();
        }
    }
}

void SteamAppDirectorySelector::MoveAllApps()
{
    SteamAppListModel* model = dynamic_cast<SteamAppListModel*>(ListView->model());
    if (NULL != model)
    {
        for (int i=0; i<model->rowCount(); ++i)
        {
            qDebug() << model->app(model->index(i))->GetName();
        }
    }
}
