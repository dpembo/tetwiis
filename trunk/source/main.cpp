//==============================================================================
//==============================================================================
// Project:  TetWiis
// Auther :  Pembo
// Copyright (C)2009 Pembo - http://www.pembo.co.uk
//==============================================================================

/**
 * @mainpage TetWiis Main
 * TetWiis main game loop
 */
 

//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <gccore.h>
#include <unistd.h>


#include <iostream>
#include <vector>


#include <wiiuse/wpad.h>

#include <grrlib.h>    

#include "Square.h"
#include "block.h"
#include "BlockList.h"
#include "Timer.h"
#include "Debug.h"
#include "Scoring.h"
#include "Music.h"
#include "Menu.h"

//Graphics
#include "images/img_cursor.h"
#include "images/tetwiisback.h"
#include "images/pembo.h"
#include "images/grrliblogo.h"
#include "images/musicby.h"
#include "images/loading.h"


#include "images/titlebackground.h"
#include "images/options.h"
#include "images/optionsover.h"
#include "images/exitapp.h"
#include "images/exitappover.h"
#include "images/resume.h"
#include "images/resumeover.h"
#include "images/startnewgame.h"
#include "images/startnewgameover.h"
#include "images/gameover.h"
#include "images/paused.h"
#include "images/wiimotevertical.h"

#include "images/effectsoption.h"
#include "images/mainmenu.h"
#include "images/mainmenuover.h"
#include "images/lefton.h"
#include "images/leftoff.h"
#include "images/righton.h"
#include "images/rightoff.h"
#include "images/effectsoption.h"
#include "images/musicoption.h"
#include "images/progressbar.h"

#include "images/count3.h"
#include "images/count2.h"
#include "images/count1.h"
#include "images/countgo.h"

#include "fonts/BMfont5.h"

#include "ErasDemi_ttf.h"

#include "images/backtoback.h"
#include "images/scoretetwiis.h"
#include "images/levelup.h"


#include "SquareImageProvider.h"
#include "Background.h"

#include "StringUtils/StringUtils.h"
#include "AppPath.h"
#include "scores/ScoresXml.h"

#include "fileop.h"

#ifdef HW_RVL
#include <di/di.h>
#endif


#define SYS_RETURNTOHBMENU   7

//Button States
#define NORMAL 0
#define OVER 1
#define CLICKED 2
#define DISABLED 3

#define HW_REG_BASE 0xcd800000
#define HW_ARMIRQMASK (HW_REG_BASE + 0x03c)
#define HW_ARMIRQFLAG (HW_REG_BASE + 0x038)



//------------------------------------------------------------------------------
// Externals
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------

//64
char chars[] = "-ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz !_-=+#,.?*";
char* scoreTableName=strdup("     ");
bool doneScore = false;
int posScoreTable = -1;

enum GameStates { MENU, GETREADY, INGAME, PAUSED, GAMEOVER, OPTIONS, SCORES};

int gameState = MENU;

int dispScore = 0;
int dispLines = 0;
int dispLevel = 1;
int frontScreenOnScore = 0;

int holdTimer = 0;
int flashTimer = 0;
int direction = 1;



int highScoreOptionSlider = 0;

Block* currentBlock;
Point point((5*GameField::getSquareSize()),0);
Music* musicPlayer = 0;
Scoring scoring;
BlockList* blockList = 0;


#define FONT_HEIGHT 16
#define FONT_WIDTH 8

Mtx GXmodelView2D;
GRRLIB_texImg *tex_cursor, *tex_font, *tex_back,*tex_startlogo,*tex_grrlib,*tex_loading,*tex_title,*tex_musicby;

GRRLIB_texImg *tex_startnewgame, *tex_startnewgameover;
GRRLIB_texImg *tex_options, *tex_optionsover;
GRRLIB_texImg *tex_exitapp, *tex_exitappover;
GRRLIB_texImg *tex_resume, *tex_resumeover;
GRRLIB_texImg *tex_paused,*tex_gameover;
GRRLIB_texImg *tex_wiimotevertical;

GRRLIB_texImg *tex_progressbar;
GRRLIB_texImg *tex_lefton,*tex_leftoff;
GRRLIB_texImg *tex_righton,*tex_rightoff;
GRRLIB_texImg *tex_effectsoption,*tex_musicoption;
GRRLIB_texImg *tex_mainmenu,*tex_mainmenuover;


GRRLIB_texImg *tex_count3,*tex_count2,*tex_count1,*tex_countgo;


GRRLIB_texImg *tex_scoretetwiis,*tex_backtoback,*tex_levelup;
GRRLIB_texImg *scoreNotification;

GRRLIB_ttfFont *scoreFont;

int rumbletime=0;

//static GXRModeObj *rmode = NULL;
s8 HWButton = -1;
//static void *xfb = NULL;

double timePassed = 0;
double elapsed =0;

bool playedGameOverSound;


	
char* scoreStr = strdup("                                              ");
char* nolinesStr = strdup("                                              ");
char* noLevelStr = strdup("                                              ");
char* timePassedStr = strdup("                                              ");
char* startTimeStr = strdup("                                              ");

bool increment=true;
int moveCounter = 0;
int menubouncepos = 0;


u32 wpadheld,wpadup,pressed;
int wpadx=0, wpady=0;

ir_t ir1;

int beforeLevel,afterLevel;
int prevOverItem = -1;
int rotationAngle = 0;
int prevScoreType = -1;


char* app_path;
ScoresXml scoresXml;

// Which of the chars the user is editing!
int onInit = 0;
//3 ints to hold the score entry selction
int onChar1 = 0;
int onChar2 = 0;
int onChar3 = 0;

char inits1 = '-';
char inits2 = '-';
char inits3 = '-';

#define CLOCKWISE 1
#define ANTICLOCKWISE -1

//_______________________________________________________________________________
/**
 * Check if we have hardware access
 */
int have_hw_access()
{
	if((*(volatile unsigned int*)HW_ARMIRQMASK)&&(*(volatile unsigned int*)HW_ARMIRQFLAG)) return 1;
	else return 0;
}

//_______________________________________________________________________________
/**
 * Callback for the reset button on the Wii.
 */
void WiiResetPressed()
{
	HWButton = SYS_RETURNTOMENU;
}

//_______________________________________________________________________________
/**
 * Callback for the power button on the Wii.
 */
void WiiPowerPressed()
{
	HWButton = SYS_POWEROFF_STANDBY;
}

//_______________________________________________________________________________
/**
 * Callback for the power button on the Wiimote.
 * @param[in] chan The Wiimote that pressed the button
 */
