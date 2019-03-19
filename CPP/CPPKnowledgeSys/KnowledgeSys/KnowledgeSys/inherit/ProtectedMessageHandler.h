#pragma once
#include "MessageHandler.h"

class ProtectedMessageHandler : protected MessageHandler
{
public:
	ProtectedMessageHandler(std::string id);
	~ProtectedMessageHandler();
};

