#ifndef FSMCOMMON_H
#define FSMCOMMON_H

#include<iostream>
#include<string>


typedef struct
{
	int eventType;
	char eventChar;
}event_t;

typedef struct
{
	int errorType;
	std::string errorString;
}error_t;

typedef struct
{
	void(*action) (void*);
	int nextState;
}cell_t;

#endif