void WiimotePowerPressed(s32 chan)
{
	HWButton = SYS_POWEROFF_STANDBY;
	//SYS_POWEROFF
}

//_______________________________________________________________________________
/*
* Starts the wiimote rumble
*/
void startRumble()
{
        rumbletime = 1;
        WPAD_Rumble(WPAD_CHAN_0, 1);
}

//_______________________________________________________________________________
/*
* Starts the wiimote rumble after 7 iterations (about 0.5 seconds)
*/
bool checkStopRumble(bool longrumble)
{
	if(longrumble==false && rumbletime == 7)
	{
			rumbletime = 0;
			WPAD_Rumble(WPAD_CHAN_0, 0);
			return true;
	}
	else if(longrumble==true && rumbletime == 14)
	{
			rumbletime = 0;
			WPAD_Rumble(WPAD_CHAN_0, 0);
			return true;				
	}
	else
	{
			rumbletime++;
			return false;
	}
}

//_______________________________________________________________________________
/*
* Initialise the textures/images
*/
void tex_Init()
{	//font is initialized first
	tex_font=GRRLIB_LoadTexture(BMfont5);
	scoreFont = GRRLIB_LoadTTF(ErasDemi_ttf, ErasDemi_ttf_size);
    GRRLIB_InitTileSet(tex_font, FONT_WIDTH, FONT_HEIGHT, 0);
	tex_cursor=GRRLIB_LoadTexturePNG(img_cursor);
	tex_back=GRRLIB_LoadTexturePNG(tetwiisback);
	tex_startlogo=GRRLIB_LoadTexturePNG(pembo);
	tex_grrlib=GRRLIB_LoadTexturePNG(grrliblogo);
	tex_loading=GRRLIB_LoadTexturePNG(loading);
	tex_title=GRRLIB_LoadTexturePNG(titlebackground);
	tex_wiimotevertical=GRRLIB_LoadTexturePNG(wiimotevertical);
	
	tex_options=GRRLIB_LoadTexturePNG(options);
	tex_optionsover=GRRLIB_LoadTexturePNG(optionsover);
	tex_exitapp=GRRLIB_LoadTexturePNG(exitapp);
	tex_exitappover=GRRLIB_LoadTexturePNG(exitappover);
	tex_resume=GRRLIB_LoadTexturePNG(resume);
	tex_resumeover=GRRLIB_LoadTexturePNG(resumeover);
	tex_startnewgame=GRRLIB_LoadTexturePNG(startnewgame);
	tex_startnewgameover=GRRLIB_LoadTexturePNG(startnewgameover);
	
	
	tex_paused = GRRLIB_LoadTexturePNG(paused);
	tex_gameover = GRRLIB_LoadTexturePNG(gameover);
	
	tex_scoretetwiis = GRRLIB_LoadTexturePNG(scoretetwiis);
	tex_backtoback = GRRLIB_LoadTexturePNG(backtoback);
	tex_levelup = GRRLIB_LoadTexturePNG(levelup);
	
	tex_musicby = GRRLIB_LoadTexturePNG(musicby);
	
	
	tex_progressbar = GRRLIB_LoadTexturePNG(progressbar);
	tex_lefton = GRRLIB_LoadTexturePNG(lefton);
	tex_leftoff = GRRLIB_LoadTexturePNG(leftoff);
	tex_righton = GRRLIB_LoadTexturePNG(righton);
	tex_rightoff = GRRLIB_LoadTexturePNG(rightoff);
	tex_effectsoption = GRRLIB_LoadTexturePNG(effectsoption);
	tex_musicoption = GRRLIB_LoadTexturePNG(musicoption);
	tex_mainmenu = GRRLIB_LoadTexturePNG(mainmenu);
	tex_mainmenuover = GRRLIB_LoadTexturePNG(mainmenuover);
	
	GRRLIB_SetMidHandle(tex_levelup,true);
	GRRLIB_SetMidHandle(tex_backtoback,true);
	GRRLIB_SetMidHandle(tex_scoretetwiis,true);
	
	tex_count3= GRRLIB_LoadTexturePNG(count3);
	tex_count2= GRRLIB_LoadTexturePNG(count2);
	tex_count1= GRRLIB_LoadTexturePNG(count1);
	tex_countgo= GRRLIB_LoadTexturePNG(countgo);
	
	SYS_SetResetCallback(WiiResetPressed);
	SYS_SetPowerCallback(WiiPowerPressed);
	WPAD_SetPowerButtonCallback(WiimotePowerPressed);
	
	SquareImageProvider::initialise();
	Background::initialise();
	
}

//_______________________________________________________________________________
/*
* Clean up
*/
void tex_free()
{	free(tex_back);
	free(tex_startlogo);
	free(tex_cursor);
	free(tex_font);
	free(tex_grrlib);
	free(tex_loading);
	
	free(tex_title);
	free(tex_startnewgame);
	free(tex_startnewgameover);
	free(tex_options);
	free(tex_optionsover);
	free(tex_exitapp);
	free(tex_exitappover);	
	free(tex_resume);
	free(tex_resumeover);
	
	free(tex_paused);
	free(tex_gameover);
	free(tex_wiimotevertical);
	free(tex_scoretetwiis);
	free(tex_backtoback);
	free(tex_levelup);
	
	free(tex_musicby);
	
	
	free(tex_progressbar);
	free(tex_lefton);
	free(tex_leftoff);
	free(tex_righton);
	free(tex_rightoff);
	free(tex_effectsoption);
	free(tex_musicoption);
	free(tex_mainmenu);
	free(tex_mainmenuover);
	
	free(tex_count3);
	free(tex_count2);
	free(tex_count1);
	free(tex_countgo);
}

//_______________________________________________________________________________
/*
* Draw Score Notifications
*/
int drawAnyScoreNotifications(int scoreType)
{
	//1 - level up
	//2 - tetris
	//3 - back2back
	
	if(scoreType<0)
	{
		prevScoreType = -1;
		return -1;
	}
	
	//New score type - start again!
	if(scoreType!=prevScoreType)
	{
		rotationAngle=0;
	}
	
	if(scoreType>0) rotationAngle+=3;
	
	if(rotationAngle>=360)
	{	
		rotationAngle=0;
		scoreType=-1;
	}
	
	//Currently drawing one!
	//Only swap if it's a new scoreType (i.e. not -1)
	//otherwise carry on drawing!
		
	if(scoreType==1)
	{
		GRRLIB_DrawImg(375+60,232+20,tex_levelup,rotationAngle,1,1,0xFFFFFFFF);
	}
	else if(scoreType==2)
	{
		GRRLIB_DrawImg(375+68,232+20,tex_scoretetwiis,rotationAngle,1,1,0xFFFFFFFF);
	}
	else if(scoreType==3)
	{
		GRRLIB_DrawImg(375+68,232+20,tex_backtoback,rotationAngle,1,1,0xFFFFFFFF);
	} 
		
	prevScoreType = scoreType;
	return scoreType;

}

