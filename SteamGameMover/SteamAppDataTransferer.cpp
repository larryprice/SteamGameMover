#include "SteamAppDataTransferer.h"

SteamAppDataTransferer::SteamAppDataTransferer(QObject *parent)
    : QObject(parent),
      LeftDir(),
      RightDir()
{
}


SteamAppDataTransferer::~SteamAppDataTransferer()
{
}

void SteamAppDataTransferer::SetLeftDir(const QString& dirName)
{
    LeftDir = dirName;
}

QString SteamAppDataTransferer::GetLeftDir() const
{
    return LeftDir;
}

void SteamAppDataTransferer::SetRightDir(const QString& dirName)
{
    RightDir = dirName;
}

QString SteamAppDataTransferer::GetRightDir() const
{
    return RightDir;
}
