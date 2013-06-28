#ifndef SGM_DIRECTORY_SELECTOR_H
#define SGM_DIRECTORY_SELECTOR_H

#include <QModelIndexList>
#include <QObject>

class SteamAppListItem;

class QLineEdit;
class QListView;
class QPushButton;
class QWidget;

class SteamAppDirectorySelector : public QObject
{
    Q_OBJECT

public:
    SteamAppDirectorySelector(QLineEdit* text, QListView* list, QWidget *parent);
    virtual ~SteamAppDirectorySelector();

signals:
    void AppDirChanged(const QString& dirName);
    void MoveApps(const QList<QSharedPointer<SteamAppListItem> > apps);

public slots:
    void OpenFileDialog();
    void Refresh();
    void MoveSelectedApps();
    void MoveAllApps();

private:
    QList<QSharedPointer<SteamAppListItem> > GetGameList();
    void MoveAppList(const QModelIndexList &indices);

    QWidget* Parent;
    QLineEdit* AppDir;
    QListView* ListView;
};

#endif // SGM_DIRECTORY_SELECTOR_H
