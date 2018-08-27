#ifndef OBJECTPARSEFSM_H
#define OBJECTPARSEFSM_H


#include<iostream>
#include<string>
#include"JSONobject.h"
#include "objFsmActRoutines.h"



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
	void(*actionRoutine)(void*);
	int nextState;
}cell_t;

typedef enum {WAITING_FOR_OBJ_OPENER,WAITING_FOR_QUOTE_ORBRACE,WAITING_FOR_MEMBER,WAITING_FOR_OBJ_CLOSER_ORNEXT,END} stateType; 
#define STATE_COUNT 5


typedef enum { OPENING_BRACKETS, CLOSING_BRACKETS,QUOTATION, COLON,OPENING_SQ_BRACKETS,CLOSING_SQ_BRACKETS,COMMA,NULL_,BOOL,NUMBER,END_OF_FILE} eventType;
#define EVENT_COUNT 11


typedef enum{IN_STRING, IN_INNER_OBJ, IN_ARRAY, OUTSIDE}readingPlace;

class objectParseFSM
{
public:
	objectParseFSM(char* JSONstring); //constructor
	bool fsmStartParsing();//empieza a parsear un string en busca de objetos(esta es la fsm)
	error_t getError();  //devuelve una estructura error con el tipo de error ocurrido, NO_ERROR en caso de no haber error
	string getObjName(); //devuelve el nombre del objeto recibido
	stateType getCurrentState();


	JSONmember* getMembers(); //devuelve el puntero al arreglo de miembros
	unsigned int getMemberCount();
	void setError_(int errorType, const char* errorString);//para facilitar el seteo del error dentro de la fsm


private:
	string objName;//aqui se guardara el nombre del objeto, si es un arreglo se guarda "null"
	JSONmember* toSave; //arreglo que se crea dinamicamente con todos los miembros del objeto encontrados, se envia luego al programa principal
	error_t err;
	event_t event_;
	readingPlace readingPlace_;
	JSONmember tempMember;//lugar donde se guardan los atributos de cada miembro a medida que se lee la informacion
	stateType currentState;
	
	char *cursorPos; //posicion del cursor en el string
	unsigned int memberCount;//lleva la cuenta de la cantidad de campos encontrados


	
	void fsmStep(event_t ev);//realiza un paso de la fsm
	event_t generateEvent(char* JSONstring);//genera a partir de los strings recibidos los eventos para la fsm
	

	


	/*TABLA DE ESTADOS DE LA FSM*/
	cell_t FsmTable[STATE_COUNT][EVENT_COUNT] = 
	{
	{{doNothing,WAITING_FOR_QUOTE_ORBRACE},{setError,END},{setError,END},{setError,END},{saveArrayObj,END},{setError,END},{setError,END},{setError,END},{setError,END},{setError,END},{setError,END}},\
	{{setError,END},{areBracesValid,END},{saveMemberName,WAITING_FOR_MEMBER}, {setError,END}, {setError,END}, {setError,END}, {setError,END}, {setError,END}, {setError,END}, {setError,END}, {setError,END}} ,\
	{{saveMemberData, WAITING_FOR_OBJ_CLOSER_ORNEXT},{setError,END},{saveMemberData,WAITING_FOR_OBJ_CLOSER_ORNEXT},{setError,END},{saveMemberData,WAITING_FOR_OBJ_CLOSER_ORNEXT},{setError,END},{setError,END},{saveMemberData,WAITING_FOR_OBJ_CLOSER_ORNEXT}, {saveMemberData,WAITING_FOR_OBJ_CLOSER_ORNEXT}, {saveMemberData,WAITING_FOR_OBJ_CLOSER_ORNEXT}, {setError,END}},\
	{{setError, END},{createNewMember,END},{setError,END},{setError,END},{setError,END},{setError,END},{createNewMember,WAITING_FOR_QUOTE_ORBRACE},{setError,END},{setError,END},{setError,END},{setError,END}},\
	{{setError, END},{setError,END},{setError,END},{setError,END},{setError,END},{setError,END},{setError,END},{setError,END},{setError,END},{setError,END},{endFsm,END}} \
	};
};


#endif