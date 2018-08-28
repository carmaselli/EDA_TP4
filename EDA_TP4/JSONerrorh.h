#ifndef JSONERROR_H
#define JSONERROR_H

#include <string>
#include "objectParseFsm.h"


using namespace std;


class JSONError
{
	error_t myError;
public:

	JSONError(errorType has_Failed = NO_ERROR, const char * Desc = NULL);

	string getErrorString(void);

	errorType hasFailed(void);
}

#endif // !1




