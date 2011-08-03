/**
 *
 * Tetwiis
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 

//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
# include "Scoring.h"


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
Scoring::Scoring()
{
	scoreMultiplier = 1;
}
 
//_______________________________________________________________________________
/**
 * destructor
 */
Scoring::~Scoring()
{
}


void Scoring::resetScore()
{
	score = 0;
	level = 1;
	linesCleared = 0;
	scoreMultiplier = 1;
}

void Scoring::singleLine()
{
	scoreMultiplier = 1;
	addLinesCleared(1);
	score += SINGLE * (level + height);
}


void Scoring::doubleLine()
{
	scoreMultiplier = 1;
	addLinesCleared(2);

	score += DOUBLE * (level + height);
	lastNoCleared = 2;
}

void Scoring::tripleLine()
{
	scoreMultiplier = 1;
	addLinesCleared(3);

	score += TRIPLE * (level + height);
	lastNoCleared = 3;
}

void Scoring::tetrisLine()
{
	scoreMultiplier = TETRIS;
	addLinesCleared(4);
	if(lastNoCleared==4)
	{
		scoreMultiplier = BACKTOBACK;
	}
	score += scoreMultiplier * (level + height);
	lastNoCleared = 4;
}

bool Scoring::wasBackToBack()
{
	return(scoreMultiplier==BACKTOBACK);
}

void Scoring::checkLevelIncrement()
{
	level = (floor(linesCleared/10)) + 1;
	if (level>99)level=99;
}

int Scoring::addLinesCleared(int innoLinesCleared)
{
	linesCleared+=innoLinesCleared;
	checkLevelIncrement();
	return linesCleared;
}

int Scoring::calculateScore(int innoLinesCleared, bool infastDrop, int inheight )
{
	scoreMultiplier = 1;
	height = 0;
	switch(innoLinesCleared)
	{
		case 0:
		{
			lastNoCleared=0;

			if(infastDrop) 
				score+=hardDrop;
			else 
				score+=softDrop;
			
			break;
		}
		
		case 1:
		{
			singleLine();
			break;
		}
		
		case 2:
		{
			doubleLine();
			break;
		}
		
		case 3:
		{
			tripleLine();
			break;
		}
		
		case 4:
		{
			tetrisLine();
			break;
		}
		
	}
	return score;
}
