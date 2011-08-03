
/**
 *
 * Skinned Console Applications C++/Wii Library
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 
//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
# include "StringUtils.h"



//------------------------------------------------------------------------------
// Externals
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------



//_______________________________________________________________________________
/**
 * Constructor
 */
 StringUtils::StringUtils()
 {
 }
 
//_______________________________________________________________________________
/**
 * destructor
 */
 StringUtils::~StringUtils()
 {
 }
 

//_______________________________________________________________________________
/**
 * Gets the last index of a character in a string
 * @param[in] string to find character in
 * @param[in] char to search for
 * @return int containing position of searchFor or -1 if not found
 **/
int StringUtils::lastIndexOf(char* string, char searchFor)
{
	char *ptr_my;
	ptr_my=strrchr(string, searchFor);
	

		if (ptr_my == NULL)
			return -1;
			//printf("Character is not found.\n");
		//else
			//printf("Character found at %d\n", ptr_my - string+1);
			
	
	int i = -1;
	i = (ptr_my - string+1);
	return i;
}

//_________________________________________________________________________
/**
 * Gets the length of a string
 * @param[in] string to get length of
 * @return int containing length of string
 **/
int StringUtils::stringlength(char* string)
{
	return strlen(string);
}

//_________________________________________________________________________
/**
 * Performs a 'left' substring
 * @param[in] input string to substring from
 * @param[in] length number of chars to copy from left of string
 * @return substring value
 **/
char* StringUtils::left(char* input, int length)
{
	char result[length+1];
	//printf("\nInput is : [%s]",input);
	//printf("\nLength is: [%i]",length);
	strlcpy (result, input, length+1);
	//printf("\nRESULT IS: [%s]\n",result);
	return strdup(result);
}


//_________________________________________________________________________
/**
 * Concatenates 2 strings
 * @param[in] str1 string 1
 * @param[in] str2 string 2
 * @return str1 plus str2
 **/
char * StringUtils::concat(char* str1,char* str2)
{
	char str[200];
	strcpy (str,strdup(str1));
	strcat  (str,strdup(str2));
	//puts(str);
	return strdup(str);
	
}
