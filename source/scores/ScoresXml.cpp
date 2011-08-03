/**
 *
 * Skinned Console Applications C++/Wii Library
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 

//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
# include "ScoresXml.h"

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
ScoresXml::ScoresXml()
{
	

}


 
//_______________________________________________________________________________
/**
 * destructor
 */
ScoresXml::~ScoresXml()
{
	
}

void ScoresXml::init()
{
	DBFILE = AppPath::getFullFilename(strdup("tetwiis.dat"));
	initialiseScoresArray();
	loadScoresFile();
}
//_______________________________________________________________________________
/**
 * Initialise the Scores Array with empty values
 */
void ScoresXml::initialiseScoresArray()
{
	int i=0;
	for (i = 0;i<10;i++)
	{
		Score s;
		s.setScore(strdup("0"));
		s.setName(strdup("AAA"));
		s.setValidation(strdup("0000423000000000000000002879"),false);
		scores[i] = s;

	}
}

//_______________________________________________________________________________
/**
 * Reset all scores
 */
void ScoresXml::resetAllScores()
{
	scores[0].setValues( strdup("1000"),strdup("AAA"),strdup("0000423000000000000000028079"));
	scores[1].setValues( strdup("900"),strdup("AAA"),strdup("0000423000000000000000025279"));
	scores[2].setValues( strdup("800"),strdup("AAA"),strdup("0000423000000000000000022479"));
	scores[3].setValues( strdup("700"),strdup("AAA"),strdup("0000423000000000000000019679"));
	scores[4].setValues( strdup("600"),strdup("AAA"),strdup("0000423000000000000000016879"));
	scores[5].setValues( strdup("500"),strdup("AAA"),strdup("0000423000000000000000014079"));
	scores[6].setValues( strdup("400"),strdup("AAA"),strdup("0000423000000000000000011279"));
	scores[7].setValues( strdup("300"),strdup("AAA"),strdup("0000423000000000000000008479"));
	scores[8].setValues( strdup("200"),strdup("AAA"),strdup("0000423000000000000000005679"));
	scores[9].setValues( strdup("100"),strdup("AAA"),strdup("0000423000000000000000002879"));        
}

//_______________________________________________________________________________
/**
 * Load the scores file.
 */
void ScoresXml::loadScoresFile()
{
FILE *fp = fopen(getDBFILE(), "rb");

	mxml_node_t *scoretree;
	mxml_node_t *scorenode;

	bool valid=false;
			
	if (fp == NULL) 
	{
	
		fclose(fp);
		printf("Unable to open settings file [%s]",getDBFILE());
		sleep(10);
	}
	
	else
	{
		fseek (fp , 0, SEEK_END);
		long settings_size = ftell (fp);
		rewind (fp);
		
		if (settings_size > 0) 
		{
			
			scoretree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
			fclose(fp);	
			
		
			int scoreCount;
			//Now populate the Skin object for each skin!
			scoreCount=0;
			for (scorenode = mxmlFindElement(scoretree, scoretree,"score",NULL, NULL,MXML_DESCEND);scorenode != NULL;scorenode = mxmlFindElement(scorenode, scoretree,"score",NULL, NULL,MXML_DESCEND))
			{
				printf("\nParsing score [%s]-[%s]\n",strdup(mxmlElementGetAttr(scorenode,"name")),strdup(mxmlElementGetAttr(scorenode,"score")));			
				valid = scores[scoreCount].setValues( strdup(mxmlElementGetAttr(scorenode,"score")), strdup(mxmlElementGetAttr(scorenode,"name")),strdup(mxmlElementGetAttr(scorenode,"validation")));
				if(valid!=true)
				{
					resetAllScores();
					break;
				}
				scoreCount++;
			}
			
			scorenode = mxmlFindElement(scoretree, scoretree, "music", NULL, NULL, MXML_DESCEND);
			setMusicVol(atoi(mxmlElementGetAttr(scorenode,"volume")));
			
			scorenode = mxmlFindElement(scoretree, scoretree, "effects", NULL, NULL, MXML_DESCEND);
			setSoundVol(atoi(mxmlElementGetAttr(scorenode,"volume")));
			
		}			

		else 
		{
			fclose(fp);
			//unlink("sd:/apps/bootmii/bce_messages.xml");
			printf("Unable to read settings file [tetwiis.xml]");
			
		}		
	}//*/	
}


