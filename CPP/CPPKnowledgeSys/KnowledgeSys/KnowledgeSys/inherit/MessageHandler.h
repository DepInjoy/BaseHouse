#pragma once
#include <iostream>
#include <string>

class MessageHandler
{
public:
	MessageHandler(std::string id);
	MessageHandler();
	~MessageHandler();
	int sendMessages(std::string msg);
	int processStatus;
private:
	void handleMessage(std::string msg);
	std::string uuid;
protected:
	std::string contact;
};
