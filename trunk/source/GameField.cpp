/**
 *
 * Tetwiis
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 

//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
# include "GameField.h"
# include "Debug.h"
# include "Offset.h"
#include <grrlib.h>    




//------------------------------------------------------------------------------
// Externals
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------
Square* GameField::arrGameField[width+1][height+1];
//int GameField::arrBitGameField[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


//_______________________________________________________________________________
/**
 * Constructor
 */
GameField::GameField()
{
}


//_______________________________________________________________________________
/**
 * destructor
 */
GameField::~GameField()
{
}

void GameField::reset()
{
	int x,y;
	for(y=height;y>=0;y--)
	{
		for(x=width; x>=0; x--)
		{
			arrGameField[x][y]=0;
		}
	}
}

bool GameField::isEmpty(int x,int y)
{

	/*char* debugMessage = strdup("                                                              ");
	sprintf(debugMessage, "CALLED ISEMPTY X[%i] Y[%i] W[%i] H[%i]", x,y,width,height);		
	Debug::log((const char*)debugMessage);*/

	if(x<0)return false;
	else if(x>width)return false;
	else if(y > height)return false;
	//else if(y>=0 && (arrBitGameField[y]&(1<<x))!=0)return false;
	else if(y>=0 && arrGameField[x][y]!=NULL)return false;
	return true;
}

void GameField::stopSquare(Square* square)
{
	int x,y;
	x = square->getLocation().getX()/getSquareSize();
	y = square->getLocation().getY()/getSquareSize();


	

	//char* debugMessage = strdup("                                                              ");
	//sprintf(debugMessage, "STOPSQ X[%i] Y[%i]", x,y );		
	//Debug::log((const char*)debugMessage);
	

	if(x<0)return;
	if(x>width)return;
	if(y<0)return;
	if(y>height) return;
	
	
	//arrBitGameField[y] = arrBitGameField[y] | (1<<x);
	arrGameField[x][y] = square;
}

int GameField::firstPopulatedLine()
{
	for(int y=0;y<height;y++)
	{
		if(!lineEmpty(y))return y;
	}
	return -1;
}

bool GameField::lineFull(int y)
{
	int x;
	for(x=0;x<=width;x++)
	{
		if(arrGameField[x][y]==NULL)return false;
	}
	return true;
	
}

bool GameField::lineEmpty(int y)
{
	int x;
	for(x=0;x<=width;x++)
	{
		if(arrGameField[x][y]!=NULL)return false;
	}
	return true;
}

int GameField::checkLines()
{

	//char* debugMessage = strdup("                                                              ");
	
	int checkLinesResult=0; //Number of lines completed
	int y = height ;
	
	while(y>=0)
	{
	
		//sprintf(debugMessage, "checkLines Y[%i]",y);		
		//Debug::log((const char*)debugMessage);
		
		//Stop when a blank line is reached
		if(lineEmpty(y)==true)
		{

			//Debug::log(strdup("Stopping - found blank line"));
			y=0;
		}
		
		//if all bits of line are set then increment the counter
		//to clear the line and move all above lines down.
		if(lineFull(y)==true)
		{
			//Debug::log(strdup("Found full line"));		
			checkLinesResult++;
			
			//Move all lines down
			int index;
			for(index = y;index>=0;index--)
			{
				//sprintf(debugMessage, "Moving down [%i] to [%i]",index,index-1);		
				//Debug::log((const char*)debugMessage);
		
				//If current line is not first of gamefield
				///copy the line above
				if(index>0)
				{
				
					//Debug::log(strdup("copying bits"));				
					//Copy bits from line above
					//arrBitGameField[index] = (arrBitGameField[index-1]+0);
					
					//Copy each of the squares
					int x;
					for(x=0;x<=width;x++)
					{
						//sprintf(debugMessage, "Copying square x[%i]",x);		
						//Debug::log((const char*)debugMessage);
					
						//Copy square
						arrGameField[x][index] = arrGameField[x][index-1];
						//Update location of square
						
						//Debug::log(strdup("Updating location"));
						if(arrGameField[x][index]!=NULL)
						{
							//arrGameField[x][index]->getLocationInst()->setX(arrGameField[x][index]->getLocationInst()->getX());
							arrGameField[x][index]->getLocationInst()->setY(arrGameField[x][index]->getLocationInst()->getY()+squareSize);
						}
					}
				}
				else
				{
					//If current line is first line of gamefield
					//just clear the line!
					//Debug::log(strdup("current line is first line!"));
					//arrBitGameField[index]=bitEmpty;
					int x;
					for(x=0;x<=width;x++)
					{
						arrGameField[x][index] = NULL;
					}
				}
			}
		}
		else
		{
			y--;
		}
	}
	return checkLinesResult;
}



void GameField::redraw()
{

	
	int x,y;
	
	//char* debugMessage = strdup("                                                              ");
	//sprintf(debugMessage, "REDRAW W[%i] H[%i]",width,height);		
	//Debug::log((const char*)debugMessage);
	
	
	for(y=height;y>=0;y--)
	{
		
		//sprintf(debugMessage, "On Y[%i]",y);		
		//Debug::log((const char*)debugMessage);	
		/*if(lineEmpty(y)!=true)
		{*/
			
			//Debug::log(strdup("not empty!"));			
			for(x=width; x>=0; x--)
			{
				if(drawGrid)
				{
					drawRectangle( (x*getSquareSize())+Offset::getOffsetX(),(y*getSquareSize())+Offset::getOffsetY(),getSquareSize(),getSquareSize(),0x444444FF,0);
				}	
				//sprintf(debugMessage, "y[%i] Not Empty X[%i] sq exists[%i]" ,y,x,arrGameField[x][y]!=NULL);		
				//Debug::log((const char*)debugMessage);				
				if(arrGameField[x][y]!= NULL )arrGameField[x][y]->show();
			}
		/*}
		else
		{
		//	Debug::log(strdup("empty!"));			
			for(x=width; x>=0; x--)
			{
				drawRectangle(x*squareSize+Offset::getOffsetX(),y*squareSize+Offset::getOffsetY(),10,10,0x999999FF,0);
			}
		}*/
	}
}


 //_______________________________________________________________________________
/*
 * Draws a rectangle
 */
void GameField::drawRectangle(int x,int y,int width,int height, u32 color, bool fill)
{
	int fillint=0;
	if(fill)fillint=1;
	GRRLIB_Rectangle(x,y,width,height,color,fillint);
}
