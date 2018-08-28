#include "objFsmActRoutines.h"
#include "objectParseFsm.h"

void setError(void * objectParseFSM_)
{
	//en funcion del current state y el evento recibido escribir cual fue el error
}

void createNewMember(void * objectParseFSM_)
{
	objectParseFSM *p2class = (objectParseFSM *)objectParseFSM_;
	p2class->createNewMember_();
}


void doNothing(void * objectParseFSM_)
{
	//listo
}

void areBracesValid(void * objectParseFSM_)
{
	objectParseFSM *p2class = (objectParseFSM *)objectParseFSM_;
	if (p2class->getMemberCount() > 0)
	{
		p2class->setError_(BRACES_AFTER_COMMA, BRACES_AF_COMMA_STR); //si memberCount es mayor que 0 significa que luego de una comma enviaron una llave
	}
	//si es 0 entonces era un objeto vacio y no hago nada(termina fsm
}

void saveMemberName(void * objectParseFSM_)
{
	objectParseFSM *p2class = (objectParseFSM *)objectParseFSM_;
	char* cursor = p2class->getCursorPos();
	bool ready = false;
	int i = 1;
	while (!p2class -> cursorAtEnd(cursor) && !ready)
	{
		if (cursor[i] == ASCII_QUOTATION)
		{
			if (i != 1)
			{
				copyString(cursor, &cursor[i], p2class->getTempMember()->name);
				
			}
			else
			{
				p2class->setError_(NO_NAME, NO_NAME_STR);
			}
			ready = true;
		}
	}
	if (!ready) //si sali del while pouqe llegue al final del string
	{
		p2class->setError_(BAD_FORMAT, BAD_FORMAT_STR);
	}

}

void endFsm(void * objectParseFSM_)
{
}

void saveArrayObj(void * objectParseFSM_)
{
}

void saveObjectData(void * objectParseFSM_)
{
}

void saveStringData(void * objectParseFSM_)
{
}

void saveArrayData(void * objectParseFSM_)
{
}

void saveOthersData(void * objectParseFSM_)
{
}

void copyString(char * start, char * end,string& destination)
{
	while (start - end)
	{
		destination += *start;
	}
}
