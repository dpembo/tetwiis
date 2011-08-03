/**
 *
 * Tetwiis
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 

//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
# include "Square.h"
# include "Offset.h"



//------------------------------------------------------------------------------
// Externals
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------

//_______________________________________________________________________________
/**
 * Constructor
 */
Square::Square()
{
	initialised = false;
}

//_______________________________________________________________________________
/**
 * Constructor
 */
Square::Square(int x,int y, int width, int height, u32 inforeColor, u32 inbackColor)
{
	Point alocation(x,y);
	Size asize(width,height);
	Color aforeColor(inforeColor);
	Color abackColor(inbackColor);
	
	setLocation(alocation);
	setSize(asize);
	setColor(aforeColor,abackColor);


	initialised = true;
}


 
//_______________________________________________________________________________
/**
 * destructor
 */
Square::~Square()
{

	
	
}

//_______________________________________________________________________________
/**
 * Show Methods
 */
 void Square::show()
 {
	//GRRLIB_Rectangle
	drawRectangle(location.getX()+Offset::getOffsetX(),location.getY()+Offset::getOffsetY(),size.getWidth(),size.getHeight(),foreColor.getColor(),true);
	
	u32 newCol = foreColor.getColor() + 10;
	drawRectangle(location.getX()+Offset::getOffsetX()+1,location.getY()+Offset::getOffsetY()+1,size.getWidth()-2,size.getHeight()-2,newCol,true);
	
	newCol = foreColor.getColor() +20;
	drawRectangle(location.getX()+Offset::getOffsetX()+2,location.getY()+Offset::getOffsetY()+2,size.getWidth()-4,size.getHeight()-4,newCol,true);
	
	newCol = foreColor.getColor() +30;
	drawRectangle(location.getX()+Offset::getOffsetX()+3,location.getY()+Offset::getOffsetY()+3,size.getWidth()-6,size.getHeight()-6,newCol,true);
 }
 
//_______________________________________________________________________________
/**
 * Hide Method
 */
 void Square::hide()
 {
	//GRRLIB_Rectangle(location.getX(),location.getY(),size.getWidth(),size.getHeight(),backColor.getColor(),0);
	drawRectangle(location.getX()+Offset::getOffsetX(),location.getY()+Offset::getOffsetY(),size.getWidth(),size.getHeight(),backColor.getColor(),true);
	
 }
 
 
 //_______________________________________________________________________________
/*
 * Draws a rectangle
 */
void Square::drawRectangle(int x,int y,int width,int height, u32 color, bool fill)
{

	//GRRLIB_Rectangle(x,y,width,height,color,fill?1:0);
	//Image is always 20,20 (though bottom 2 and right 2 pixels are transparent!
	SquareImageProvider::drawSquare(location.getX()+Offset::getOffsetX(),location.getY()+Offset::getOffsetY(),0,1,1,color);	
}
 
 
