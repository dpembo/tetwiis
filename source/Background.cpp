/**
 *
 * Tetwiis
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 

//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
# include "Background.h"

//------------------------------------------------------------------------------
// Externals
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------
static GRRLIB_texImg *tex_bg1;
static GRRLIB_texImg *tex_bg2;
static GRRLIB_texImg *tex_bg3;

//static GRRLIB_texImg *tex_bg4;
//static GRRLIB_texImg *tex_bg5;
static int onImage;
static int lastOnImage;
static int lastOnLevel;

//_______________________________________________________________________________
/**
 * constructor
 */
Background::Background()
{
}
 
//_______________________________________________________________________________
/**
 * destructor
 */
Background::~Background()
{
	free(tex_bg1);
	free(tex_bg2);
	free(tex_bg3);
	//free(tex_bg4);
	//free(tex_bg5);
}

void Background::initialise()
{
	tex_bg1=GRRLIB_LoadTexturePNG(bg1);
	tex_bg2=GRRLIB_LoadTexturePNG(bg2);
	tex_bg3=GRRLIB_LoadTexturePNG(bg3);
	//tex_bg4=GRRLIB_LoadTexturePNG(bg4);
	//tex_bg5=GRRLIB_LoadTexturePNG(bg5);

		
	onImage=1;
	lastOnImage=1;
	lastOnLevel = 1;
}

void Background::reset()
{
	onImage=1;
	lastOnImage=1;
	lastOnLevel = 1;
}

void Background::drawBackGround(int level)
{
	if(lastOnLevel!=level && level%5==0)onImage++;
	if(onImage>3)onImage=1;
	/*if(onImage!=lastOnImage)
	{
		if(onImage==1)tex_bg1=GRRLIB_LoadTexturePNG(bg1);
		if(onImage==2)tex_bg1=GRRLIB_LoadTexturePNG(bg2);
		if(onImage==3)tex_bg1=GRRLIB_LoadTexturePNG(bg3);
		if(onImage==4)tex_bg1=GRRLIB_LoadTexturePNG(bg4);
		if(onImage==5)tex_bg1=GRRLIB_LoadTexturePNG(bg5);
		
	}*/
	
	if(onImage==1)GRRLIB_DrawImg(0,0,tex_bg1,0,1,1,0xFFFFFFFF);
	else if(onImage==2)GRRLIB_DrawImg(0,0,tex_bg2,0,1,1,0xFFFFFFFF);
	else if(onImage==3)GRRLIB_DrawImg(0,0,tex_bg3,0,1,1,0xFFFFFFFF);
	//else if(onImage==4)GRRLIB_DrawImg(0,0,tex_bg4,0,1,1,0xFFFFFFFF);
	//if(onImage==5)GRRLIB_DrawImg(0,0,tex_bg5,0,1,1,0xFFFFFFFF);
	//GRRLIB_DrawImg(0,0,tex_bg1,0,1,1,0xFFFFFFFF);
	

	//lastOnImage = onImage;
	lastOnLevel = level;
}

