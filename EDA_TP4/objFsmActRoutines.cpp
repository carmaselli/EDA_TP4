#include "objFsmActRoutines.h"
#include "objectParseFsm.h"

void setError(void * objectParseFSM_)
{
	//en funcion del current state y el evento recibido escribir cual fue el error
	//FALTA!
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
	while (!p2class->cursorAtEnd(&cursor[i]) && !ready)
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
		i++;
	}
	if (!ready) //si sali del while pouqe llegue al final del string
	{
		p2class->setError_(BAD_FORMAT, BAD_FORMAT_STR);
	}
	else
	{
		p2class->setCursorPos(&cursor[i]); // si sali del while y no hubo ningun error entonces seteo la nueva posicion del cursor
	}
	

}


void saveArrayObj(void * objectParseFSM_)
{
	//FALTA!
}

void saveObjectData(void * objectParseFSM_)
{
	//FALTA!!
}

void saveStringData(void * objectParseFSM_)
{
	//FALTA!!
}

void saveArrayData(void * objectParseFSM_)
{
	//FALTA!!
}

void saveOthersData(void * objectParseFSM_)
{
	//FALTA!!
}

void copyString(char * start, char * end,string& destination)
{
	while (start - end)
	{
		destination += *start++;
	}
}
