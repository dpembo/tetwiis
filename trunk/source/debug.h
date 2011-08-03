

/**
 *
 * Tetwiis
 * (C)2009 http://www.pembo.co.uk
 *
 **/

#ifndef DEBUG_HPP
#define DEBUG_HPP

 
//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <gccore.h>
#include <fat.h>
#include <sys/dir.h>


class Debug
{
	public:
		Debug();
		~Debug();
		
		static FILE *f;
		
		static void initialise();
		static void log(const char* msg);
		
	private:

		static const bool DEBUG_ON = false;
		static bool can_open_root_fs();
		static void initialiseFat();
		
	
};
#endif

