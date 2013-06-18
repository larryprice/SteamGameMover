#include "SteamAppListItem.h"
#include <QFile>
#include <QRegExp>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
SteamAppListItem::SteamAppListItem(QString manifestName, QObject *parent)
    : QObject(parent),
    AppManifestFilePath(manifestName),
    Name()
{
    QFile manifest(manifestName);
    if (manifest.open(QIODevice::ReadOnly))
    {
        QTextStream manifestStream(&manifest);
        while (!manifestStream.atEnd())
        {
            QStringList lines = manifestStream.readLine().simplified().split("\" \"");
            if (lines.count() == 2 && lines.first() == "\"name")
            {
                Name = lines.last();
                Name.chop(1);
            }
        }
        manifest.close();
    }
}

QString SteamAppListItem::GetName() const
{
    return Name;
}
