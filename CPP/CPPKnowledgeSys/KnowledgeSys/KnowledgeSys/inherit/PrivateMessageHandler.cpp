#include "PrivateMessageHandler.h"
PrivateMessageHandler::PrivateMessageHandler(std::string id): 
	MessageHandler(id)
{
	std::cout << "Construct PrivateMessageHandler " << std::endl;
}


PrivateMessageHandler::~PrivateMessageHandler()
{
	std::cout << "Deconstruct PrivateMessageHandler " << std::endl;
}

int PrivateMessageHandler::sendMessages(std::string msg)
{
	std::cout << "PrivateMessageHandler:: Send message [ " << msg << " ]" << std::endl;
	return 0;
}