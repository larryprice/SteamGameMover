#include "SGMDirectorySelector.h"
#include "SGMListItemModel.h"
#include <QFileDialog>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QWidget>

SGMDirectorySelector::SGMDirectorySelector(QLineEdit* text, QListView* list, QWidget* parent)
    : Parent(parent),
      AppDir(text),
      ListView(list)
{
}

SGMDirectorySelector::~SGMDirectorySelector()
{
    Parent = NULL;
    AppDir = NULL;
    ListView = NULL;
}

void SGMDirectorySelector::OpenFileDialog()
{
    if (NULL != AppDir && NULL != ListView)
    {
        QString appDirName = QFileDialog::getExistingDirectory(Parent, tr("Open Directory"), QString(),
                                                        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        AppDir->setText(appDirName);

        Refresh();
    }
}

void SGMDirectorySelector::Refresh()
{
    ListView->setModel(new SGMListItemModel(GetGameList(), Parent));
}

QStringList SGMDirectorySelector::GetGameList()
{
    QStringList gameList;
    if (NULL != AppDir)
    {
        QDir appDir(AppDir->text());
        gameList = appDir.entryList(QStringList("appmanifest_*.acf"));
    }
    return gameList;
}
