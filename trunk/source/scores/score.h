/**
 *
 * Skinned Console Applications C++/Wii Library
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 
//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <gccore.h>
#include <fat.h>
#include <string.h>
#include <unistd.h>
#include "../StringUtils/StringUtils.h"


#ifndef SCORE_HPP
#define SCORE_HPP

class Score
{
	public: 
		Score();
		~Score();
		char* getName(){return name;}; 
		char* getScore(){return score;}; 
		char* getValidation(){return validation;}; 
		void setName(char* inName){name = inName;};
		void setScore(char* inScore){score = inScore;};
		bool setValidation(char* inValidation,bool calc);
		void setValues(char* inScore,char* inName);
		bool setValues(char* inScore,char* inName,char* inValidation);
		void calcValidation();
		
	private:
		char * name;
		char * score;
		char * validation;
		
		
};

#endif
