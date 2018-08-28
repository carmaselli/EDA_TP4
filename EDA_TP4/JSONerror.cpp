#include "JSONerrorh.h"

JSONError::JSONError(errorType has_Failed = NO_ERROR, const char * Desc = NULL)
{
	myError.error = has_Failed;
	myError.errorString = Desc;
}

string JSONError::getErrorString(void)
{
	return myError.errorString;
}

errorType JSONError::hasFailed(void)
{
	return myError.error;
}