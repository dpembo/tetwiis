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
#include <ogc/lwp_watchdog.h>
#include <fat.h>
#include <sys/dir.h>
#include <mp3player.h>
#include <asndlib.h>
#include <drop_raw.h>
#include <tetris_raw.h>
#include <levelup_raw.h>
#include <gameover_raw.h>
#include <counterbeep_raw.h>
#include <clock_raw.h>
#include <gobeep_raw.h>
#include "AppPath.h"


#ifndef MUSIC_HPP
#define MUSIC_HPP
class Music
{
	public:
		Music();
		~Music();
		
		FILE *titleBGM;
		long titlelSize;
		char * titleBuffer;
		size_t titleResult;
		bool titleMP3isready;
		
		FILE *ingame1BGM;
		long ingame1lSize;
		char * ingame1Buffer;
		size_t ingame1Result;
		bool ingame1MP3isready;		
		
		FILE *gameOverBGM;
		long gameOverlSize;
		char * gameOverBuffer;
		size_t gameOverResult;
		bool gameOverMP3isready;	

		int soundvol;
		int musicvol;

		void loadMusicIntoBuffer();
		
		void initTitleMusic();
		void playTitleMusic();
		
		void initIngame1Music();
		void playIngame1Music();

		void initGameOverMusic();
		void playGameOverMusic();		
		
		void stop();
		
		void mute();
		void unmute();
		
		
		void sfxDropBlock();
		void sfxLevelUp();
		void sfxTetris();
		void sfxGameOver();
		void sfxCounterBeep();
		void sfxGoBeep();
		void sfxClock();
		
		void adjustMusicVol(bool increase);
		void adjustSoundVol(bool increase);
		
		int getMusicVol(){return musicvol;};
		int getSoundVol(){return soundvol;};
		
		void setMusicVol(int inVol){musicvol = inVol;unmute();};
		void setSoundVol(int inVol){soundvol = inVol;};
		
		
	private:
	
		void initialiseFat();
		bool can_open_root_fs();
		void playsfx(int freq, void *pcm, s32 pcmsize);

};
#endif

