#ifndef OBJECTPARSEFSM_H
#define OBJECTPARSEFSM_H


#include<iostream>
#include<string>
#include"JSONobject.h"
#include "objFsmActRoutines.h"

#define ASCII_OPENING_BRACKETS '{'
#define ASCII_CLOSING_BRACKETS '}'
#define ASCII_QUOTATION '\"'
#define ASCII_COLON ':'
#define ASCII_COMMA ','
#define ASCII_OPENING_SQ_BRACKETS '['
#define ASCII_CLOSING_SQ_BRACKETS ']'
#define ASCII_NEW_LINE '\n'

#define NO_MEMBERS 0
#define NO_MEM_STR "No hay memoria disponible para crear mas campos"
#define BRACES_AF_COMMA_STR "se esperaba '\"' y se recibio '}'"
#define INVALID_OPENER_STR "El objeto no empieza con un caracter valido"
#define NO_NAME_STR "Se recibio un objeto sin nombre entre las comillas"
#define BAD_FORMAT_STR "El formato del objeto recibido es incorrecto, verificar simbolos"
#define UNKNOWN_EVENT_STR "Se recibio un caracter inesperado, el formato del objeto es incorrecto"
#define POINTER_NOT_SET_STR "No se ha seteado correctamente el puntero a la clase"
typedef enum {NO_ERROR,NO_MEMORY,BRACES_AFTER_COMMA, INVALID_OPENER,NO_NAME,BAD_FORMAT,UNKNOWN_EVENT,POINTER_NOT_SET}errorType;



typedef enum { WAITING_FOR_OBJ_OPENER, WAITING_FOR_QUOTE_ORBRACE, WAITING_FOR_MEMBER, WAITING_FOR_OBJ_CLOSER_ORNEXT, END } stateType;
#define STATE_COUNT 5


typedef enum { OPENING_BRACKETS, CLOSING_BRACKETS, QUOTATION, COLON, OPENING_SQ_BRACKETS, CLOSING_SQ_BRACKETS, COMMA, NULL_, BOOL, NUMBER,} eventType;
#define EVENT_COUNT 10


typedef enum { IN_STRING, IN_INNER_OBJ, IN_ARRAY, OUTSIDE }readingPlace;
typedef struct
{	eventType eventType_;
	char eventChar;
}event_t;

typedef struct
{
	errorType error;
	std::string errorString;
}error_t;

typedef struct
{
	void(*actionRoutine)(void*);
	stateType nextState;
}cell_t;







class objectParseFSM
{
public:
	objectParseFSM(char* JSONstring); //constructor
	bool fsmStartParsing();//empieza a parsear un string en busca de objetos(esta es la fsm)
	error_t getError();  //devuelve una estructura error con el tipo de error ocurrido, NO_ERROR en caso de no haber error
	stateType getCurrentState();
	bool fsmHasFinished();
	char* getCursorPos();
	void setCursorPos(char * newPos);
	void createNewMember_();
	event_t getCurrentEvent();
	JSONmember *getTempMember();
	bool cursorAtEnd(char* cursorPos_);
	void setItselfPointer(objectParseFSM* itself_);
	

	JSONmember* getMembers(); //devuelve el puntero al arreglo de miembros
	unsigned int getMemberCount();
	void setError_(errorType errorType_, const char* errorString);//para facilitar el seteo del error dentro de la fsm
	void freeFsmMemory();


private:
	JSONmember* toSave; //arreglo que se crea dinamicamente con todos los miembros del objeto encontrados, se envia luego al programa principal
	error_t err;
	event_t event_;
	readingPlace readingPlace_;
	JSONmember tempMember;//lugar donde se guardan los atributos de cada miembro a medida que se lee la informacion
	stateType currentState;
	char* JSONstringcopy;
	bool FSMdone;
	char* endOfStr;
	char *cursorPos; //posicion del cursor en el string
	unsigned int memberCount;//lleva la cuenta de la cantidad de campos encontrados
	objectParseFSM* itself;//puntero a si misma, para las rutinas de accion de la fsm, debe ser seteado por el usuario con setItselfPointer
	
	void cleanWhitespace(char* cursor);
	bool isBool(char*cursor);
	bool isNull(char*cursor);
	bool isNumber(char*cursor);
	char* pointerToEnd(char* JSONstring);//cuenta la cantidad de caracteres hasta la ultima llave
	
	void fsmStep(event_t ev);//realiza un paso de la fsm
	event_t generateEvent(char* JSONstring);//genera a partir de los strings recibidos los eventos para la fsm
	

	


	/*TABLA DE ESTADOS DE LA FSM*/
	cell_t FsmTable[STATE_COUNT][EVENT_COUNT] = 
	{//     {     ,     }     ,     "    ,      :    ,    [    ,     ]    ,     NULL ,     BOOL   ,    NUMBER    
				{{doNothing,WAITING_FOR_QUOTE_ORBRACE},{setError,END},{setError,END},{setError,END},{saveArrayObj,END},{setError,END},{setError,END},{setError,END},{setError,END},{setError,END}},
				{{setError,END},{areBracesValid,END},{saveMemberName,WAITING_FOR_MEMBER}, {setError,END}, {setError,END}, {setError,END}, {setError,END}, {setError,END}, {setError,END}, {setError,END}} ,
	/*states*/	{{saveObjectData, WAITING_FOR_OBJ_CLOSER_ORNEXT},{setError,END},{saveStringData,WAITING_FOR_OBJ_CLOSER_ORNEXT},{setError,END},{saveArrayData,WAITING_FOR_OBJ_CLOSER_ORNEXT},{setError,END},{setError,END},{saveOthersData,WAITING_FOR_OBJ_CLOSER_ORNEXT}, {saveOthersData,WAITING_FOR_OBJ_CLOSER_ORNEXT}, {saveOthersData,WAITING_FOR_OBJ_CLOSER_ORNEXT}},
				{{setError, END},{createNewMember,END},{setError,END},{setError,END},{setError,END},{setError,END},{createNewMember,WAITING_FOR_QUOTE_ORBRACE},{setError,END},{setError,END},{setError,END}},
				{{setError, END},{setError,END},{setError,END},{setError,END},{setError,END},{setError,END},{setError,END},{setError,END},{setError,END},{setError,END}} 
	};
};
 


#endif