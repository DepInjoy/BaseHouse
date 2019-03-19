#pragma once
#include "MessageHandler.h"
class PrivateMessageHandler : private MessageHandler
{
public:
	PrivateMessageHandler(std::string id);
	~PrivateMessageHandler();
	int sendMessages(std::string msg);
};