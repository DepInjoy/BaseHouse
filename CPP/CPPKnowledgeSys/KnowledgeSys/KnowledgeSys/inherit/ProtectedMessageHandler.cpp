#include "ProtectedMessageHandler.h"

ProtectedMessageHandler::ProtectedMessageHandler(std::string id)
	: MessageHandler(id)
{
	std::cout << "Construct ProtectedMessageHandler " << std::endl;
	sendMessages("Haaahahahaahhhhhhhhhhhh");
}


ProtectedMessageHandler::~ProtectedMessageHandler()
{
	std::cout << "Deconstruct ProtectedMessageHandler " << std::endl;
}