//_______________________________________________________________________________
/**
* Draw Vertical Wiimote reminder
**/
void drawWiiMoteReminder()
{
	//const int width = 24;
	//const int height= 92;
	
	if(flashTimer>500 && flashTimer<1000)
	{	
		if(doneScore==false)GRRLIB_DrawImg( 15 ,5,tex_wiimotevertical,0,1,1,0xFFFFFFFF);
	}
	if(flashTimer>1500)
	{
		flashTimer = 0;
	}
	
}

//_______________________________________________________________________________
/**
* Draw the game over message
**/
void drawGameOverMessage()
{
	const int width = 320/2;
	const int height= 120/2;
	
	GRRLIB_DrawImg( (245-(width/2)) ,220-(height/2),tex_gameover,0,0.5,0.5,0xFFFFFFFF);
}

//_______________________________________________________________________________
/**
* Draw the Loading message (not used anymore)
**/
void drawLoadingMessage()
{
	const int width = 320/2;
	const int height= 120/2;
	
	GRRLIB_DrawImg(320-(width/2),240-(height/2),tex_loading,0,0.5,0.5,0xFFFFFFFF);
	GRRLIB_Render();
}

//_______________________________________________________________________________
/**
* Draw the title background image
**/
void drawTitleBackground()
{
	GRRLIB_DrawImg(0,0,tex_title,0,1,1,0xFFFFFFFF);
}


//_______________________________________________________________________________
/**
* Plage 
**/
void playOverSample(int overItem)
{
	//only play if the over menu item changes
	if(prevOverItem!=overItem)
	{
		musicPlayer->sfxDropBlock();
		if(overItem>0)startRumble();
	}
	

	prevOverItem = overItem;
}

int startPressed(u32 wpaddown)
{
	playOverSample(1);
	u32 check = 999;
	if(wpaddown==check || (pressed & WPAD_BUTTON_A))
	{
		//Get a new random block!
		currentBlock = new Block(point,0);
		scoring.resetScore();
		
		scoreStr = strdup("                                              ");
		nolinesStr = strdup("                                              ");
		noLevelStr = strdup("                                              ");
		timePassedStr = strdup("                                              ");
		startTimeStr = strdup("                                              ");
		
		
		inits1='-';
		inits2='-';
		inits3='-';
		onInit = 0;
		onChar1 = 0;
		onChar2 = 0;
		onChar3 = 0;
		doneScore = false;
		posScoreTable = -1;

		
		blockList->holdBlock(-1);
		blockList->initialiseQueue();
		dispLines = 0;
		dispScore = 0;
		dispLevel = 1;
		beforeLevel = 1;
		afterLevel = 1;
		//nolines = 0;
		GameField::reset();
		Point point(5*GameField::getSquareSize(),0);
		currentBlock = new Block(point,0);
		playedGameOverSound = false;
		musicPlayer->stop();
		//musicPlayer->initIngame1Music();
		Background::reset();
		gameState = GETREADY;
	}
	return 0;
}

int optionsPressed(u32 wpaddown)
{
	u32 check = 999;
	playOverSample(2);
	if(wpaddown==check || (pressed & WPAD_BUTTON_A))
	{
		gameState =OPTIONS;
	}
	return 0;
}

int exitAppPressed(u32 wpaddown)
{
	playOverSample(3);
	if(pressed & WPAD_BUTTON_A)
	{
		rumbletime = 0;
		WPAD_Rumble(WPAD_CHAN_0, 0);
		tex_free();
		GRRLIB_Exit();
		exit(0);
	}
	return 0;
}

int resumePressed(u32 wpaddown)
{
	playOverSample(3);
	if(pressed & WPAD_BUTTON_A)
	{
		rumbletime = 0;
		WPAD_Rumble(WPAD_CHAN_0, 0);
		gameState = INGAME;
		musicPlayer->unmute();
	}
	return 0;
}


int mainmenuPressed(u32 wpaddown)
{
	playOverSample(4);

	if(wpaddown==999 || (pressed & WPAD_BUTTON_A))
	{
		if(gameState == OPTIONS)
		{
			scoresXml.setMusicVol(musicPlayer->getMusicVol());
			scoresXml.setSoundVol(musicPlayer->getSoundVol());
			scoresXml.updateScores();		
		}
		if(gameState == PAUSED)
		{
			musicPlayer->stop();
			musicPlayer->unmute();
		}
		
		if(gameState == SCORES)musicPlayer->stop();
		
		rumbletime = 0;
		WPAD_Rumble(WPAD_CHAN_0, 0);
		
		gameState = MENU;
	}
	return 0;
}

int sfxDownPressed(u32 wpaddown)
{
	playOverSample(5);
	if(wpaddown==999  || (pressed & WPAD_BUTTON_A))
	{
		musicPlayer->adjustSoundVol(false);
	}
	return 0;
}

int sfxUpPressed(u32 wpaddown)
{
	playOverSample(6);
	if(wpaddown==999 || (pressed & WPAD_BUTTON_A))
	{
		musicPlayer->adjustSoundVol(true);
	}
	return 0;
}

int musicUpPressed(u32 wpaddown)
{
	playOverSample(7);
	if(wpaddown==999 || (pressed & WPAD_BUTTON_A))
	{
		musicPlayer->adjustMusicVol(true);
	}
	return 0;
}

int musicDownPressed(u32 wpaddown)
{
	playOverSample(8);
	if(wpaddown==999 || (pressed & WPAD_BUTTON_A))
	{
		musicPlayer->adjustMusicVol(false);
	}
	return 0;
}

void drawPausedScreen()
{
	GRRLIB_FillScreen(0x000000FF);    // Clear the screen

	const int width = 320/2;
	const int height= 120/2;
	GRRLIB_DrawImg(320-(width/2),140-(height/2),tex_paused,0,0.5,0.5,0xFFFFFFFF);
	GRRLIB_Printf(230,160, tex_font, 0xFFFFFFFF, 1, "Press 'HOME' to resume");
	
	Menu::draw_button_callback(350,220,400,80, wpadx, wpady, pressed, false, tex_resume, tex_resumeover, tex_resumeover, tex_resume,&resumePressed);
	Menu::draw_button_callback(350,310,400,80, wpadx, wpady, pressed, false, tex_mainmenu, tex_mainmenuover, tex_mainmenuover, tex_mainmenu,&mainmenuPressed);
	Menu::draw_button_callback(350,400,400,80, wpadx, wpady, pressed, false, tex_exitapp, tex_exitappover, tex_exitappover, tex_exitapp,&exitAppPressed);
}


