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
    ins->parseFile(cfgPath);
    ins->parseArgs();
}

void Config::parseFile(const QString &cfgPath)
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

void Config::parseArgs()
{
    QRegExp regex("config\\.(.+)(\\.(.+))*\\=(.+)?");

    for (auto arg : QCoreApplication::arguments())
        if (regex.indexIn(arg) > -1)
        {
            auto key = regex.cap(1);
            auto value = regex.cap(4);

            if (key == "net.host")
            {
                QJsonObject tmp = ins->config["net"].toObject();
                tmp.insert("host", value);
                ins->config.insert("net", tmp);
            }
            else if (key == "net.port")
            {
                QJsonObject tmp = ins->config["net"].toObject();
                tmp.insert("port", value.toInt());
                ins->config.insert("net", tmp);
            }
            else if (key == "ai.agent_name")
            {
                QJsonObject tmp = ins->config["ai"].toObject();
                tmp.insert("agent_name", value);
                ins->config.insert("ai", tmp);
            }
            else if (key == "ai.team_nickname")
            {
                QJsonObject tmp = ins->config["ai"].toObject();
                tmp.insert("team_nickname", value);
                ins->config.insert("ai", tmp);
            }
            else if (key == "ai.token")
            {
                QJsonObject tmp = ins->config["ai"].toObject();
                tmp.insert("token", value);
                ins->config.insert("ai", tmp);
            }
        }
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
