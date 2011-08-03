/**
 *
 * Tetwiis
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 

//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
# include "Music.h"
#

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
Music::Music()
{
	soundvol=250;
	musicvol=250;
	initialiseFat();
	ASND_Init();
	MP3Player_Init();
	
	titleMP3isready = false;
	ingame1MP3isready = false;
	loadMusicIntoBuffer();
	
}

 
//_______________________________________________________________________________
/**
 * destructor
 */
Music::~Music()
{
}

void Music::loadMusicIntoBuffer()
{
	MP3Player_Stop();
	//if(titleBuffer)free(titleBuffer);
	titleBGM = fopen(AppPath::getFullFilename(strdup("music/title.mp3")), "rb");
	if(titleBGM)
	{
		//Obtain file size
		fseek (titleBGM , 0 , SEEK_END);
		titlelSize = ftell(titleBGM);
		rewind (titleBGM);
		//Allocate memory to contain the whole file
		titleBuffer = (char*) malloc (sizeof(char)*titlelSize);
		//Copy the file into the buffer
		titleResult = fread (titleBuffer,1,titlelSize,titleBGM);
		fclose(titleBGM);
	}
	titleMP3isready = true;
	
	ingame1BGM = fopen(AppPath::getFullFilename(strdup("music/ingame1.mp3")), "rb");
	if(ingame1BGM)
	{
		//Obtain file size
		fseek (ingame1BGM , 0 , SEEK_END);
		ingame1lSize = ftell(ingame1BGM);
		rewind (ingame1BGM);
		//Allocate memory to contain the whole file
		ingame1Buffer = (char*) malloc (sizeof(char)*ingame1lSize);
		//Copy the file into the buffer
		ingame1Result = fread (ingame1Buffer,1,ingame1lSize,ingame1BGM);
		fclose(ingame1BGM);
	}
	ingame1MP3isready = true;
	
	gameOverBGM = fopen(AppPath::getFullFilename(strdup("music/highscore.mp3")), "rb");
	if(gameOverBGM)
	{
		//Obtain file size
		fseek (gameOverBGM , 0 , SEEK_END);
		gameOverlSize = ftell(gameOverBGM);
		rewind (gameOverBGM);
		//Allocate memory to contain the whole file
		gameOverBuffer = (char*) malloc (sizeof(char)*gameOverlSize);
		//Copy the file into the buffer
		gameOverResult = fread (gameOverBuffer,1,gameOverlSize,gameOverBGM);
		fclose(gameOverBGM);
	}
	gameOverMP3isready = false;	

}

void Music::initTitleMusic()
{
	MP3Player_PlayBuffer(titleBuffer,titlelSize,NULL);
}

void Music::initIngame1Music()
{
	MP3Player_PlayBuffer(ingame1Buffer,ingame1lSize,NULL);
}

void Music::initGameOverMusic()
{
	MP3Player_PlayBuffer(gameOverBuffer,gameOverlSize,NULL);
}

void Music::playTitleMusic()
{
	if( (!MP3Player_IsPlaying() && titleMP3isready))
	{
		MP3Player_PlayBuffer(titleBuffer, titlelSize, NULL);
	}

}

void Music::playIngame1Music()
{
	if( (!MP3Player_IsPlaying() && ingame1MP3isready))
	{
		MP3Player_PlayBuffer(ingame1Buffer, ingame1lSize, NULL);
	}
}

void Music::playGameOverMusic()
{
	if(MP3Player_IsPlaying() && (gameOverMP3isready))
	{
		MP3Player_PlayBuffer(gameOverBuffer, gameOverlSize, NULL);
	}

}

void Music::stop()
{
	MP3Player_Stop();
}

//_______________________________________________________________________________
/*
* Can open the SD Card
*/
bool Music::can_open_root_fs() 
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
void Music::initialiseFat()
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

void Music::mute()
{
	MP3Player_Volume(0);
}

void Music::unmute()
{
	MP3Player_Volume(musicvol);
}


void Music::playsfx(int freq, void *pcm, s32 pcmsize) {
	ASND_SetVoice(SND_GetFirstUnusedVoice(), 3, freq, 0, pcm, pcmsize, soundvol, soundvol, NULL);
}

void Music::sfxDropBlock()
{
	playsfx(44100, (char *) drop_raw, drop_raw_size);
}

void Music::sfxTetris()
{
	playsfx(44100, (char *) tetris_raw, tetris_raw_size);
}

void Music::sfxLevelUp()
{
	playsfx(44100, (char *) levelup_raw, levelup_raw_size);
}


void Music::sfxGameOver()
{
	playsfx(44100, (char *) gameover_raw, gameover_raw_size);
}

void Music::sfxCounterBeep()
{
	playsfx(44100, (char *) counterbeep_raw, counterbeep_raw_size);
}

void Music::sfxClock()
{
	playsfx(44100, (char *) clock_raw, clock_raw_size);
}

void Music::sfxGoBeep()
{
	playsfx(44100, (char *) gobeep_raw, gobeep_raw_size);
}




void Music::adjustMusicVol(bool increase)
{
	if(increase)
	{
		musicvol+=25;
		if(musicvol>250)musicvol=250;
	}
	else
	{
		musicvol-=25;
		if(musicvol<0)musicvol=0;
	}
	unmute();
}

void Music::adjustSoundVol(bool increase)
{
	if(increase)
	{
		soundvol+=25;
		if(soundvol>250)soundvol=250;
	}
	else
	{
		soundvol-=25;
		if(soundvol<0)soundvol=0;
	}
	sfxTetris();
}
