
/**
 *
 * Tetwiis
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 

//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
# include "Debug.h"

//------------------------------------------------------------------------------
// Externals
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------

//_______________________________________________________________________________
/**
 * constructor
 */
Debug::Debug()
{
}
 
//_______________________________________________________________________________
/**
 * destructor
 */
Debug::~Debug()
{
}

void Debug::initialise()
{
	initialiseFat();
}

//_______________________________________________________________________________
/*
* Can open the SD Card
*/
bool Debug::can_open_root_fs() 
{
	DIR_ITER *root = diropen("SD:/");
	if (root) 
	{
		dirclose(root);
		return true;
	}
	return false;
}

//_______________________________________________________________________________
/*
* Initialises FAT
*/
void Debug::initialiseFat()
{
	//printf(" Initialising FAT ......... ");
	if (!fatInitDefault())
	{
		//drawError(15,11,11,50,err1_initFatErr);
		//errorApplication("Unable to initialise FAT subsystem, exiting.\n");
	}
	
	if (!can_open_root_fs()) 
	{
		//errorApplication("Unable to open SD card, exiting.\n");
		//drawError(15,11,11,50,err2_rootFS);
	}
	//printf("Done\n");

}


void Debug::log(const char* msg)
{
		if(DEBUG_ON==true)
		{
		FILE *f = fopen ("SD:/tetwiis.log", "a");
		fputs(msg,f);
		fputs("\n",f);
		fclose(f);
		}
}
