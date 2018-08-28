#ifndef OBJFSMACTROUTINES_H
#define OBJFSMACTROUTINES_H

#include<iostream>
#include<string>


/*rutinas de accion*/
void setError(void* objectParseFSM_);
void createNewMember(void *objectParseFSM_);
void doNothing(void* objectParseFSM_);
void areBracesValid(void* objectParseFSM_);
void saveMemberName(void* objectParseFSM_);
void endFsm(void* objectParseFSM_);
void saveArrayObj(void* objectParseFSM_);
void saveObjectData(void* objectParseFSM_);
void saveStringData(void* objectParseFSM_);
void saveArrayData(void* objectParseFSM_);
void saveOthersData(void* objectParseFSM_);



/*funciones internas*/
void copyString(char*start, char*end,std::string& destination);

#endif // !OBJFSMACTROUTINES_H

