

/**
 *
 * Tetwiis
 * (C)2009 http://www.pembo.co.uk
 *
 **/

#ifndef SQUARE_HPP
#define SQUARE_HPP

 
//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <gccore.h>

#include "Point.h"
#include "Size.h"
#include "Color.h"

#include <grrlib.h>    
#include "SquareImageProvider.h"


class Square
{
	public:
		Square();
		Square(int x,int y, int width, int height, u32 inforeColor, u32 inbackColor);
		~Square();
		
		void show();
		void hide();
		Size getSize(){return size;};
		Point getLocation() const {return location;};
		Point* getLocationInst() {return &location;};
		void setSize(Size inSize){size = inSize;};
		void setLocation(Point inLocation){location= inLocation;initialised = true;};
		void setColor(Color inforeColor,Color inbackColor){foreColor = inforeColor; backColor = inbackColor;};
		
		Color getForeColor(){return foreColor;};
		Color getBackColor(){return backColor;};
		
		bool isInitialised(){return initialised;};
	
		
	private:
		bool initialised;
		Point location;
		Size size;
		Color foreColor;
		Color backColor;
		
		
		void drawRectangle(int x,int y,int width,int height, u32 color, bool fill);
		
	
};
#endif

