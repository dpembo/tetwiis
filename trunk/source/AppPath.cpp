/**
 *
 * Tetwiis
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 

//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
# include "AppPath.h"

//------------------------------------------------------------------------------
// Externals
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------
static char* app_path;
//_______________________________________________________________________________
/**
 * constructor
 */
AppPath::AppPath()
{
}
 
//_______________________________________________________________________________
/**
 * destructor
 */
AppPath::~AppPath()
{

}

//_______________________________________________________________________________
/*
* Initialise the App path
*/
void AppPath::initialiseAppPath(int argc, char* argv,char* defaultPath)
{
	//printf("ARGC is %i",argc);
	//printf("start app path");
	//sleep(5);
	
	if(argc>0 && argv!=NULL && (StringUtils::stringlength(argv)>0))
	{
		int lindexof =StringUtils::lastIndexOf(strdup(argv),'/');
		//printf("\nLast Index of: %i\n",lindexof);
		app_path = strdup(StringUtils::left(strdup(argv),lindexof));
		//printf("PATH: %s\n",app_path);
	}
	else
	{
		//setColor(RED,BLACK);
		//printf(" Unable to determine working directory - assuming [sd:/apps/Bootmii_cfg_ed/]");
		app_path = defaultPath;
		//setColor(WHITE,BLACK);
	}

	//printf("Done app path");
	//sleep(5);


}


void AppPath::setAppPath(char* inAppPath)
{
	app_path=inAppPath;

}


char* AppPath::getAppPath()
{
	return app_path;
}

char* AppPath::getFullFilename(char* filename)
{
	return StringUtils::concat(app_path,filename);
}


