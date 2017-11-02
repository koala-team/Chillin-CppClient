#ifndef CONFIG_H
#define CONFIG_H

#include <QJsonObject>


namespace koala { namespace chillin { namespace client {

class Config
{
public:
    static void initialize(const QString &cfgPath);
    static Config *instance();
    const QJsonObject &getConfig() const;

private:
    Config();
    ~Config();

    void parseFile(const QString &cfgPath);
    void parseArgs();

private:
    static Config *ins;
    QJsonObject config;
};

}}}

#endif // CONFIG_H
