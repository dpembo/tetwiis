

/**
 *
 * Tetwiis
 * (C)2009 http://www.pembo.co.uk
 *
 **/

#ifndef GAMEFIELD_HPP
#define GAMEFIELD_HPP

 
//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <gccore.h>
#include "square.h"

#include <grrlib.h>    


class GameField
{
	public:
		GameField();
		~GameField();
		
		static bool isEmpty(int x,int y);
		static int checkLines();
		static void stopSquare(Square* square);
		static void reset();
		static int getSquareSize(){return squareSize;};
		static int getWidth(){return width;};
		static int getHeight(){return height;};
		static void redraw();
		
		static int getOffSetX(){return offsetX;};
		static int getOffSetY(){return offsetY;};
		static void drawRectangle(int x,int y,int width,int height, u32 color, bool fill);
		static int firstPopulatedLine();
		
	private:
		

		
		const static int squareSize=18;
		
		//How many blocks wide and high
		const static int width = 9;
		const static int height = 21;
		
		static Square* arrGameField[width+1][height+1];
		//static int arrBitGameField[20];
		
		const static int bitEmpty = 0x0;
		const static int bitFull = 0x3FF;
		const static int offsetX = 164;
		const static int offsetY = 18;
		
		const static bool drawGrid = false;
		
		static bool lineEmpty(int y);
		static bool lineFull(int y);
		
		
		
	
};
#endif

