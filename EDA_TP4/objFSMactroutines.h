#ifndef OBJFSMACTROUTINES_H
#define OBJFSMACTROUTINES_H

/*rutinas de accion*/
	 //ver que mandar en el puntero ahora que no necesitan nada
void setError(void* objectParseFSM_);
void createNewMember(void *objectParseFSM_);
void saveMemberData(void* objectParseFSM_);
void checkMode(void* objectParseFSM_);
void doNothing(void* objectParseFSM_);
void areBracesValid(void* objectParseFSM_);
void saveMemberName(void* objectParseFSM_);
void endFsm(void* objectParseFSM_);
void saveArrayObj(void* objectParseFSM_);

#endif // !OBJFSMACTROUTINES_H

