#include "JSONobject.h"

const char *JSONObject :: getFieldType(const char * f)
{
	int i = findMember(f);
	if (i == -1)
	{
		return "invalid";
	}
	else
	{
		return (JSONdata[i].type).c_str();
	}
	}
const char * JSONObject :: getArrayType(const char * f)
{
	int i = findMember(f);
	if (i == -1)
	{
		return "invalid";
	}
	const char *value;
	value = (JSONdata[i].value).c_str();
	value++;
	if (*value == '[')
	{
		return "array";
	}
	else if (*value == '{')
	{
		return "object";
	}
	else if (*value == '\"')
	{
		return "string";
	}
	else if (*value == true || *value == false)
	{
		return "bool";
	}
	else
	{
		return "number";
	}
}
unsigned int JSONObject :: getFieldCount(void)
{
	return memberCount;
}

unsigned int JSONObject:: getFieldSize(const char *f)
{
	unsigned int result = 0;
	const char * temp = f;
	int i = findMember(f);
	if (i == -1)
	{
		return 0;
	}
	const char * letter = (JSONdata[i].value).c_str();
	while (*letter != '}')
	{
		while (*letter != ':')
		{
			if (*letter == '{')
			{
				while (*letter != '}')
				{
					f++;
				}
			}
			f++;
		}
		result++;
	}
	f = temp;
	return result;
}

unsigned int JSONObject :: getFieldCount(const char *f)
{
	return fieldCount;
}
void JSONObject :: print(void)
{
	printf("FIELD : TYPE\n---------------\n");
	for (int i = 0; i <= memberCount; i++)
	{
		std::cout << JSONdata[i].name << ": " << JSONdata[i].type << endl;
	}
	printf("End of JSON object.\n");
}
bool JSONObject :: isFieldPresent(const char * f)
{
	int i = findMember(f);
	if (i >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool JSONObject :: isEmpty(void)
{
	if (!getFieldCount())
	{
		//pregutar que se hace si pasa que no hay nombre pero si value.
	}
}
void * JSONObject :: copyField(const char * f)
{
	int i = findMember(f);
	char * value = (char *) (JSONdata[i].value).c_str();
	if (i >= 0)
	{
		return copyToHeap(value);
	}
	else
	{
		return NULL;
	}
}
void * JSONObject::copyToHeap(char * value)
{
	char * temp = value;
	int cant = 0;
	while (*value != '\0')
	{
		cant++;
		value++;
	}
	value = temp;
	char * copy = (char*) malloc(cant * sizeof(char));
	temp = copy;
	for (; cant != 0; cant--)
	{
		*copy = *value;
		copy++;
		value++;
	}
	copy = temp;
	return copy;		//WTF SIGNIFICA ESTO BUTE
}
int JSONObject::str_case_cmp(char * str1, char * str2)
{
	char auxStr1[100];
	char auxStr2[100];
	strcpy_s(auxStr1, 100, str1);
	str_to_lwr(auxStr1);
	strcpy_s(auxStr2, 100, str2);	
	return strcmp(auxStr1, auxStr2);
}
void JSONObject::str_to_lwr(char * str)
{
	int i = 0;
	while (*(str + i) != '\0')
	{
		if (isupper(*(str + i)))
		{
			*(str + i) = tolower(*(str + i));
		}
		i++;
	}
}
int JSONObject::findMember(const char *f)
{
	int aux = 0, aux2 = -1;
	string str(f);
	for (int i = 0; i <= memberCount && aux != 1; i++)
	{
		if (!str.compare(JSONdata[i].name))			
		{
			aux = 1;
			aux2 = i;
		}
	}
	return aux2;
}



