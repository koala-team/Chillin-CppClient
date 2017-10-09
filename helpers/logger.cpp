#include "logger.h"

#include <iostream>

using namespace std;


namespace koala { namespace chillin { namespace client {

Logger *Logger::ins = new Logger();

Logger::Logger()
{
}

Logger::~Logger()
{
}

Logger *Logger::instance()
{
    return ins;
}


void Logger::print(const QString &text)
{
    cout << text.toStdString() << endl;
}


void Logger::log(const QString &text)
{
    print(">>> " + text);
}

void Logger::warn(const QString &text)
{
    print(QString("\033[0;33m>>> %1\033[0m").arg(text));
}

void Logger::err(const QString &text)
{
    print(QString("\033[0;31m>>> %1\033[0m").arg(text));
}

void Logger::succeed(const QString &text)
{
    print(QString("\033[0;32m>>> %1\033[0m").arg(text));
}

}}}
