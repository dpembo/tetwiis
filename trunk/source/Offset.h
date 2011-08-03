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



#ifndef OFFSET_HPP
#define OFFSET_HPP
class Offset
{
	public:
		Offset();
		~Offset();
		static int getOffsetX() {return offsetX;};
		static int getOffsetY() {return offsetY;};
		

		
	private:
		static const int offsetX = 161;
		static const int offsetY = 8;
};
#endif

