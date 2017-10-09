#include "parser.h"

#include <QMetaType>

using namespace std;
using namespace ks;
using namespace ks::messages;


namespace koala { namespace chillin { namespace client {

Parser::Parser()
{
}

Parser::~Parser()
{
}

string Parser::encode(const KSObject *message) const
{
    Message msg;
    msg.type(message->name());
    msg.payload(message->serialize());
    return msg.serialize();
}

ParsedMessage *Parser::decode(const string &data) const
{
    ParsedMessage *result = new ParsedMessage();

    // fill result->message
    Message msg;
    msg.deserialize(data);
    result->message = KSObjectFactory::instance()->create(msg.type());
    result->message->deserialize(msg.payload());

    return result;
}


/////////////////////////////////////////////////////////////////
//////////////////       ParsedMessage       ////////////////////
/////////////////////////////////////////////////////////////////

ParsedMessage::~ParsedMessage()
{
    KSObjectFactory::instance()->destroy(message);
}


/////////////////////////////////////////////////////////////////
//////////////////       KSObjectFactory       //////////////////
/////////////////////////////////////////////////////////////////

#define registerType(Type) qRegisterMetaType<Type>(#Type);

KSObjectFactory *KSObjectFactory::ins = new KSObjectFactory();

KSObjectFactory::KSObjectFactory()
{
    // register messages
    registerType(JoinOfflineGame);
    registerType(JoinOnlineGame);
    registerType(ClientJoined);
    registerType(AgentJoined);
    registerType(AgentLeft);

    registerType(StartGame);
    registerType(EndGame);
    registerType(BaseSnapshot);
    registerType(RealtimeSnapshot);
    registerType(TurnbasedSnapshot);

    registerType(BaseCommand);
    registerType(RealtimeCommand);
    registerType(TurnbasedCommand);
}

KSObjectFactory::~KSObjectFactory()
{
}

KSObjectFactory *KSObjectFactory::instance()
{
    return ins;
}


KSObject *KSObjectFactory::create(const string &typeName)
{
    int id = QMetaType::type(typeName.c_str());
    if (id != QMetaType::UnknownType)
    {
        KSObject *obj = (KSObject*) QMetaType::create(id);
        ids[obj] = id;
        return obj;
    }

    throw ParseException(typeName);
}

void KSObjectFactory::destroy(ks::KSObject *obj)
{
    QMetaType::destroy(ids[obj], (void*) obj);
    ids.erase(obj);
}

}}}
