#ifndef SGM_DIRECTORY_SELECTOR_H
#define SGM_DIRECTORY_SELECTOR_H

#include <QObject>
#include <QSharedDataPointer>

class QLineEdit;
class QListView;
class QPushButton;
class QWidget;

class SGMDirectorySelector : public QObject
{
    Q_OBJECT

public:
    SGMDirectorySelector(QLineEdit* text, QListView* list, QWidget *parent);
    virtual ~SGMDirectorySelector();

public slots:
    void OpenFileDialog();
    void Refresh();

private:
    QStringList GetGameList();

    QWidget* Parent;
    QLineEdit* AppDir;
    QListView* ListView;
};

#endif // SGM_DIRECTORY_SELECTOR_H
