#ifndef JSONERROR_H
#define JSONERROR_H

#include <string>


using namespace std;




class JSONError
{
public:

	JSONError(bool has Failed = false, const char * Desc = NULL);

	string getErorString(void);

	bool hasFailed(void);
}

#endif // !1




