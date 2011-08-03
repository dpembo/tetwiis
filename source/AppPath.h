/**
 *
 * Tetwiis
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 
//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <gccore.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include "StringUtils/StringUtils.h"


#ifndef APPPATH_HPP
#define APPPATH_HPP
class AppPath
{
	public:
		AppPath();
		~AppPath();
		
		static void setAppPath(char* inAppPath);
		static char* getAppPath();
		static void initialiseAppPath(int argc, char* argv,char* defaultPath);
		static char* getFullFilename(char* filename);

		
	private:
		
};
#endif

