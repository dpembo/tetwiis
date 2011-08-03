/**
 *
 * Skinned Console Applications C++/Wii Library
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 
//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------

#include <mxml.h>
#include <fat.h>
#include <stdlib.h>
#include <stdio.h>


#include <string.h>
#include <unistd.h>
#include "score.h"
#include "../AppPath.h"
#include "../Music.h"


#ifndef SCORESXML_HPP
#define SCORESXML_HPP

class ScoresXml
{
	public: 
		ScoresXml();
		~ScoresXml();
		void init();
		char* getDBFILE(){return DBFILE;}; 
		Score* getScore(int i){return &scores[i];};
		int insertScorePosition(int score);
		void insertScore(int score,char* name);
		void resetAllScores();
		void updateScores();
		int getMusicVol(){return musicVol;};
		int getSoundVol(){return soundVol;};
		void setMusicVol(int inVol){musicVol = inVol;};
		void setSoundVol(int inVol){soundVol = inVol;};
		
		
	
	private:
		char * DBFILE;
		char * TEMPDIR;
		Score scores[10];
		void initialiseScoresArray();
		void loadScoresFile();
		int soundVol;
		int musicVol;
		
};

#endif
