#ifndef OBJECTPARSEFSM_H
#define OBJECTPARSEFSM_H

#include"fsmCommon.h"
#include<iostream>
#include<string>
#include"JSONobject.h"
#include"objFSMactroutines.h"

typedef enum { WAITING_FOR_OBJOPENER, WAITING_FOR_OPENING_QUOT, WAITING_FOR_CLOSING_QUOT,WAITING_FOR_COLON,\
WAITING_FOR_DATAOPENING_BRACKETS, WAITING_FOR_DATACLOSING_BRACKETS, WAITING_FOR_OBJCLOSER,END} stateType; //ver si end debe ser un estado o solo una funcion
#define STATE_COUNT 8


typedef enum { OPENING_BRACKETS, CLOSING_BRACKETS,QUOTATION, COLON,OPENING_SQ_BRACKETS,CLOSING_SQ_BRACKETS,END_OF_FILE} eventType;
#define EVENT_COUNT 7

typedef enum{OBJECT,ARRAY} parseMode;
typedef enum{IN_STRING, IN_INNER_OBJ, IN_ARRAY, OUTSIDE}readingPlace;

class objectParseFSM
{
public:
	objectParseFSM(char* JSONstring); //constructor
	bool fsmStartParsing(void);//empieza a parsear un string en busca de objetos(esta es la fsm)
	error_t getError();  //devuelve una estructura error con el tipo de error ocurrido, NO_ERROR en caso de no haber error
	string getObjName(); //devuelve el nombre del objeto recibido
	JSONmember* getMemberArray(); //devuelve el puntero al arreglo de miembros
private:
	string objName;//aqui se guardara el nombre del objeto, si es un arreglo se guarda "null"
	JSONmember* toSave; //arreglo que se crea dinamicamente con todos los miembros del objeto encontrados, se envia luego al programa principal
	error_t err;
	event_t event_;
	parseMode mode;
	char *cursorPos;
	readingPlace readingPlace_;







	void fsmStep(event_t ev);//realiza un paso de la fsm
	event_t generateEvent(char* JSONstring);//genera a partir de los strings recibidos los eventos para la fsm
	void setError_(int errorType, const char* errorString);//para facilitar el seteo del error dentro de la fsm
	const cell_t objFsmTable[STATE_COUNT][EVENT_COUNT] = {	//op brackets, close brackets, quotation, colon, op_square brackets, close square brackets, EOF
															{{setMode,WAITING_FOR_OPENING_QUOT},{setError,END}, {setError,END}, {setError,END}, {parseArray,WAITING_FOR_OBJCLOSER}, {setError,END},{setError,END}},				
															{{setError, END}, {setError, END}, { parseString,WAITING_FOR_CLOSING_QUOT }, { setError,END }, { setError,END }, { setError,END }, { setError,END }},
															{{setError, END}, { setError,END }, {doNothing,WAITING_FOR_COLON}, { setError,END }, { setError,END }, { setError,END }, { setError,END }},
															{{setError, END}, { setError,END }, { setError,END }, { doNothing,WAITING_FOR_DATAOPENING_BRACKETS }, { setError,END }, { setError,END }, { setError,END }},
															{{startMemberFSM,WAITING_FOR_DATACLOSING_BRACKETS}, { setError,END }, { setError,END }, { setError,END }, { setError,END }, { setError,END }, { setError,END } },
															{{setError, END}, {saveMembers,WAITING_FOR_OBJCLOSER}, { setError,END }, { setError,END }, { setError,END }, { setError,END }, { setError,END }}, 
															{{setError, END}, { checkMode,END }, { setError,END }, { setError,END }, { setError,END }, {checkMode,END}, { setError,END }}, 
															{{setError, END}, { setError, END }, { setError, END }, { setError, END }, { setError, END }, { setError, END }, {endFsm,END}}
														};




};

#endif