void drawOptions()
{
	drawTitleBackground();
	int calc;
	//music header
	GRRLIB_DrawImg(166,157,tex_musicoption,0,1,1,0xFFFFFFFF);

	//Up down buttons
	Menu::draw_button_callback(-266,186,424,52, wpadx, wpady, pressed, false, tex_leftoff, tex_lefton, tex_lefton, tex_leftoff,&musicDownPressed);
	Menu::draw_button_callback(500,186,424,52, wpadx, wpady, pressed, false, tex_rightoff, tex_righton, tex_righton, tex_rightoff,&musicUpPressed);
	
	//Music Progress Bar
	GRRLIB_DrawImg(164,190,tex_progressbar,0,1,1,0xFFFFFFFF);
	
	calc = musicPlayer->getMusicVol();
	calc = calc/25;
	if(calc<10)GRRLIB_Rectangle(173+(calc*31),196,310-(calc*31),30,0x000000FF,1);
	
	
	
	//SFX -----------------------------------------------------------
	
	//sfx header
	GRRLIB_DrawImg(165,268,tex_effectsoption,0,1,1,0xFFFFFFFF);

	//Up down buttons
	Menu::draw_button_callback(-266,293,424,52, wpadx, wpady, pressed, false, tex_leftoff, tex_lefton, tex_lefton, tex_leftoff,&sfxDownPressed);
	Menu::draw_button_callback(500,293,424,52, wpadx, wpady, pressed, false, tex_rightoff, tex_righton, tex_righton, tex_rightoff,&sfxUpPressed);
	
	//SFX progress bar
	GRRLIB_DrawImg(164,297,tex_progressbar,0,1,1,0xFFFFFFFF);
	
	//Finally draw a rectangle to hide the progress bar blocks!
	
	calc = musicPlayer->getSoundVol();
	calc = calc/25;
	
	//calc = number of boxes to show!
	//starting point should be x + calc*30;
	if(calc<10)GRRLIB_Rectangle(173+(calc*31),303,310-calc*31,30,0x000000FF,1);
	
	
	//Main Menu button -----------------------------------------------
	
	//Main menu button
	Menu::draw_button_callback(350,374,400,80, wpadx, wpady, pressed, false, tex_mainmenu, tex_mainmenuover, tex_mainmenuover, tex_mainmenu,&mainmenuPressed);
	
	
}


void drawScores()
{
	drawTitleBackground();
	
	int startY=150;
	int nameXPos = 420;
	int i=0;
	int j=0;
	int onScore = 0;
	char* oncharStr = strdup("          ");
	if(posScoreTable==-1)posScoreTable=scoresXml.insertScorePosition(scoring.getScore());
	u32 color = 0xFFFFFFFF;
	if(posScoreTable<0) doneScore = true;
	if(posScoreTable>=0 && doneScore == false)
	{
		GRRLIB_PrintfTTF(20 ,   startY, scoreFont, "You have achieved a NEW High Score!",16,0xFFFF00FF);
		GRRLIB_PrintfTTF(20 ,startY+20, scoreFont, "Enter your initials with the wiimote",16,0xFFFF00FF);
		GRRLIB_PrintfTTF(20 ,startY+40, scoreFont, "using up/down to select a letter and",16,0xFFFF00FF);
		GRRLIB_PrintfTTF(20 ,startY+60, scoreFont, "left/right to move between characters",16,0xFFFF00FF);
		GRRLIB_PrintfTTF(20 ,startY+90, scoreFont, "Press (A) when finished to save your score!",16,0xFFFF00FF);
	

		//Now draw the 3 chars - which ever one they're on, draw in yellow
		if(onInit==0)color=0xFFFF00FF;else color= 0xFFFFFFFF;
		//GRRLIB_Printf(20 ,startY+130, tex_scoreFont, color, 1, "%c",chars[onChar1]);
		sprintf(oncharStr,"%c",chars[onChar1]);
		GRRLIB_PrintfTTF(40, startY+130, scoreFont, oncharStr, 26, color);
		
		if(onInit==1)color=0xFFFF00FF;else color= 0xFFFFFFFF;
		//GRRLIB_Printf(70 ,startY+130, tex_scoreFont, color, 1, "%c",chars[onChar2]);
		sprintf(oncharStr,"%c",chars[onChar2]);
		GRRLIB_PrintfTTF(70, startY+130, scoreFont, oncharStr, 26, color);
		
		if(onInit==2)color=0xFFFF00FF;else color= 0xFFFFFFFF;
		//GRRLIB_Printf(130 ,startY+130, tex_font, color, 1, "%c",chars[onChar3]);
		sprintf(oncharStr,"%c",chars[onChar3]);
		GRRLIB_PrintfTTF(100, startY+130, scoreFont, oncharStr, 26, color);
	}
	
	//Draw the 3 chars
	
	//if(doneScore==true)
	/*{*/
	for(i=0;i<10;i++)
	{
		j=i+1;
		
		color= 0xFFFFFFFF;
		if(i==posScoreTable)color=0xFFFF00FF;
		
			
		if(i==posScoreTable)
		{
			sprintf(oncharStr,"%d.",j);
			GRRLIB_PrintfTTF(nameXPos-30 ,startY + i*20, scoreFont, oncharStr, 16, 0xFFFF00FF);		
			sprintf(oncharStr,"%c%c%c",chars[onChar1],chars[onChar2],chars[onChar3]);
			GRRLIB_PrintfTTF(nameXPos+30  ,startY + i*20, scoreFont, oncharStr, 16, 0xFFFF00FF);
			sprintf(oncharStr,"%d",scoring.getScore());
			GRRLIB_PrintfTTF(nameXPos+110 ,startY + i*20, scoreFont, oncharStr, 16, 0xFFFF00FF);
			//GRRLIB_Printf(nameXPos-30 ,startY + i*20, tex_font, 0xFFFF00FF, 1, "%d.",j);
			//GRRLIB_Printf(nameXPos ,startY + i*20, tex_font, 0xFFFF00FF, 1, "%c%c%c",chars[onChar1],chars[onChar2],chars[onChar3]);
			//GRRLIB_Printf(nameXPos + 90,startY + i*20, tex_font, 0xFFFF00FF, 1, "%d",scoring.getScore());

		}
		else
		{

			onScore = i;
			if(doneScore == false && i>posScoreTable)onScore = i-1;
			sprintf(oncharStr,"%d.",j);
			GRRLIB_PrintfTTF(nameXPos-30  ,startY + i*20, scoreFont, oncharStr, 16, color);		
			GRRLIB_PrintfTTF(nameXPos+30 ,startY + i*20, scoreFont, scoresXml.getScore(onScore)->getName(), 16, color);
			GRRLIB_PrintfTTF(nameXPos+110 ,startY + i*20, scoreFont, scoresXml.getScore(onScore)->getScore(), 16, color);
		}
		
	}
	
	/*}*/
	
	
	//Slide in from right!
	
	if(doneScore==true &&highScoreOptionSlider>0)highScoreOptionSlider=highScoreOptionSlider-4;
	
	if(doneScore==true)Menu::draw_button_callback(350+highScoreOptionSlider,374,400,80, wpadx, wpady, pressed, false, tex_mainmenu, tex_mainmenuover, tex_mainmenuover, tex_mainmenu,&mainmenuPressed);
	
}

