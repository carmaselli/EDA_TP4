#include "objectParseFsm.h"

objectParseFSM::objectParseFSM(char * JSONstring)
{
}

bool objectParseFSM::fsmStartParsing(void)
{
	return false;
}

error_t objectParseFSM::getError()
{
	return error_t();
}

string objectParseFSM::getObjName()
{
	return string();
}

JSONmember * objectParseFSM::getMemberArray()
{
	return nullptr;
}


void objectParseFSM::fsmStep(event_t ev)
{
}

event_t objectParseFSM::generateEvent(char * JSONstring)
{
	return event_t();
}

void objectParseFSM::setError_(int errorType, const char * errorString)
{
}

