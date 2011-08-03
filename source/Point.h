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


#ifndef POINT_HPP
#define POINT_HPP
class Point
{
	public:
		Point();
		Point(int in_x,int in_y){x=in_x;y=in_y;};
		~Point();
		int getX()const {return x;};
		int getY()const {return y;};
		void setX(int in_x){x = in_x;};
		void setY(int in_y){y = in_y;};

		
	private:
		int x;
		int y;
};
#endif

