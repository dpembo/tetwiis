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

#include <grrlib.h>    
#include "images/squareimage.h"

#ifndef SQIMAGE_HPP
#define SQIMAGE_HPP
class SquareImageProvider
{
	public:
		SquareImageProvider();
		~SquareImageProvider();
		static void drawSquare(int x, int y, int rotation, int zoomx, int zoomy, u32 color);
		static void initialise();
		//static GRRLIB_texImg *tex_sqimage;
		
		//static GRRLIB_texImg* getTexImage(){return tex_sqimage;};
		
	private:
	
	
		
};
#endif

