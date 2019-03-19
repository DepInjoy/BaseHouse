#include "MessageHandler.h"

MessageHandler::MessageHandler(std::string id):
	uuid(id)
{
	std::cout << "Construct MessageHandler " << std::endl;
}

MessageHandler::MessageHandler(void) :
	uuid("Default")
{
	std::cout << "Construct MessageHandler with default id" << std::endl;
}
MessageHandler::~MessageHandler()
{
	std::cout << "Deconstruct MessageHandler " << std::endl;
}

int MessageHandler::sendMessages(std::string msg)
{
	std::cout << "MessageHandler:: Send message " << msg << std::endl;
	return 0;
}

void MessageHandler::handleMessage(std::string msg)
{
	std::cout << "MessageHandler:: Handle message " << msg << std::endl;
}