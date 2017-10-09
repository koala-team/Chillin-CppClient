#ifndef LOGGER_H
#define LOGGER_H

#include <QString>


namespace koala { namespace chillin { namespace client {

class Logger
{
public:
    static Logger *instance();

    void log(const QString &text);
    void warn(const QString &text);
    void err(const QString &text);
    void succeed(const QString &text);

private:
    Logger();
    ~Logger();

    void print(const QString &text);

private:
    static Logger *ins;
};

}}}

#endif // LOGGER_H
