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
#include "images/bg1.h"
#include "images/bg2.h"
#include "images/bg3.h"
//#include "images/bg4.h"
//#include "images/bg5.h"

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP
class Background
{
	public:
		Background();
		~Background();
		static void drawBackGround(int level);
		static void reset();
		static void initialise();
		//static GRRLIB_texImg *tex_sqimage;
		
		//static GRRLIB_texImg* getTexImage(){return tex_sqimage;};
		
	private:
	
	
		
};
#endif

