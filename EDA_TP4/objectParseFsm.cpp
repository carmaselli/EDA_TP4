#include "objectParseFsm.h"

objectParseFSM::objectParseFSM(char * JSONstring)
{
	toSave = NULL;
	err.error = NO_ERROR;
	err.errorString = "NO_ERROR DEFAULT";
	currentState = WAITING_FOR_OBJ_OPENER;
	JSONstringcopy = JSONstring;
	cursorPos = JSONstring;
	memberCount = NO_MEMBERS;
	FSMdone = false;
}

bool objectParseFSM::fsmStartParsing(void)
{
	while (!fsmHasFinished())
	{
		fsmStep(generateEvent(cursorPos));
	}
	return false;
}

error_t objectParseFSM::getError()
{
	return err;
}


stateType objectParseFSM::getCurrentState()
{
	return currentState;
}

bool objectParseFSM::fsmHasFinished()
{
	return FSMdone;
}

void objectParseFSM::setCursorPos(char * newPos)
{
	cursorPos = newPos;
}

void objectParseFSM::createNewMember_(JSONmember newMember)
{
	if (memberCount == 0 && toSave == NULL)//si es el primer miembro uso malloc
	{
		toSave = (JSONmember*)malloc(1*sizeof(JSONmember));
		if (toSave == NULL)
		{
			setError_(NO_MEMORY, NO_MEM_STR);
		}
	}
	else if (memberCount > 1 && toSave != NULL)//si ya hay otros uso realloc
	{
		toSave =(JSONmember*) realloc(toSave,memberCount*sizeof(JSONmember));
		if (toSave == NULL)
		{
			setError_(NO_MEMORY, NO_MEM_STR);
		}
	}
}

event_t objectParseFSM::getCurrentEvent()
{
	return event_;
}

JSONmember * objectParseFSM::getMembers()
{
	return toSave;
}



unsigned int objectParseFSM::getMemberCount()
{
	return memberCount;
}


void objectParseFSM::fsmStep(event_t ev)
{
	//FALTA!!!!!!!!
}

event_t objectParseFSM::generateEvent(char * JSONstring)
{

	//FALTA!!!!!
	return event_t();
}

void objectParseFSM::setError_(errorType errorType_, const char * errorString)
{
	err.error = errorType_;
	err.errorString = std::string(errorString);
}

void objectParseFSM::freeFsmMemory()
{
	free(toSave);
}

