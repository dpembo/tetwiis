/**
 *
 * Skinned Console Applications C++/Wii Library
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 

#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP

//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

class StringUtils
{
	public:	
		StringUtils();
		~StringUtils();

		static int lastIndexOf(char* string, char searchFor);
		static int stringlength(char* string);
		static char* left(char* input, int length);
		static char* concat(char* str1,char* str2);
		
	private:

};
		

#endif