//_______________________________________________________________________________
/**
 * Finds which position you are in the score table!
 */
int ScoresXml::insertScorePosition(int score)
{
	int i=9;
    //printf("Inserting Score [%d]",score);
	int insertPos = -1;
	for(i=9;i>=0;i--)
	{
        //printf("On [%d]\n",i);
		int onScore = atoi(getScore(i)->getScore());
		//printf("comparing score: [%d] with onScore: [%d]\n",score,onScore);
		if(score>onScore) insertPos=i;
        else break;
	}
	return insertPos;
}
//_______________________________________________________________________________
/**
 * Insert a new score into the table
 */
void ScoresXml::insertScore(int score,char* name)
{
	//First find the insert position - go from to 1
	int insertPos = -1;
	
	insertPos = insertScorePosition(score);
	
	//printf("Score Pos [%d]\n",insertPos);
	//If it's 10, just drop in the new score 
	char* scoreStr =strdup("                                                  ");
	sprintf(scoreStr,"%d",score);
	if(insertPos == 9) 
	{
		getScore(9)->setValues(strdup(scoreStr),strdup(name));
	}
	else if(insertPos <9 and insertPos >=0)
	{
		//need to shuffle down one place all scores below insert pos,
		//then set score in insert pos
		for (int i=8;i>=insertPos;i--)
		{
			getScore(i+1)->setValues(strdup(getScore(i)->getScore()),strdup(getScore(i)->getName()));
		}
		getScore(insertPos)->setValues(scoreStr,name);
	}
	else return;
}


//_______________________________________________________________________________
/**
 * Update the scores file.
 */
void ScoresXml::updateScores()
{
	mxml_node_t *scoretree;
	mxml_node_t *scorenode;
	FILE *fp = fopen(getDBFILE(), "rb");
	//printf("About to load XML\n\n");

	if (fp == NULL)
	{
		fclose(fp);
		printf("Unable to open settings file");

	}
	else
	{
		fseek (fp , 0, SEEK_END);
		long settings_size = ftell (fp);
		rewind (fp);

		if (settings_size > 0)
		{

			scoretree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
			fclose(fp);	
			
		
			int scoreCount;
			scoreCount=0;
			for (scorenode = mxmlFindElement(scoretree, scoretree,"score",NULL, NULL,MXML_DESCEND);scorenode != NULL;scorenode = mxmlFindElement(scorenode, scoretree,"score",NULL, NULL,MXML_DESCEND))
			{
				printf("\nParsing score [%s]-[%s]\n",strdup(mxmlElementGetAttr(scorenode,"name")),strdup(mxmlElementGetAttr(scorenode,"score")));			
				Score* s = getScore(scoreCount);
				mxmlElementSetAttr(scorenode,"name",strdup(s->getName()));
				mxmlElementSetAttr(scorenode,"score",strdup(s->getScore()));
				mxmlElementSetAttr(scorenode,"validation",strdup(s->getValidation()));
				scoreCount++;
			}
			
			char * volStr = strdup("   ");
			sprintf(volStr,"%i",getMusicVol());
			scorenode = mxmlFindElement(scoretree, scoretree, "music", NULL, NULL, MXML_DESCEND);
			mxmlElementSetAttr(scorenode,"volume",volStr);
			
			char * sfxvolStr = strdup("   ");
			sprintf(sfxvolStr,"%i",getSoundVol());
			scorenode = mxmlFindElement(scoretree, scoretree, "effects", NULL, NULL, MXML_DESCEND);
			mxmlElementSetAttr(scorenode,"volume",sfxvolStr);

			FILE *f;
			f = fopen(getDBFILE(), "wb");

			if (f == NULL)
			{
				fclose(f);
				//printf("Settings could not be written.\n");
				//press1ToContinue();
				printf("Unable to write settings to [bce_settings.xml]");
			}
			else
			{
				mxmlSaveFile(scoretree, f, MXML_NO_CALLBACK);
				fclose(f);
				mxmlDelete(scorenode);
				mxmlDelete(scoretree);
				//printf("Settings Saved\n");
				f = NULL;
			}


		}
	}

	fp = NULL;
	scorenode = NULL;
	scoretree = NULL;
}