#include "objFsmActRoutines.h"
#include "objectParseFsm.h"

void setError(void * objectParseFSM_)
{
	objectParseFSM *p2class = (objectParseFSM *)objectParseFSM_;
	p2class->setError_(1,"mal");
}

void createNewMember(void * objectParseFSM_)
{
}

void saveMemberData(void * objectParseFSM_)
{
	objectParseFSM *p2class = (objectParseFSM *)objectParseFSM_;
	switch (p2class->getCurrentEvent().eventChar)
	{
		case
	}

}

void checkMode(void * objectParseFSM_)
{
}

void doNothing(void * objectParseFSM_)
{
	//listo
}

void areBracesValid(void * objectParseFSM_)
{
}

void saveMemberName(void * objectParseFSM_)
{
}

void endFsm(void * objectParseFSM_)
{
}

void saveArrayObj(void * objectParseFSM_)
{
}
