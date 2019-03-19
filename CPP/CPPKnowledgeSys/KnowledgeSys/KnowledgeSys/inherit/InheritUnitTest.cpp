#include "InheritUnitTest.h"
#include "ProtectedMessageHandler.h"
#include "PublicMessageHandler.h"

void InheritUnitTest::PrivateInherit(void)
{
	PrivateMessageHandler* p = new PrivateMessageHandler("UNIT TEST");
	p->sendMessages("Private Inherit Unit Test");
	//int status = p->processStatus;
	delete p;
	p = NULL;
}

void InheritUnitTest::ProtectedInherit(void)
{
	ProtectedMessageHandler* p = new ProtectedMessageHandler("PROTECTED UNIT TEST");
	//p->sendMessages("Protected Inherit Unit Test");
	//std::cout << p->processStatus << std::endl;
	//std::cout << p->contact << std::endl;
	delete p;
	p = NULL;
}

void InheritUnitTest::PublicInherit(void)
{
	PublicMessageHandler* p = new PublicMessageHandler("PUBLIC UNIT TEST");
	p->sendMessages("Pubic Inherit Unit Test");
	std::cout << p->processStatus << std::endl;
	//std::cout << p->contact << std::endl;
	delete p;
	p = NULL;
}

