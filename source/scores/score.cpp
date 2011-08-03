/**
 *
 * Skinned Console Applications C++/Wii Library
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 

//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
# include "Score.h"


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
Score::Score()
{

}
 
//_______________________________________________________________________________
/**
 * destructor
 */
Score::~Score()
{
	
}

//_______________________________________________________________________________
/**
 * Sets the score values and checks that the validation number passed is
 * correct - if not the scoreboard will be reset!
 */
bool Score::setValues(char* inScore,char* inName,char* inValidation)
{
	setScore(inScore);
	setName(inName);
	bool res = setValidation(inValidation,true);
    return res;
}

//_______________________________________________________________________________
/**
 * Set the values and calculate and set a correct validation number
 */
void Score::setValues(char* inScore,char* inName)
{
	setScore(inScore);
	setName(inName);
	calcValidation();
}

//_______________________________________________________________________________
/**
 * Set the validation number
 */
bool Score::setValidation(char* inValidation,bool calc)
{
	if(calc)
	{
		calcValidation();
		if(strcmp(validation,inValidation)!=0)
		{
			//printf(" - Validation NOT ok\n");
			return false;
		}
		else
		{
			//printf(" - Validation ok\n");
			validation = inValidation;
			return true;
		}
	}
	else
	{
	validation = inValidation;
	return true;
	}
	
}

//_______________________________________________________________________________
/**
 * Calculate and then Set the validation number
 */
void Score::calcValidation()
{
	int name1 = getName()[0];
	int name2 = getName()[1];
	int name3 = getName()[2];
	
	int totalName = (name1+name2)*name3;
	totalName = totalName + 28;
	totalName = totalName / 2;
	totalName = totalName - 9;
	
	char* str = strdup("                                                  ");
	sprintf(str,"%.08d",totalName);
	
	int scoreInt = atoi(getScore());
	scoreInt = scoreInt * 28;
	scoreInt = scoreInt + 100;
	scoreInt = scoreInt - 21;
	
	char* str2 = strdup("                                                  ");
	sprintf(str2,"%.020d",scoreInt);
	
	setValidation(strdup(StringUtils::concat(str,str2)),false);
	//printf(getValidation());
	
}
