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


#ifndef COLOR_HPP
#define COLOR_HPP
class Color
{
	public:
		Color();
		Color(u32 in_color){color = in_color;};
		~Color();
		 u32 getColor(){return color;};
		 void setColor(u32 in_color){color=in_color;};
		 

		
	private:
		u32 color;

};
#endif

