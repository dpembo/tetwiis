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
#include <mxml.h>
#include <math.h>
#include "music.h"
#include "encryption/aes.h"



#ifndef SCORING_HPP
#define SCORING_HPP
class Scoring
{
	public:
		Scoring();
		~Scoring();
		
		enum scoreLevelMultipliers { SINGLE = 100, DOUBLE = 300, TRIPLE = 500,TETRIS=800, BACKTOBACK=1200 };

		void resetScore();
		void checkLevelIncrement();
		int addLinesCleared(int innoLinesCleared);
		int calculateScore(int innoLinesCleared, bool infastDrop, int inheight);

		int height;
		int level;
		int score;
		int linesCleared;
		int lastNoCleared;

		int getLevel(){return level;};
		int getScore(){return score;};
		int getLinesCleared(){return linesCleared;};
		bool wasBackToBack();
		
	private:
		

		int getHeight(){return height;};
		int getLastNoCleared(){return lastNoCleared;};		
		
		void setLevel(int inLevel){level=inLevel;};
		void setScore(int inScore){score=inScore;};
		void setLinesCleared(int inLinesCleared){linesCleared=inLinesCleared;};
		
		static const int softDrop = 4;
		static const int hardDrop = 8;
		static const int levelIncrement = 10;
		int scoreMultiplier;
		
		

		
		void singleLine();
		void doubleLine();
		void tripleLine();
		void tetrisLine();

		

	
		

};
#endif

