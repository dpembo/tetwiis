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
#include <wiiuse/wpad.h>
#include <grrlib.h>    
#include "images/options.h"
#include "images/optionsover.h"
#include "images/exitapp.h"
#include "images/exitappover.h"
#include "images/startnewgame.h"
#include "images/startnewgameover.h"

#include "fonts/BMfont5.h"

//Button States
#define NORMAL 0
#define OVER 1
#define PRESSED 2
#define DISABLED 3

#ifndef MENU_HPP
#define MENU_HPP
class Menu
{
	public:
		Menu();
		~Menu();
		
		static int draw_button(int x,int y,int width,int height, int wpadx, int wpady, u32 wpaddown, bool disabledState, GRRLIB_texImg *normal, GRRLIB_texImg *over, GRRLIB_texImg *pressed, GRRLIB_texImg *disabled);
		static int draw_button_callback(int x,int y,int width, int height, int wpadx, int wpady, u32 wpaddown, bool disabledState, GRRLIB_texImg *normal, GRRLIB_texImg *over, GRRLIB_texImg *pressed, GRRLIB_texImg *disabled,int (*pt2Func)(u32));
		static bool coordinatesintersect(int x, int y, int width, int height, int posx, int posy);

		static void initialise();
		static void cleanUp();
		
	private:
	
		static GRRLIB_texImg *tex_cursor, *tex_font;
		static GRRLIB_texImg *tex_startnewgame, *tex_startnewgameover;
		static GRRLIB_texImg *tex_options, *tex_optionsover;
		static GRRLIB_texImg *tex_exitapp, *tex_exitappover;

};
#endif

