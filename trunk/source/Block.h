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
#include "Square.h"
#include "Point.h"
#include "GameField.h"


#ifndef BLOCK_HPP
#define BLOCK_HPP
class Block
{
	public:
		enum BlockTypes{ bl_Undefined,bl_Square,bl_Line,bl_J,bl_L,bl_T,bl_Z,bl_S};
		enum RotationDirections{ north,east,south,west};
		Block(Point location, int newBlockType);
		Block(Point location, int newBlockType, GRRLIB_texImg *tex_squareimage);
		~Block();
		
		bool down();
		bool left();
		bool right();
		

		void rotate(int direction);
		bool doRotate(int xadjust,int direction);
		void show();
		void hide();
		int getBlockType(){return blockType;};
		void setBlockType(int newBlockType){blockType=newBlockType;};
		
		bool checkStartNewBlock();
		
		Square* getSquare1(){return sq1;};
		Square* getSquare2(){return sq2;};
		Square* getSquare3(){return sq3;};
		Square* getSquare4(){return sq4;};
		
		void drawDropPosition();
		
		int top();

		
	private:
		Square* sq1;
		Square* sq2;
		Square* sq3;
		Square* sq4;
		
		Point* sq1p;
		Point* sq2p;
		Point* sq3p;
		Point* sq4p;
		
		//Used for the preview block!
		int posy1;
		int posy2;
		int posy3;
		int posy4;
		
		int start1;
		int start2;
		int start3;
		int start4;
		
		int counter;
		int topPos;
		
		int statusRotation;
		int squareSize;
		int blockType;
		int getDropPoint();
		u32 getColor(int blockType);
		
		bool rotated;
		int minX;
		int maxX;
		
		
		int oldp1x;
		int oldp2x;
		int oldp3x;
		int oldp4x;
		
		int oldp1y;
		int oldp2y;
		int oldp3y;
		int oldp4y;
		
		void drawJ(int direction);
		void drawL(int direction);
		void drawT(int direction);
		
};
#endif

