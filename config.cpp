#include "config.h"

#include <QtCore>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>


namespace koala { namespace chillin { namespace client {

Config *Config::ins = new Config();

Config::Config()
{
}

Config::~Config()
{
}

void Config::initialize(const QString &cfgPath)
{
    QString cfgAbsPath = cfgPath;
    if (cfgPath.isNull() || cfgPath == "")
        cfgAbsPath = "gamecfg.json";
    if (!QFileInfo(cfgPath).isAbsolute())
        cfgAbsPath = QCoreApplication::applicationDirPath() + "/" + cfgAbsPath;

    if (!QFileInfo(cfgAbsPath).exists())
    {
        QFile::copy(":/config/gamecfg.json", cfgAbsPath);
        QFile file(cfgAbsPath);
        file.setPermissions(
            QFile::ReadOwner | QFile::WriteOwner |
            QFile::ReadGroup | QFile::WriteGroup |
            QFile::ReadOther
        );
    }

    QFile file(cfgAbsPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString jsonData = file.readAll();
    file.close();

    ins->config = QJsonDocument::fromJson(jsonData.toUtf8()).object();
}

Config *Config::instance()
{
    return ins;
}

const QJsonObject &Config::getConfig() const
{
    return ins->config;
}

}}}
