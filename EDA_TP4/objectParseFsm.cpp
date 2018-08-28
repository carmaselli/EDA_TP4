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
	if ((endOfStr = pointerToEnd(JSONstringcopy)) == NULL)
	{
		setError_(INVALID_OPENER, INVALID_OPENER_STR);
	}
	while (!fsmHasFinished() && err.error == NO_ERROR)
	{
		fsmStep(generateEvent(cursorPos));
	}
	return err.error==NO_ERROR ? true : false ;
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



char * objectParseFSM::getCursorPos() 
{
	return cursorPos;
}

void objectParseFSM::setCursorPos(char * newPos)
{
	cursorPos = newPos;
}

void objectParseFSM::createNewMember_()
{
	if (memberCount == 1 && toSave == NULL)//si es el primer miembro uso malloc
	{
		toSave = (JSONmember*)malloc(1*sizeof(JSONmember));
		if (toSave == NULL)
		{
			setError_(NO_MEMORY, NO_MEM_STR);
		}
		else
		{
			toSave[memberCount-1] = tempMember;
		}
	}
	else if (memberCount > 1 && toSave != NULL)//si ya hay otros uso realloc
	{
		toSave =(JSONmember*) realloc(toSave,memberCount*sizeof(JSONmember));
		if (toSave == NULL)
		{
			setError_(NO_MEMORY, NO_MEM_STR);
		}
		else
		{
			toSave[memberCount-1] = tempMember;
		}
	}
	
}

event_t objectParseFSM::getCurrentEvent()
{
	return event_;
}

JSONmember * objectParseFSM::getTempMember()
{
	return &tempMember;
}

bool objectParseFSM::cursorAtEnd(char * cursorPos_)
{
	return endOfStr-cursorPos_==0 ? true:false;
}

JSONmember * objectParseFSM::getMembers()
{
	return toSave;
}



unsigned int objectParseFSM::getMemberCount()
{
	return memberCount;
}


char * objectParseFSM::pointerToEnd(char * JSONstring)
{
	bool ready = false;
	unsigned int bracketCount;
	char* returnPointer = NULL;
	if (*JSONstring == ASCII_OPENING_SQ_BRACKETS)
	{
		while (!ready)
		{
			if (*JSONstring == ASCII_OPENING_SQ_BRACKETS)
			{
				bracketCount++;
			}
			else if (*JSONstring == ASCII_CLOSING_SQ_BRACKETS)
			{
				bracketCount--;
			}
			if (bracketCount == 0)
			{
				ready = true;
			}
			JSONstring++;
		}
		returnPointer = JSONstring--;
	}
	else if (*JSONstring == ASCII_OPENING_BRACKETS)
	{
		while (!ready)
		{
			if (*JSONstring == ASCII_OPENING_BRACKETS)
			{
				bracketCount++;
			}
			else if (*JSONstring == ASCII_CLOSING_BRACKETS)
			{
				bracketCount--;
			}
			if (bracketCount == 0)
			{
				ready = true;
			}
			JSONstring++;
		}
		returnPointer = JSONstring--;
	}
	return returnPointer;
}

void objectParseFSM::fsmStep(event_t ev)
{
	//FALTA!!!!!!!!
}

event_t objectParseFSM::generateEvent(char * JSONstring)
{

	
	return event_t();
}

void objectParseFSM::setError_(errorType errorType_, const char * errorString)
{
	err.error = errorType_;
	err.errorString = std::string(errorString);
}

void objectParseFSM::freeFsmMemory()
{
	if (toSave != NULL)
	{
		free(toSave);
	}
}

