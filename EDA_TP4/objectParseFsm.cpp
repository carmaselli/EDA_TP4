#include "objectParseFsm.h"

objectParseFSM::objectParseFSM(char * JSONstring)
{
	toSave = NULL;
	itself = NULL;
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

void objectParseFSM::setItselfPointer(objectParseFSM * itself_)
{
	itself = itself_;
}

void objectParseFSM::cleanWhitespace(char * cursor)
{
	while (*cursor == ' ' || *cursor == '\t' || *cursor == '\n' && !cursorAtEnd(cursor))
	{
		cursor++;
	}
	setCursorPos(cursor);
}

bool objectParseFSM::isBool(char * cursor)
{
	bool ready = false;
	bool error = false;
	const char *boolStr[] = { "true", "false" };
	int i,j;
	for (i = 0;i<sizeof(boolStr)/sizeof(boolStr[1]) && !ready ;i++)
	{
		for ( j=0;!ready && !error; j++)
		{
			int d = boolStr[i][j] - cursor[j];
			if (d != 0)
			{
				error = true;
			}
			else if (!boolStr[i][j+1])//si son el mismo string y el siguiente del interno es el terminador son iguales
			{
				ready = true;
			}
		}
	}
	
	
	return  ready && (cursor[j] == ' ' || cursor[j] == '\t' || cursor[j] == '\n');
}

bool objectParseFSM::isNull(char * cursor)
{
	bool ready = false;
	bool error = false;
	const char nullStr[] = "null";
	int  j;
	for(j = 0; !ready && !error; j++)
	{
		int d = nullStr[j] - cursor[j];
		if (d != 0)
		{
			error = true;
		}
		else if (!nullStr[j + 1])//si son el mismo string y el siguiente del interno es el terminador son iguales
		{
			ready = true;
		}
	}
	return  ready && (cursor[j] == ' ' || cursor[j] == '\t' || cursor[j] == '\n'||cursor[j] == ',');
}




bool objectParseFSM::isNumber(char * cursor)
{
	int i = 0;
	while (!cursorAtEnd(&cursor[i]), cursor[i] >= '0' && cursor[i] <= '9' || cursor[i] == '.' || cursor[i] == 'e' || cursor[i] == 'E' || cursor[i] == '+' || cursor[i] == '-')
	{
		i++;
	}

	return (cursor[i] == ' ' || cursor[i] == '\t' || cursor[i] == '\n' || cursor[i] == ',');
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
	if (itself != NULL)
	{
		FsmTable[currentState][ev.eventType_].actionRoutine(itself);
		currentState = FsmTable[currentState][ev.eventType_].nextState;
	}
	else
	{
		setError_(POINTER_NOT_SET, POINTER_NOT_SET_STR);
	}
}

event_t objectParseFSM::generateEvent(char * JSONstring)
{
	event_t temp;
	cleanWhitespace(cursorPos);
	switch (*cursorPos)
	{
	case ASCII_OPENING_BRACKETS:
		temp.eventType_ = OPENING_BRACKETS;
		temp.eventChar = *cursorPos;
		break;
	case ASCII_CLOSING_BRACKETS:
		temp.eventType_ = CLOSING_BRACKETS;
		temp.eventChar = *cursorPos;
		break;
	case ASCII_QUOTATION:
		temp.eventType_ = QUOTATION;
		temp.eventChar = *cursorPos;
		break;
	case ASCII_COLON:
		temp.eventType_ = COLON;
		temp.eventChar = *cursorPos;
		break;
	case ASCII_OPENING_SQ_BRACKETS:
		temp.eventType_ = OPENING_SQ_BRACKETS;
		temp.eventChar = *cursorPos;
		break;
	case ASCII_CLOSING_SQ_BRACKETS:
		temp.eventType_ = CLOSING_SQ_BRACKETS;
		temp.eventChar = *cursorPos;
		break;
	case ASCII_COMMA:
		temp.eventType_ = COMMA;
		temp.eventChar = *cursorPos;
		break;
	default:
		if (isBool(cursorPos))//si es numero bool o null
		{
			temp.eventType_ = BOOL;
			temp.eventChar = *cursorPos;			
		}
		else if (isNull(cursorPos))
		{
			temp.eventType_ = NULL_;
			temp.eventChar = *cursorPos;
		}
		else if (isNumber(cursorPos))
		{
			temp.eventType_ = NUMBER;
			temp.eventChar = *cursorPos;
		}
		else
		{
			setError_(UNKNOWN_EVENT, UNKNOWN_EVENT_STR);
		}
		break;
	}
	return temp;
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


