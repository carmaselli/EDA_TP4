#include "JSONobject.h"

class JSONobject 
{
public:



	const char * getFieldType(const char * f)
	{
		int i = findMember(f);
		if (i == -1)
		{
			return "invalid";
		}
		else
		{
			return JSONdata[i].type;
		}

	}

	const char * getArrayType(const char * f)			// terminar
	{
		int i = findMember(f);
		if (i == -1)
		{
			return "invalid";
		}
		char *value = JSONdata[i].value;
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

	unsigned int getFieldCount(void)
	{
		return memberCount;
	}


	unsigned int setFieldSize(const char *f)
	{
		unsigned int result = 0;
		const char * temp = f;
		int i = findMember(f);
		if (i == -1)
		{
			return 0;
		}
		char * letter = JSONdata[i].value;
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

	unsigned int getFieldCount(const char *f)
	{
		return fieldCount;
	}

	void print(void)
	{
		printf("FIELD : TYPE\n---------------\n");
		for (int i = 0; i <= memberCount; i++)
		{
			printf("%s : %s\n", JSONdata[i].name, JSONdata[i].type);
		}
		printf("End of JSON object.\n");
	}

	bool isFieldPresent(const char * f)
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

	bool isEmpty(void)
	{
		if (!getFieldCount())
		{
			//pregutar que se hace si pasa que no hay nombre pero si value.
		}
	}

	void * copyField(const char * f)
	{
		int i = findMember(f);
		char * value = JSONdata[i].value;
		if (i >= 0)
		{
			return copyToHeap(value);
		}
		else
		{
			return NULL;
		}
	}

	void * copyToHeap(char * value)
	{
		char * temp = value;
		int cant = 0;
		while (*value != '\0')
		{
			cant++;
			value++;
		}
		value = temp;
		char * copy = malloc(cant * sizeof(char));
		temp = copy;
		for (; cant != 0; cant--)
		{
			*copy = *value;
			copy++;
			value++;
		}
		copy = temp;
		return (*void)copy;
	}

	int str_case_cmp(char * str1, char * str2)
	{
		char auxStr1[100];
		char auxStr2[100];
		strcpy_s(auxStr1, 100, str1);
		str_to_lwr(auxStr1);
		strcpy_s(auxStr2, 100, str2);	// Uso strcpy_s porque usando strcpy Visual me hacia saltar un error.
		str_to_lwr(auxStr2);

		return strcmp(auxStr1, auxStr2);
	}

	void str_to_lwr(char * str)
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

	int findMember(const char *f)
	{
		int aux = 0, aux2 = -1;
		for (int i = 0; i <= memberCount && aux != 1; i++)
		{
			if (str_case_cmp(JSONdata[i].name, f))
			{
				aux = 1;
				aux2 = i;
			}
		}
		return aux2;
	}



}