void drawMenu()
{
	drawTitleBackground();
	
	
	int startY=150;
	int nameXPos = 420;
	int i=0;
	int j=0;
	char* oncharStr = strdup("          ");
	//only increment every 3 times through
	//to slow down the bounce!
	/*
	if(moveCounter>1)
	{
		if(increment)
		{
			menubouncepos++;
		}
		else
		{
			menubouncepos--;
		}
		moveCounter = 0;
	}*/
	
	//GRRLIB_DrawImg(-100,100,tex_startnewgame,0,1,1,0xFFFFFFFF);
	//GRRLIB_DrawImg(-100,170,tex_options,0,1,1,0xFFFFFFFF);
	//GRRLIB_DrawImg(340,260,tex_exitapp,0,1,1,0xFFFFFFFF);	
	//drawExitButton(340,260,wpadx,wpady);
	//moveCounter++;
	if(holdTimer>1000){
		holdTimer = 0;
		frontScreenOnScore = frontScreenOnScore + direction;
		if(frontScreenOnScore==9)direction=-1;
		if(frontScreenOnScore==0)direction=1;
	
	}
	//GRRLIB_Printf(30,20, tex_font, 0xFFFFFFFF, 1, "%d,%d",wpadx,wpady);

	
	u32 color = 0xFFFFFFFF;
	
	for(i=0;i<10;i++)
	{
		j=i+1;
		if(i==frontScreenOnScore)color=0xFFFF00FF;
		else color = 0xFFFFFFFF;

		sprintf(oncharStr,"%d.",j);
		GRRLIB_PrintfTTF(nameXPos-30  ,startY + i*20, scoreFont, oncharStr, 16, color);		
		GRRLIB_PrintfTTF(nameXPos+30 ,startY + i*20, scoreFont, scoresXml.getScore(i)->getName(), 16, color);
		GRRLIB_PrintfTTF(nameXPos+110 ,startY + i*20, scoreFont, scoresXml.getScore(i)->getScore(), 16, color);

		
	}
	
	
	Menu::draw_button_callback(-114,249,400,80, wpadx, wpady, pressed, false, tex_startnewgame, tex_startnewgameover, tex_startnewgameover, tex_startnewgame,&startPressed);
	Menu::draw_button_callback(-114,338,400,80, wpadx, wpady, pressed, false, tex_options, tex_optionsover, tex_optionsover, tex_options,&optionsPressed);
	Menu::draw_button_callback(350,374,400,80, wpadx, wpady, pressed, false, tex_exitapp, tex_exitappover, tex_exitappover, tex_exitapp,&exitAppPressed);
	
}




void initialise(bool grrlib,int argc,char* argv)
{
	if(!grrlib)
	{
		// Initialise the video system
		VIDEO_Init();
		
		// Obtain the preferred video mode from the system
		// This will correspond to the settings in the Wii menu
		rmode = VIDEO_GetPreferredMode(NULL);

		// Allocate memory for the display in the uncached region
		//xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
		
		// Initialise the console, required for printf
		console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);
		
		// Set up the video registers with the chosen mode
		VIDEO_Configure(rmode);
		
		// Tell the video hardware where our display memory is
		VIDEO_SetNextFramebuffer(xfb);
		
		// Make the display visible
		VIDEO_SetBlack(FALSE);

		// Flush the video register changes to the hardware
		VIDEO_Flush();

		// Wait for Video setup to complete
		VIDEO_WaitVSync();
		if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
		
		// This function initialises the attached controllers
		WPAD_Init();
		
		//For the Pointer >>
		WPAD_SetVRes(0, 640, 480);
		WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
		// <<
	}
	else
	{
		// Init GRRLib
		GRRLIB_Init();
		tex_Init();
		GRRLIB_FillScreen(0x000000FF);
		GRRLIB_Render();
		
		// This function initialises the attached controllers
		WPAD_Init();
		WPAD_SetVRes(0, 640, 480);
		WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
	}
	

	
	Debug::initialise();
	
	//
	
	blockList = new BlockList();
	blockList->initialiseQueue();
	
	//drawLoadingMessage();
	
	AppPath::initialiseAppPath(argc, argv,strdup("sd:/apps/tetwiis/"));
	
	MountAllDevices();
	
	musicPlayer = new Music();	
	musicPlayer->initTitleMusic();
	
	
}



void drawScreen()
{
	
	//Draw the background
	GRRLIB_FillScreen(0x000000FF);    // Clear the screen
	Background::drawBackGround(scoring.getLevel());
	GRRLIB_DrawImg(0,-20,tex_back,0,1,1,0xFFFFFFFF);
	
				
	//sprintf(timePassedStr, "TP [%g]", timePassed);		
	//sprintf(startTimeStr,  "EL [%g]", elapsed);		
		
	sprintf(scoreStr, "%015i", dispScore);		
	sprintf(nolinesStr, "%04i", dispLines);		
	sprintf(noLevelStr, "%02i", dispLevel);
				
	GRRLIB_Printf(380,370, tex_font, 0xFFFFFFFF, 1, scoreStr);
	GRRLIB_Printf(63,245, tex_font, 0xFFFFFFFF, 1, nolinesStr);
	GRRLIB_Printf(70,245+107, tex_font, 0xFFFFFFFF, 1, noLevelStr);
	//GRRLIB_Printf(500,160, tex_font, 0xFFFFFFFF, 1, startTimeStr);
				
	currentBlock->show();
	currentBlock->drawDropPosition();
	blockList->drawBlocks();
	GameField::redraw();

}




