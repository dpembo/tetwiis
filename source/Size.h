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


#ifndef SIZE_HPP
#define SIZE_HPP
class Size
{
	public:
		Size();
		Size(int in_w,int in_h){width=in_w;height=in_h;};
		~Size();
		int getWidth()const {return width;};
		int getHeight()const {return height;};
		void setWidth(int in_w){width = in_w;};
		void setHeight(int in_h){height = in_h;};

		
	private:
		int width;
		int height;
};
#endif

