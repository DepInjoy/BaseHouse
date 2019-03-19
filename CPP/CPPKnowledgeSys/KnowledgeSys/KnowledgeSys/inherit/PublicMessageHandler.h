#pragma once
#include "MessageHandler.h"

class PublicMessageHandler : public MessageHandler
{
public:
	PublicMessageHandler(std::string id);
	~PublicMessageHandler();
};