void drawCounter(int onInt)
{
	int fi;
	for(fi=254;fi>0;fi-=8)
	{
		drawScreen();
		if(onInt==3)
		{
			GRRLIB_DrawImg(230,180,tex_count3,0,1,1,0xFFFFFF00|fi);
			
		}
		else if(onInt==2)
		{
			GRRLIB_DrawImg(230,180,tex_count2,0,1,1,0xFFFFFF00|fi);
		}
		else if(onInt==1)
		{
			GRRLIB_DrawImg(230,180,tex_count1,0,1,1,0xFFFFFF00|fi);
		}
		else
		{
			//Must be go!
			GRRLIB_DrawImg(230,180,tex_countgo,0,1,1,0xFFFFFF00|fi);
		}
		
		GRRLIB_Render();		
	}
}


void dropInPemboLogo()
{
	
	int fi=240-40;
	int vertpos = 240-40;

	vertpos = 195;
	for(fi=0;fi<254;fi+=2)
	{
		GRRLIB_DrawImg(320-160,vertpos,tex_startlogo,0,1,1,0xFFFFFF00|fi);
		GRRLIB_Render();
		WPAD_ScanPads();
		if( (WPAD_ButtonsDown(0) & WPAD_BUTTON_A)||(WPAD_ButtonsDown(0) && WPAD_CLASSIC_BUTTON_A))
		{
			return;
		}
	}
	
	for(fi=0;fi<300;fi+=2)
	{
		GRRLIB_DrawImg(320-160,vertpos,tex_startlogo,0,1,1,0xFFFFFFFF);
		GRRLIB_Render();
		WPAD_ScanPads();
		if( (WPAD_ButtonsDown(0) & WPAD_BUTTON_A)||(WPAD_ButtonsDown(0) && WPAD_CLASSIC_BUTTON_A))
		{
			return;
		}
	}
	

	for(fi=254;fi>0;fi-=2)
	{
		GRRLIB_DrawImg(320-160,vertpos,tex_startlogo,0,1,1,0xFFFFFF00|fi);
		GRRLIB_Render();
		WPAD_ScanPads();
		if( (WPAD_ButtonsDown(0) & WPAD_BUTTON_A)||(WPAD_ButtonsDown(0) && WPAD_CLASSIC_BUTTON_A))
		{
			return;
		}
	}	
	GRRLIB_FillScreen(0x000000FF);
	GRRLIB_Render();
}

void fadeMusicBy()
{
	int fi=0;
	for(fi=0;fi<254;fi+=2)
	{
		GRRLIB_DrawImg(320-176,240-64,tex_musicby,0,1,1,0xFFFFFF00|fi);
		GRRLIB_Render();
		WPAD_ScanPads();
		if( (WPAD_ButtonsDown(0) & WPAD_BUTTON_A)||(WPAD_ButtonsDown(0) && WPAD_CLASSIC_BUTTON_A))
		{
			return;
		}
	}
	
	for(fi=0;fi<20;fi+=2)
	{
		GRRLIB_DrawImg(320-176,240-64,tex_musicby,0,1,1,0xFFFFFFFF);
		GRRLIB_Render();
		WPAD_ScanPads();
		if( (WPAD_ButtonsDown(0) & WPAD_BUTTON_A)||(WPAD_ButtonsDown(0) && WPAD_CLASSIC_BUTTON_A))
		{
			return;
		}		
	}	
	
	for(fi=254;fi>0;fi-=2)
	{
		GRRLIB_DrawImg(320-176,240-64,tex_musicby,0,1,1,0xFFFFFF00|fi);
		GRRLIB_Render();
		WPAD_ScanPads();
		if( (WPAD_ButtonsDown(0) & WPAD_BUTTON_A)||(WPAD_ButtonsDown(0) && WPAD_CLASSIC_BUTTON_A))
		{
			return;
		}		
	}	
}


void fadeGRRLibLogo()
{
	int fi=0;
	for(fi=0;fi<254;fi+=2)
	{
		GRRLIB_DrawImg(320-100,240-34,tex_grrlib,0,0.5,0.5,0xFFFFFF00|fi);
		GRRLIB_Render();
		WPAD_ScanPads();
		if( (WPAD_ButtonsDown(0) & WPAD_BUTTON_A)||(WPAD_ButtonsDown(0) && WPAD_CLASSIC_BUTTON_A))
		{
			return;
		}
	}
	
	for(fi=0;fi<20;fi+=2)
	{
		GRRLIB_DrawImg(320-100,240-34,tex_grrlib,0,0.5,0.5,0xFFFFFFFF);
		GRRLIB_Render();
		WPAD_ScanPads();
		if( (WPAD_ButtonsDown(0) & WPAD_BUTTON_A)||(WPAD_ButtonsDown(0) && WPAD_CLASSIC_BUTTON_A))
		{
			return;
		}		
	}	
	
	for(fi=254;fi>0;fi-=2)
	{
		GRRLIB_DrawImg(320-100,240-34,tex_grrlib,0,0.5,0.5,0xFFFFFF00|fi);
		GRRLIB_Render();
		WPAD_ScanPads();
		if( (WPAD_ButtonsDown(0) & WPAD_BUTTON_A)||(WPAD_ButtonsDown(0) && WPAD_CLASSIC_BUTTON_A))
		{
			return;
		}		
	}	
}

void QuickFadeInTitleBackground()
{
	int fi=0;

	for(fi=0;fi<254;fi+=10)
	{
		GRRLIB_DrawImg(0,0,tex_title,0,1,1,0xFFFFFF00|fi);
		GRRLIB_Render();
	}	
}



/**
 * Entry point.
 * @param[in] argc The number of arguments invoked with the program
 * @param[in] argv The array containing the arguments
 * @return 0 on clean exit, an error code otherwise
 */
