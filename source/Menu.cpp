/**
 *
 * Tetwiis
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 

//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
# include "Menu.h"

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
Menu::Menu()
{


}

void Menu::initialise()
{
//	tex_font=GRRLIB_LoadTexture(BMfont5);
}

void Menu::cleanUp()
{

	//free(tex_font);

}

 
//_______________________________________________________________________________
/**
 * destructor
 */
Menu::~Menu()
{

	//cleanUp();
}


//_______________________________________________________________________________ 
/*
 * Actually draws a button
 */

int Menu::draw_button(int x,int y,int width,int height, int wpadx, int wpady, u32 wpaddown, bool disabledState, GRRLIB_texImg *normal, GRRLIB_texImg *over, GRRLIB_texImg *pressed, GRRLIB_texImg *disabled)
{
	int state = NORMAL;
	if(disabledState)
	{
		state = DISABLED;
	}
	else
	{
		if(coordinatesintersect(x,y,width,height,wpadx,wpady))state = OVER;
		bool aPressed = false;
		
		if(state == OVER)
		{
			aPressed = wpaddown & WPAD_BUTTON_A;
			if(aPressed)state = PRESSED;
		}
		
	}
	

	if(state==NORMAL) 		GRRLIB_DrawImg(x,y,normal   ,0,1,1,0xFFFFFFFF);
	else if(state==OVER) 	GRRLIB_DrawImg(x,y,over     ,0,1,1,0xFFFFFFFF);
	else if(state==PRESSED) GRRLIB_DrawImg(x,y,pressed  ,0,1,1,0xFFFFFFFF);
	else if(state==DISABLED)GRRLIB_DrawImg(x,y,disabled ,0,1,1,0xFFFFFFFF);
	//else GRRLIB_Printf(x,y, tex_font,0xFFFFFFFF, 1, "ERRSTATE");
	
	return state;
}

int Menu::draw_button_callback(int x,int y,int width, int height, int wpadx, int wpady, u32 wpaddown, bool disabledState, GRRLIB_texImg *normal, GRRLIB_texImg *over, GRRLIB_texImg *pressed, GRRLIB_texImg *disabled,int (*pt2Func)(u32))
{
	int state;
	state = draw_button(x,y,width,height,wpadx,wpady,wpaddown,disabledState,normal,over,pressed,disabled);
	if(coordinatesintersect(x,y,width,height,wpadx,wpady))
	{
		(*pt2Func)(wpaddown);
	}
	return state;
}

//_______________________________________________________________________________ 
/*
 * Used to decide whether a coordinate (posx,posy) is within a bounding box
 * x,y,width,height
 */
bool Menu::coordinatesintersect(int x, int y, int width, int height, int posx, int posy)
{
	return GRRLIB_PtInRect(x,y,width,height,posx,posy);
}




