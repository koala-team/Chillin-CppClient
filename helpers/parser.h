#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <map>
#include <exception>

#include "messages.h"


namespace koala { namespace chillin { namespace client {

class ParsedMessage;

class Parser
{
public:
    Parser();
    ~Parser();

    std::string encode(const ks::KSObject *message) const;
    ParsedMessage *decode(const std::string &data) const;
};


class ParseException : public std::exception
{
private:
    std::string message;

public:
    ParseException(const std::string &typeName)
    {
        message = "undefiend type '" + typeName + "'";
    }

    const char *what() const throw()
    {
        return message.c_str();
    }
};


struct ParsedMessage
{
    ks::KSObject *message = 0;

    ~ParsedMessage();
};


class KSObjectFactory
{
public:
    static KSObjectFactory *instance();
    ks::KSObject *create(const std::string &typeName);
    void destroy(ks::KSObject *obj);

private:
    KSObjectFactory();
    ~KSObjectFactory();

private:
    static KSObjectFactory *ins;
    std::map<ks::KSObject*, int> ids;
};

}}}

#endif // PARSER_H
