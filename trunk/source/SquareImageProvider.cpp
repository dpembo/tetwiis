/**
 *
 * Tetwiis
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 

//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
# include "SquareImageProvider.h"

//------------------------------------------------------------------------------
// Externals
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------
static GRRLIB_texImg *tex_sqimage;

//_______________________________________________________________________________
/**
 * constructor
 */
SquareImageProvider::SquareImageProvider()
{
}
 
//_______________________________________________________________________________
/**
 * destructor
 */
SquareImageProvider::~SquareImageProvider()
{
	free(tex_sqimage);
}

void SquareImageProvider::initialise()
{
	tex_sqimage=GRRLIB_LoadTexturePNG(squareimage);
}

void SquareImageProvider::drawSquare(int x, int y, int rotation, int zoomx, int zoomy, u32 color)
{
	GRRLIB_DrawImg(x,y,tex_sqimage,rotation,zoomx,zoomy,color);
}