int main(int argc, char **argv)
{
	
	// only reload IOS if AHBPROT is not enabled
    
	u32 version = IOS_GetVersion();
    s32 preferred = IOS_GetPreferredVersion();

    if(version != 58 && preferred > 0 && version != (u32)preferred && have_hw_access()!=1) 
		IOS_ReloadIOS(preferred);

	
	
	
		
	bool doFastDrop = false;

	initialise(true,argc, argv[0]);
	
	scoresXml.init();
	musicPlayer->setMusicVol(scoresXml.getMusicVol());
	musicPlayer->setSoundVol(scoresXml.getSoundVol());
	
	
	
	dropInPemboLogo();
	fadeMusicBy();
	fadeGRRLibLogo();
	QuickFadeInTitleBackground();
	
	Timer timer;


	//Vector blocks;
	//Block *currentBlock;
	
	currentBlock = new Block(point,0);
	
	bool movedDown = false;
	int fullLines;
	int nextBlockType = -1;
	bool hasMovedDown = false;	
	beforeLevel = 1;
	afterLevel = 1;

	bool usedHold = false;
	
	playedGameOverSound = false;
	int scoreNotification = -1;
	holdTimer = 0;
	flashTimer = 0;
	
	//Amount of time for hold keys..
	int holdTimerReset = 125;
	int clockSoundTimer = 0;
	int clockSoundReset = 420;
	int letGoTimer = 0;
	int letGoReset = 125;
	int firstPopulatedLine = -1;
	bool letGoTimerActive = false;
	
	while(1) {

		// Call WPAD_ScanPads each loop, this reads the latest controller states
		
		WPAD_IR(WPAD_CHAN_0, &ir1);
        WPAD_ScanPads();
		
        wpadheld = WPAD_ButtonsHeld(0);
		pressed = WPAD_ButtonsDown(0);
		wpadup = WPAD_ButtonsUp(0);
        wpadx=ir1.sx-200;
        wpady=ir1.sy-250;

		//Get the number of ms since last iteration!
		timePassed = timer.timePassed();
		elapsed += timePassed;
		holdTimer += timePassed;
		flashTimer += timePassed;
		clockSoundTimer += timePassed;
		letGoTimer+= timePassed;
		if(clockSoundTimer>clockSoundReset+5000)clockSoundTimer=0;
		if(flashTimer>1500)flashTimer=0;
		if(letGoTimer>1500)letGoTimer=0;
		
		
		
		//Used as if its already moved down, don't do it again.
		hasMovedDown = false;
		
		// WPAD_ButtonsDown tells us which buttons were pressed in this loop
		// this is a "one shot" state which will not fire again until the button has been released

		if(HWButton != -1)
		{
			break;
		}
		
		
		switch(gameState)
		{
			case MENU:
			{
				
				musicPlayer->playTitleMusic();
				drawMenu();
			
				//GRRLIB_Printf(80,100, tex_font, 0xFFFFFFFF, 1, AppPath::getFullFilename(strdup("tetwiis.dat")));
				
				//If press home in the menu, then quit!
				if ( (pressed & WPAD_BUTTON_HOME)||(pressed & WPAD_CLASSIC_BUTTON_HOME)  ) 
				{
					tex_free();
					GRRLIB_Exit();
					UnmountAllDevices();
					exit(0);
				}
				
				if(pressed & WPAD_CLASSIC_BUTTON_PLUS)
				{
					startPressed(999);
					WPAD_Rumble(WPAD_CHAN_0, 0);
				}
				
				if(pressed & WPAD_CLASSIC_BUTTON_MINUS)
				{
					optionsPressed(999);
					
				}
				
				checkStopRumble(false);
			}
			break;
			
			case OPTIONS:
			{
				musicPlayer->playTitleMusic();
				drawOptions();
				checkStopRumble(false);
				
				if(pressed & WPAD_CLASSIC_BUTTON_Y){musicDownPressed(999);}
				if(pressed & WPAD_CLASSIC_BUTTON_X){musicUpPressed(999);}
				if(pressed & WPAD_CLASSIC_BUTTON_B){sfxDownPressed(999);}
				if(pressed & WPAD_CLASSIC_BUTTON_A){sfxUpPressed(999);}
				if(pressed & WPAD_CLASSIC_BUTTON_PLUS){mainmenuPressed(999);}
				if(pressed & WPAD_CLASSIC_BUTTON_MINUS){mainmenuPressed(999);}
				if(pressed & WPAD_CLASSIC_BUTTON_HOME){mainmenuPressed(999);}
			}
			break;
			
			case GETREADY:
			{
				musicPlayer->sfxCounterBeep();
				drawCounter(3);
				musicPlayer->sfxCounterBeep();
				drawCounter(2);
				musicPlayer->sfxCounterBeep();
				drawCounter(1);
				musicPlayer->sfxGoBeep();
				drawCounter(0);
				gameState=INGAME;
			}
			
			case INGAME:
			{
				musicPlayer->playIngame1Music();
				//If TICK
				firstPopulatedLine = GameField::firstPopulatedLine();
				if( firstPopulatedLine>=0 && firstPopulatedLine<=4 && (clockSoundTimer>clockSoundReset) )
				{
					musicPlayer->sfxClock();
					clockSoundTimer = 0;
				}
				
				if ((pressed & WPAD_BUTTON_RIGHT) || (pressed & WPAD_CLASSIC_BUTTON_UP))
				{
					doFastDrop = true;
					currentBlock->down();
					holdTimer=0;
				}
				
				if(!doFastDrop)
				{
					if ( pressed & WPAD_BUTTON_1){currentBlock->rotate(ANTICLOCKWISE);}
					if ( pressed & WPAD_BUTTON_2){currentBlock->rotate(CLOCKWISE);}
					if ( pressed & WPAD_CLASSIC_BUTTON_A){currentBlock->rotate(CLOCKWISE);}
					if ( pressed & WPAD_CLASSIC_BUTTON_B){currentBlock->rotate(ANTICLOCKWISE);}
					if ( pressed & WPAD_CLASSIC_BUTTON_X){currentBlock->rotate(CLOCKWISE);}
					if ( pressed & WPAD_CLASSIC_BUTTON_Y){currentBlock->rotate(ANTICLOCKWISE);}
				
					
			
					
					if ( (pressed & (WPAD_BUTTON_A|WPAD_CLASSIC_BUTTON_FULL_R)) && (usedHold == false) )
					{
						int heldBlockType;
						heldBlockType = blockList->holdBlock(currentBlock->getBlockType());
						
						if(heldBlockType<=0) heldBlockType = blockList->nextQueueItem();
						delete(currentBlock);
						currentBlock = new Block(point,heldBlockType);
						usedHold = true;
					}
					
					
					if ( (wpadheld & WPAD_BUTTON_UP || (wpadheld & WPAD_CLASSIC_BUTTON_LEFT)) && holdTimer>holdTimerReset )
					{
						currentBlock->left();
						holdTimer=0;
					}
					
					if ((wpadheld & WPAD_BUTTON_DOWN || (wpadheld & WPAD_CLASSIC_BUTTON_RIGHT)) && holdTimer > holdTimerReset)
					{
						currentBlock->right();
						holdTimer=0;
					}
					
					
					if ((wpadheld & WPAD_BUTTON_LEFT || (wpadheld & WPAD_CLASSIC_BUTTON_DOWN))  && hasMovedDown==false)
					{
						if(letGoTimerActive==true)
						{
							if(letGoTimer>letGoReset)
							{
								letGoTimer=0;
								letGoTimerActive=false;
							}
						}
						else
						{
							movedDown = currentBlock->down();
						}
						
						if(movedDown==false)
						{
							//Need to think about adding a delay here to prevent the next move down from occurring too quickly!
							letGoTimerActive=true;
							
						}
						
						holdTimer=0;
						
					}
				
				}
				
				if(doFastDrop)elapsed=10001;
				
				if(elapsed>=1000 )
				{		
					//Increase the starting elapsed time depending on the level!
					elapsed = scoring.getLevel()*40;
					
					movedDown = currentBlock->down();
					hasMovedDown = true;
					if(!movedDown)
					{
						doFastDrop = false;
						if(currentBlock->top()<0)
						{
							gameState=GAMEOVER;
							break;
						}
						else 
						{
							fullLines = GameField::checkLines();
							//nolines += fullLines;
							//score+= 100 * fullLines;
							//score += 10;
							if(fullLines>=4)
							{
								
								musicPlayer->sfxTetris();
								scoreNotification = 2;
							}
							else
							{
								musicPlayer->sfxDropBlock();
							}
							
							beforeLevel = scoring.getLevel();
							dispScore = scoring.calculateScore(fullLines,false,0);
							if(scoring.wasBackToBack()) scoreNotification = 3;
							dispLevel = scoring.getLevel();
							
							
							
							
							if(dispLevel>beforeLevel)
							{
								musicPlayer->sfxLevelUp();
								scoreNotification = 1;
							}
							dispLines = scoring.getLinesCleared();
							
							Point point(5*GameField::getSquareSize(),0);
							
							
							nextBlockType = blockList->nextQueueItem();
							currentBlock = new Block(point,nextBlockType);
							
							if(currentBlock->checkStartNewBlock()==false)
							{
								gameState=GAMEOVER;
								//musicPlayer->initGameOverMusic();
								//musicPlayer->playGameOverMusic();
								//break;	
							}							
							
							usedHold = false;
						}
					}
			
				}				
				

				

		
				//If press home then pause.
				if ( (pressed & WPAD_BUTTON_HOME)||(pressed & WPAD_CLASSIC_BUTTON_HOME)  ) 
				{
					gameState = PAUSED;
					musicPlayer->mute();
				}
				
				
				drawScreen();
				scoreNotification = drawAnyScoreNotifications(scoreNotification);
			}
			break;
			
			case PAUSED:
			{
				drawPausedScreen();
				if ( (pressed & WPAD_BUTTON_HOME)||(pressed & WPAD_CLASSIC_BUTTON_HOME)  ) 
				{
					gameState = INGAME;
					musicPlayer->unmute();
				}	
				checkStopRumble(true);		
			}
			break;			
			
			case GAMEOVER:
			{
				drawScreen();
				
				musicPlayer->stop();
				musicPlayer->mute();
				
				//Do this once only!
				if(playedGameOverSound==false)
				{
					startRumble();
					musicPlayer->sfxGameOver();
					playedGameOverSound = true;
					highScoreOptionSlider = 400;
				}
				
				drawGameOverMessage();
				if ( (pressed & WPAD_BUTTON_A)||(pressed & WPAD_CLASSIC_BUTTON_A) )
				{
					musicPlayer->stop();
					musicPlayer->unmute();
					//musicPlayer->initGameOverMusic();
					QuickFadeInTitleBackground();
					
					posScoreTable=scoresXml.insertScorePosition(scoring.getScore());
					if(posScoreTable<0)
					{
						musicPlayer->initTitleMusic();
						gameState = MENU;
					}
					else 
					{
						musicPlayer->initGameOverMusic();
						gameState = SCORES;
					}
					
				}
				
				checkStopRumble(true);
			}
			break;
			
			case SCORES:
			{
				drawScores();
				drawWiiMoteReminder();
				if(doneScore==false)
				{
					if ( (wpadheld & WPAD_BUTTON_UP || (wpadheld & WPAD_CLASSIC_BUTTON_UP)) && holdTimer>holdTimerReset )
					{
						if(onChar1>63)onChar1=0;
						
						if(onInit==0)onChar1++;
						if(onInit==1)onChar2++;
						if(onInit==2)onChar3++;
						holdTimer=0;
					}
					if ( (wpadheld & WPAD_BUTTON_DOWN || (wpadheld & WPAD_CLASSIC_BUTTON_DOWN)) && holdTimer>holdTimerReset )
					{
						if(onInit==0)onChar1--;
						if(onInit==1)onChar2--;
						if(onInit==2)onChar3--;
						holdTimer=0;
					}

					if ( (pressed & WPAD_BUTTON_LEFT || (pressed & WPAD_CLASSIC_BUTTON_LEFT)) && holdTimer>holdTimerReset )
					{
						onInit--;
					}
					if ( (pressed & WPAD_BUTTON_RIGHT || (pressed & WPAD_CLASSIC_BUTTON_RIGHT)) && holdTimer>holdTimerReset )
					{
						onInit++;
					}

					if ((pressed & WPAD_BUTTON_A) || (pressed & WPAD_CLASSIC_BUTTON_A) )
					{
						sprintf(scoreTableName, "%c%c%c", chars[onChar1],chars[onChar2],chars[onChar3]);		
						scoresXml.insertScore(scoring.getScore(),strdup(scoreTableName));
						scoresXml.updateScores();
						doneScore = true;
					}
					
					if(onInit<0)onInit=0;
					if(onInit>2)onInit=2;
					if(onChar1<0)onChar1=63;
					if(onChar2<0)onChar2=63;
					if(onChar3<0)onChar3=63;
					if(onChar1>63)onChar1=0;
					if(onChar2>63)onChar2=0;
					if(onChar3>63)onChar3=0;					
				
				}
				else
				{
					if(pressed & WPAD_CLASSIC_BUTTON_HOME)
					{
						mainmenuPressed(999);
					}
				}
				checkStopRumble(false);
			}
		}

		//Draw the cursor if not in game		
		if(gameState!=INGAME)GRRLIB_DrawImg(wpadx-13,wpady,tex_cursor,ir1.angle,1,1,0xFFFFFFFF);
		//Render the screen
		GRRLIB_Render();
		// Wait for the next frame
		//VIDEO_WaitVSync();
	}
	
	if(HWButton == SYS_POWEROFF_STANDBY)
	{
		SYS_ResetSystem(SYS_POWEROFF,0,0);
	}
	
	if(HWButton == SYS_RETURNTOMENU)
	{
		SYS_ResetSystem(SYS_RESTART,0,0);
		
	}
			
	UnmountAllDevices();
	return 0;
}




