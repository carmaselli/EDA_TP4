#ifndef OBJFSMACTROUTINE_H
#define OBJFSMACTROUTINE_H

/*rutinas de accion*/
void setMode(void* objectParseFSM_);
void setError(void* objectParseFSM_);
void startMemberFSM(void *objectParseFSM_);
void saveMembers(void* objectParseFSM_);
void parseString(void* objectParseFSM_);
void parseArray(void* objectParseFSM_);
void checkMode(void* objectParseFSM_);
void doNothing(void* objectParseFSM_);
void endFsm(void* objectParseFSM_);

#endif
