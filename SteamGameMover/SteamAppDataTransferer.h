#ifndef STEAMAPPDATATRANSFERER_H
#define STEAMAPPDATATRANSFERER_H

#include <QObject>

class SteamAppDataTransferer : public QObject
{
    Q_OBJECT
public:
    SteamAppDataTransferer(QObject *parent = 0);
    virtual ~SteamAppDataTransferer();

    QString GetLeftDir() const;
    QString GetRightDir() const;

public slots:
    void SetLeftDir(const QString& dirName);
    void SetRightDir(const QString& dirName);

private:
    QString LeftDir;
    QString RightDir;
};

#endif // STEAMAPPDATATRANSFERER_H
