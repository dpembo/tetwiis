/**
 *
 * Tetwiis
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 

//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
#include "Block.h"
#include <grrlib.h>    
#include "fonts/BMfont5.h"
#include "images/img_cursor.h"
#include "debug.h"
#include "Offset.h"




//------------------------------------------------------------------------------
// Externals
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------
#define CLOCKWISE 1
#define ANTICLOCKWISE -1

//_______________________________________________________________________________
/**
 * Constructor
 */

Block::Block(Point location, int newBlockType)
{
	squareSize = GameField::getSquareSize();
	statusRotation = north;
	blockType = 0;
	srand((unsigned)time(0)); 
	int random_integer;
	//Create the new block.  If undefined get a random block!
	if(newBlockType == bl_Undefined)
	{
		random_integer = (rand()%7)+1; 
		blockType = random_integer;
		
	}
	else
	{
		blockType = newBlockType;
	}
	
	
	/*char* debugMessage = strdup("                                                              ");
	sprintf(debugMessage, "NEW BLOCK ADDED %i", blockType);		
	Debug::log((const char*)debugMessage);*/
	

	sq1 = new Square(location.getX(),location.getY(),squareSize,squareSize,getColor(blockType),0x000000FF);
	sq2 = new Square(location.getX(),location.getY(),squareSize,squareSize,getColor(blockType),0x000000FF);
	sq3 = new Square(location.getX(),location.getY(),squareSize,squareSize,getColor(blockType),0x000000FF);
	sq4 = new Square(location.getX(),location.getY(),squareSize,squareSize,getColor(blockType),0x000000FF);
	
	

	
	switch (blockType)
	{
		//  ##
		//  ##
		case bl_Square:
		{
			sq1p = new Point(location.getX(),location.getY());
			sq2p = new Point(location.getX()+squareSize,location.getY());
			sq3p = new Point(location.getX(),location.getY()+squareSize);
			sq4p = new Point(location.getX()+squareSize,location.getY()+squareSize);

		}
		break;
		
		//  #
		//  @
		//  #
		//  #
		case bl_Line:
		{
			sq1p = new Point(location.getX(),location.getY()-squareSize);
			sq2p = new Point(location.getX(),location.getY());
			sq3p = new Point(location.getX(),location.getY()+squareSize);
			sq4p = new Point(location.getX(),location.getY()+(squareSize*2));
		}
		break;
		
		//  #
		//  #
		// #@
		case bl_J:
		{
			sq1p = new Point(location.getX(),location.getY()-(squareSize*2));
			sq2p = new Point(location.getX(),location.getY()-squareSize);
			sq3p = new Point(location.getX(),location.getY());
			sq4p = new Point(location.getX()-squareSize,location.getY());
		}
		break;
		
		// #
		// # 
		// @#
		case bl_L:
		{
			sq1p = new Point(location.getX(),location.getY()-(squareSize*2));
			sq2p = new Point(location.getX(),location.getY()-squareSize);
			sq3p = new Point(location.getX(),location.getY());
			sq4p = new Point(location.getX()+squareSize,location.getY());
		}
		break;
		
		// #@#
		//  #
		case bl_T:
		{
			sq1p = new Point(location.getX()-squareSize,location.getY());
			sq2p = new Point(location.getX(),location.getY());
			sq3p = new Point(location.getX()+squareSize,location.getY());
			sq4p = new Point(location.getX(),location.getY()+squareSize);		
		}
		break;

		// #@
		//  ##
		case bl_Z:
		{
			sq1p = new Point(location.getX()-squareSize,location.getY());
			sq2p = new Point(location.getX(),location.getY());
			sq3p = new Point(location.getX(),location.getY()+squareSize);
			sq4p = new Point(location.getX()+squareSize,location.getY()+squareSize);		
		}
		break;
		
		//   @#
		//  ##
		case bl_S:
		{
			sq1p = new Point(location.getX()+squareSize,location.getY());
			sq2p = new Point(location.getX(),location.getY());
			sq3p = new Point(location.getX()-squareSize,location.getY()+squareSize);
			sq4p = new Point(location.getX(),location.getY()+squareSize);				
		}
		break;

		default:
		{
			sq1p = new Point(location.getX(),location.getY());
			sq2p = new Point(location.getX()+squareSize,location.getY());
			sq3p = new Point(location.getX(),location.getY()+squareSize);
			sq4p = new Point(location.getX()+squareSize,location.getY()+squareSize);		
		}
	};
	
	sq1->setLocation(*sq1p);
	sq2->setLocation(*sq2p);
	sq3->setLocation(*sq3p);
	sq4->setLocation(*sq4p);
	
	
}

 
//_______________________________________________________________________________
/**
 * destructor
 */
Block::~Block()
{
	delete(sq1);
	delete(sq2);
	delete(sq3);
	delete(sq4);
	
	delete(sq1p);
	delete(sq2p);
	delete(sq3p);
	delete(sq4p);
	
}

//_______________________________________________________________________________
/**
 * Move down
 */
bool Block::down()
{
	
	//Debug::log(strdup("down"));
	
	//If there's no block below current one, go down
	if(
		GameField::isEmpty(sq1->getLocationInst()->getX()/squareSize,sq1->getLocationInst()->getY()/squareSize+1) &&
		GameField::isEmpty(sq2->getLocationInst()->getX()/squareSize,sq2->getLocationInst()->getY()/squareSize+1) &&
		GameField::isEmpty(sq3->getLocationInst()->getX()/squareSize,sq3->getLocationInst()->getY()/squareSize+1) &&
		GameField::isEmpty(sq4->getLocationInst()->getX()/squareSize,sq4->getLocationInst()->getY()/squareSize+1)
	)
	{
		hide();
		//Move down 1
		sq1->getLocationInst()->setY(sq1->getLocationInst()->getY()+squareSize);
		sq2->getLocationInst()->setY(sq2->getLocationInst()->getY()+squareSize);
		sq3->getLocationInst()->setY(sq3->getLocationInst()->getY()+squareSize);
		sq4->getLocationInst()->setY(sq4->getLocationInst()->getY()+squareSize);
		
		show();
		
		return true;
	}
	else
	{
		//If there is a block in the way, don't go down, and add the squares to the game controlling array
		GameField::stopSquare(sq1);
		GameField::stopSquare(sq2);
		GameField::stopSquare(sq3);
		GameField::stopSquare(sq4);
		return false;
	}
	
	
}

//_______________________________________________________________________________
/**
 * Move left
 */
bool Block::left()
{
	
	//is there a block to the left of the current one?
	if(
		GameField::isEmpty(sq1->getLocationInst()->getX()/squareSize-1,sq1->getLocationInst()->getY()/squareSize) &&
		GameField::isEmpty(sq2->getLocationInst()->getX()/squareSize-1,sq2->getLocationInst()->getY()/squareSize) &&
		GameField::isEmpty(sq3->getLocationInst()->getX()/squareSize-1,sq3->getLocationInst()->getY()/squareSize) &&
		GameField::isEmpty(sq4->getLocationInst()->getX()/squareSize-1,sq4->getLocationInst()->getY()/squareSize)
	)
	{
		hide();
		
		//move left 1
		sq1->getLocationInst()->setX(sq1->getLocationInst()->getX()-squareSize);
		sq2->getLocationInst()->setX(sq2->getLocationInst()->getX()-squareSize);
		sq3->getLocationInst()->setX(sq3->getLocationInst()->getX()-squareSize);
		sq4->getLocationInst()->setX(sq4->getLocationInst()->getX()-squareSize);
		
		show();
		return true;
	}
	else
	{
		return false;
	}
}


//_______________________________________________________________________________
/**
 * Move right
 */
bool Block::right()
{
	
	//is there a block to the right of the current one?
	if(
		GameField::isEmpty(sq1->getLocationInst()->getX()/squareSize+1,sq1->getLocationInst()->getY()/squareSize) &&
		GameField::isEmpty(sq2->getLocationInst()->getX()/squareSize+1,sq2->getLocationInst()->getY()/squareSize) &&
		GameField::isEmpty(sq3->getLocationInst()->getX()/squareSize+1,sq3->getLocationInst()->getY()/squareSize) &&
		GameField::isEmpty(sq4->getLocationInst()->getX()/squareSize+1,sq4->getLocationInst()->getY()/squareSize)
	)
	{
		hide();
		
		//move right 1
		sq1->getLocationInst()->setX(sq1->getLocationInst()->getX()+squareSize);
		sq2->getLocationInst()->setX(sq2->getLocationInst()->getX()+squareSize);
		sq3->getLocationInst()->setX(sq3->getLocationInst()->getX()+squareSize);
		sq4->getLocationInst()->setX(sq4->getLocationInst()->getX()+squareSize);
		
		show();
		return true;
	}
	else
	{
		return false;
	}
}



//_______________________________________________________________________________
/**
 * rotate - check if the block needs to be moved left/right if its on the end
 * so that it can rotate.
 * direction 1= clockwise
 * direction -1 = anticlockwise
 */
void Block::rotate(int direction)
{
	
	
	//First is its x on 0
	minX = getSquare1()->getLocationInst()->getX() + 0;
	maxX = getSquare1()->getLocationInst()->getX() + 0;
	if(minX!=0)minX= getSquare2()->getLocationInst()->getX();
	if(minX!=0)minX= getSquare3()->getLocationInst()->getX();
	if(minX!=0)minX= getSquare4()->getLocationInst()->getX();
	
	if(getSquare2()->getLocationInst()->getX() > maxX)maxX= getSquare2()->getLocationInst()->getX();
	if(getSquare3()->getLocationInst()->getX() > maxX)maxX= getSquare3()->getLocationInst()->getX();
	if(getSquare4()->getLocationInst()->getX() > maxX)maxX= getSquare4()->getLocationInst()->getX();
	
	
	rotated = doRotate(0,direction);
	
	
	if(rotated==false)
	{
	
			
			//char* debugMessage = strdup("                                                              ");
			//sprintf(debugMessage, "minx [%i] maxX [%i] count[%i]\n",minX, maxX,maxX/18);		
			//Debug::log((const char*)debugMessage);
			if(minX==0 || (blockType==bl_J && minX==squareSize))
			{
				//Add one to the x and see it if will rotate?
				rotated=doRotate(squareSize,direction);
				if(rotated==false && blockType==bl_J)
				{
					rotated=doRotate(squareSize*2,direction);
				}
				
			}
			
			if( (maxX==(9*squareSize)) || (blockType==bl_J&& maxX==(8*squareSize)) || (blockType==bl_Line && maxX==(8*squareSize)) )
			{
				rotated=doRotate(0-squareSize,direction);
				
				
				if(rotated==false && blockType==bl_J)
				{
					rotated=doRotate(0-(squareSize*2),direction);
				}
				
				if(rotated==false && blockType==bl_Line)
				{
					rotated=doRotate(0-(squareSize*2),direction);
				}
			}
	}
}

//_______________________________________________________________________________
/**
 * Draw Blocks 
 *  
 *  1
 *  |
 *4-+-2
 *  |
 *  3
 **/
 
 void Block::drawT(int direction)
 {
  	switch(direction)
	{
		case north:
		{
			getSquare1()->getLocationInst()->setX(oldp2x-squareSize);
			getSquare1()->getLocationInst()->setY(oldp2y);
			getSquare2()->getLocationInst()->setX(oldp2x);
			getSquare2()->getLocationInst()->setY(oldp2y);
			getSquare3()->getLocationInst()->setX(oldp2x+squareSize);
			getSquare3()->getLocationInst()->setY(oldp2y);
			getSquare4()->getLocationInst()->setX(oldp2x);
			getSquare4()->getLocationInst()->setY(oldp2y+squareSize);			
		}
		break;
		
		case east:
		{
			getSquare1()->getLocationInst()->setX(oldp2x);
			getSquare1()->getLocationInst()->setY(oldp2y-squareSize);
			getSquare2()->getLocationInst()->setX(oldp2x);
			getSquare2()->getLocationInst()->setY(oldp2y);
			getSquare3()->getLocationInst()->setX(oldp2x);
			getSquare3()->getLocationInst()->setY(oldp2y+squareSize);
			getSquare4()->getLocationInst()->setX(oldp2x-squareSize);
			getSquare4()->getLocationInst()->setY(oldp2y);			
		}
		break;
		
		case south:
		{
			getSquare1()->getLocationInst()->setX(oldp2x+squareSize);
			getSquare1()->getLocationInst()->setY(oldp2y);
			getSquare2()->getLocationInst()->setX(oldp2x);
			getSquare2()->getLocationInst()->setY(oldp2y);
			getSquare3()->getLocationInst()->setX(oldp2x-squareSize);
			getSquare3()->getLocationInst()->setY(oldp2y);
			getSquare4()->getLocationInst()->setX(oldp2x);
			getSquare4()->getLocationInst()->setY(oldp2y-squareSize);	
		}
		break;
		
		case west:
		{
			getSquare1()->getLocationInst()->setX(oldp2x);
			getSquare1()->getLocationInst()->setY(oldp2y+squareSize);
			getSquare2()->getLocationInst()->setX(oldp2x);
			getSquare2()->getLocationInst()->setY(oldp2y);
			getSquare3()->getLocationInst()->setX(oldp2x);
			getSquare3()->getLocationInst()->setY(oldp2y-squareSize);
			getSquare4()->getLocationInst()->setX(oldp2x+squareSize);
			getSquare4()->getLocationInst()->setY(oldp2y);	
		}
		break;
	}
 }
 
 void Block::drawL(int direction)
 {
 	switch(direction)
	{
		case north:
		{
			getSquare1()->getLocationInst()->setX(oldp3x);
			getSquare1()->getLocationInst()->setY(oldp3y-(squareSize*2));
			getSquare2()->getLocationInst()->setX(oldp3x);
			getSquare2()->getLocationInst()->setY(oldp3y-squareSize);
			getSquare3()->getLocationInst()->setX(oldp3x);
			getSquare3()->getLocationInst()->setY(oldp3y);
			getSquare4()->getLocationInst()->setX(oldp3x+squareSize);
			getSquare4()->getLocationInst()->setY(oldp3y);		
		}
		break;
		
		case east:
		{
			getSquare1()->getLocationInst()->setX(oldp3x+(squareSize*2));
			getSquare1()->getLocationInst()->setY(oldp3y);
			getSquare2()->getLocationInst()->setX(oldp3x+squareSize);
			getSquare2()->getLocationInst()->setY(oldp3y);
			getSquare3()->getLocationInst()->setX(oldp3x);
			getSquare3()->getLocationInst()->setY(oldp3y);
			getSquare4()->getLocationInst()->setX(oldp3x);
			getSquare4()->getLocationInst()->setY(oldp3y+squareSize);		
		}
		break;
		
		case south:
		{
			getSquare1()->getLocationInst()->setX(oldp3x);
			getSquare1()->getLocationInst()->setY(oldp3y+(squareSize*2));
			getSquare2()->getLocationInst()->setX(oldp3x);
			getSquare2()->getLocationInst()->setY(oldp3y+squareSize);
			getSquare3()->getLocationInst()->setX(oldp3x);
			getSquare3()->getLocationInst()->setY(oldp3y);
			getSquare4()->getLocationInst()->setX(oldp3x-squareSize);
			getSquare4()->getLocationInst()->setY(oldp3y);						
		}
		break;
		
		case west:
		{
			getSquare1()->getLocationInst()->setX(oldp3x-(squareSize*2));
			getSquare1()->getLocationInst()->setY(oldp3y);
			getSquare2()->getLocationInst()->setX(oldp3x-squareSize);
			getSquare2()->getLocationInst()->setY(oldp3y);
			getSquare3()->getLocationInst()->setX(oldp3x);
			getSquare3()->getLocationInst()->setY(oldp3y);
			getSquare4()->getLocationInst()->setX(oldp3x);
			getSquare4()->getLocationInst()->setY(oldp3y-squareSize);				
		
		}
		break;
	}	
 }
 void Block::drawJ(int direction)
 {
	//the oldp1-4x and oldp1-4y should be available.
	switch(direction)
	{
		//North
		case north:
		{
			getSquare1()->getLocationInst()->setX(oldp3x);
			getSquare1()->getLocationInst()->setY(oldp3y-(squareSize*2));
			getSquare2()->getLocationInst()->setX(oldp3x);
			getSquare2()->getLocationInst()->setY(oldp3y-squareSize);
			getSquare3()->getLocationInst()->setX(oldp3x);
			getSquare3()->getLocationInst()->setY(oldp3y);
			getSquare4()->getLocationInst()->setX(oldp3x-squareSize);
			getSquare4()->getLocationInst()->setY(oldp3y);	
		}
		break;
		
		//East
		case east:
		{
			getSquare1()->getLocationInst()->setX(oldp3x+(squareSize*2));
			getSquare1()->getLocationInst()->setY(oldp3y);
			getSquare2()->getLocationInst()->setX(oldp3x+squareSize);
			getSquare2()->getLocationInst()->setY(oldp3y);
			getSquare3()->getLocationInst()->setX(oldp3x);
			getSquare3()->getLocationInst()->setY(oldp3y);
			getSquare4()->getLocationInst()->setX(oldp3x);
			getSquare4()->getLocationInst()->setY(oldp3y-squareSize);		
		}
		break;
		
		//South
		case south:
		{
			getSquare1()->getLocationInst()->setX(oldp3x);
			getSquare1()->getLocationInst()->setY(oldp3y+(squareSize*2));
			getSquare2()->getLocationInst()->setX(oldp3x);
			getSquare2()->getLocationInst()->setY(oldp3y+squareSize);
			getSquare3()->getLocationInst()->setX(oldp3x);
			getSquare3()->getLocationInst()->setY(oldp3y);
			getSquare4()->getLocationInst()->setX(oldp3x+squareSize);
			getSquare4()->getLocationInst()->setY(oldp3y);			
		}
		break;
		
		//West
		case west:
		{
			getSquare1()->getLocationInst()->setX(oldp3x-(squareSize*2));
			getSquare1()->getLocationInst()->setY(oldp3y);
			getSquare2()->getLocationInst()->setX(oldp3x-squareSize);
			getSquare2()->getLocationInst()->setY(oldp3y);
			getSquare3()->getLocationInst()->setX(oldp3x);
			getSquare3()->getLocationInst()->setY(oldp3y);
			getSquare4()->getLocationInst()->setX(oldp3x);
			getSquare4()->getLocationInst()->setY(oldp3y+squareSize);			
		}
		break;		
		
	}
 }
//_______________________________________________________________________________
/**
 * do the rotate
 */
bool Block::doRotate(int xadjust,int direction)
{
	//Debug::log(strdup("rotate"));
	//First store old positions
	
	/*Point oldp1 = getSquare1()->getLocation();
	Point oldp2 = getSquare2()->getLocation();
	Point oldp3 = getSquare3()->getLocation();
	Point oldp4 = getSquare4()->getLocation();*/
	

	oldp1x = (getSquare1()->getLocationInst()->getX())+(xadjust);
	oldp2x = (getSquare2()->getLocationInst()->getX())+(xadjust);
	oldp3x = (getSquare3()->getLocationInst()->getX())+(xadjust);
	oldp4x = (getSquare4()->getLocationInst()->getX())+(xadjust);
	
	oldp1y = getSquare1()->getLocationInst()->getY();
	oldp2y = getSquare2()->getLocationInst()->getY();
	oldp3y = getSquare3()->getLocationInst()->getY();
	oldp4y = getSquare4()->getLocationInst()->getY();
	
	int oldStatusRotation = statusRotation;
	
	hide();
	
	switch(blockType)
	{
		//  ##
		//  ##
		case bl_Square:
		{
			//Square doesn't rotate!
		}
		break;
		
		//  #
		//  @
		//  #
		//  #
		case bl_Line:
		{
			//Line rotates around block 2
			switch(statusRotation)
			{
				// #@##
				case north:
				{
					statusRotation = east;
					getSquare1()->getLocationInst()->setX(oldp2x-squareSize);
					getSquare1()->getLocationInst()->setY(oldp2y);
					
					getSquare2()->getLocationInst()->setX(oldp2x);
					getSquare2()->getLocationInst()->setY(oldp2y);
					
					getSquare3()->getLocationInst()->setX(oldp2x+squareSize);
					getSquare3()->getLocationInst()->setY(oldp2y);
					
					getSquare4()->getLocationInst()->setX(oldp2x+(squareSize*2));
					getSquare4()->getLocationInst()->setY(oldp2y);
					
				}
				break;
				
				case east:
				{
					statusRotation = north;
					getSquare1()->getLocationInst()->setX(oldp2x);
					getSquare1()->getLocationInst()->setY(oldp2y-squareSize);
					
					getSquare2()->getLocationInst()->setX(oldp2x);
					getSquare2()->getLocationInst()->setY(oldp2y);
					
					getSquare3()->getLocationInst()->setX(oldp2x);
					getSquare3()->getLocationInst()->setY(oldp2y+squareSize);
					
					getSquare4()->getLocationInst()->setX(oldp2x);
					getSquare4()->getLocationInst()->setY(oldp2y+(squareSize*2));					
				}
				break;
			
			}
		}
		break;
		
		//  #
		//  #
		// #@
		case bl_J:
		{
			switch(statusRotation)
			{
				case north:
				{
					if(direction==CLOCKWISE)
					{
						statusRotation = east;
						drawJ(east);				
					}
					else
					{
						statusRotation = west;
						drawJ(west);
					}
					
				}
				break;
				
				case east:
				{
					if(direction==CLOCKWISE)
					{
						statusRotation = south;
						drawJ(south);		
					}					
					else
					{
						statusRotation = north;
						drawJ(north);							
					}
					

				}
				break;
				
				case south:
				{
					if(direction==CLOCKWISE)
					{
						statusRotation = west;
						drawJ(west);	
					}					
					else
					{
						statusRotation = east;
						drawJ(east);						
					}				
				
				}
				break;
				
				case west:
				{
					if(direction==CLOCKWISE)
					{
						statusRotation = north;
						drawJ(north);						
					}					
					else
					{
						statusRotation = south;
						drawJ(south);						
					}				
				}
				break;
			}	
		}
		break;
		
		// #
		// # 
		// @#
		case bl_L:
		{
			switch(statusRotation)
			{
				case north:
				{
					if(direction==CLOCKWISE)
					{
						statusRotation = east;
						drawL(east);				
					}
					else
					{
						statusRotation = west;
						drawL(west);
					}
					
				}
				break;
				
				case east:
				{
					if(direction==CLOCKWISE)
					{
						statusRotation = south;
						drawL(south);		
					}					
					else
					{
						statusRotation = north;
						drawL(north);							
					}
					

				}
				break;
				
				case south:
				{
					if(direction==CLOCKWISE)
					{
						statusRotation = west;
						drawL(west);	
					}					
					else
					{
						statusRotation = east;
						drawL(east);						
					}				
				
				}
				break;
				
				case west:
				{
					if(direction==CLOCKWISE)
					{
						statusRotation = north;
						drawL(north);						
					}					
					else
					{
						statusRotation = south;
						drawL(south);						
					}				
				}
				break;
			}
		}
		break;
		
		// #@#
		//  #
		case bl_T:
		{
				switch(statusRotation)
			{
				case north:
				{
					if(direction==CLOCKWISE)
					{
						statusRotation = east;
						drawT(east);				
					}
					else
					{
						statusRotation = west;
						drawT(west);
					}
					
				}
				break;
				
				case east:
				{
					if(direction==CLOCKWISE)
					{
						statusRotation = south;
						drawT(south);		
					}					
					else
					{
						statusRotation = north;
						drawT(north);							
					}
					

				}
				break;
				
				case south:
				{
					if(direction==CLOCKWISE)
					{
						statusRotation = west;
						drawT(west);	
					}					
					else
					{
						statusRotation = east;
						drawT(east);						
					}				
				
				}
				break;
				
				case west:
				{
					if(direction==CLOCKWISE)
					{
						statusRotation = north;
						drawT(north);						
					}					
					else
					{
						statusRotation = south;
						drawT(south);						
					}				
				}
				break;
			}
		}
		break;

		// #@
		//  ##
		case bl_Z:
		{
			switch(statusRotation)
			{
				//  #
				// #@
				// #
				case north:
				{
					statusRotation = east;
					getSquare1()->getLocationInst()->setX(oldp2x);
					getSquare1()->getLocationInst()->setY(oldp2y-squareSize);
					
					getSquare2()->getLocationInst()->setX(oldp2x);
					getSquare2()->getLocationInst()->setY(oldp2y);
					
					getSquare3()->getLocationInst()->setX(oldp2x-squareSize);
					getSquare3()->getLocationInst()->setY(oldp2y+squareSize);
					
					getSquare4()->getLocationInst()->setX(oldp2x-squareSize);
					getSquare4()->getLocationInst()->setY(oldp2y);
				}
				break;
				
				//  #@
				//   ##
				case east:
				{
					statusRotation = north;
					getSquare1()->getLocationInst()->setX(oldp2x-squareSize);
					getSquare1()->getLocationInst()->setY(oldp2y);
					
					getSquare2()->getLocationInst()->setX(oldp2x);
					getSquare2()->getLocationInst()->setY(oldp2y);
					
					getSquare3()->getLocationInst()->setX(oldp2x+squareSize);
					getSquare3()->getLocationInst()->setY(oldp2y+squareSize);
					
					getSquare4()->getLocationInst()->setX(oldp2x);
					getSquare4()->getLocationInst()->setY(oldp2y+squareSize);					
				}
				break;
			}
		}
		break;
		
		//   @#
		//  ##
		case bl_S:
		{
			switch(statusRotation)
			{
				//  #
				//  @#
				//   #
				case north:
				{
					statusRotation = east;
					getSquare1()->getLocationInst()->setX(oldp2x);
					getSquare1()->getLocationInst()->setY(oldp2y-squareSize);
					
					getSquare2()->getLocationInst()->setX(oldp2x);
					getSquare2()->getLocationInst()->setY(oldp2y);
					
					getSquare3()->getLocationInst()->setX(oldp2x+squareSize);
					getSquare3()->getLocationInst()->setY(oldp2y+squareSize);
					
					getSquare4()->getLocationInst()->setX(oldp2x+squareSize);
					getSquare4()->getLocationInst()->setY(oldp2y);
					
				}
				break;
				
				//   ##
				//  #@
				case east:
				{
					statusRotation = north;
					getSquare1()->getLocationInst()->setX(oldp2x-squareSize);
					getSquare1()->getLocationInst()->setY(oldp2y);
					
					getSquare2()->getLocationInst()->setX(oldp2x);
					getSquare2()->getLocationInst()->setY(oldp2y);
					
					getSquare3()->getLocationInst()->setX(oldp2x+squareSize);
					getSquare3()->getLocationInst()->setY(oldp2y-squareSize);
					
					getSquare4()->getLocationInst()->setX(oldp2x);
					getSquare4()->getLocationInst()->setY(oldp2y-squareSize);					
				}
				break;	
			}
		}
		break;

		default:
		{
		}
	}	
	
	//Need to check here for overlap
	//and move block back it there is
	//an overlap
	
		
	if(
		(GameField::isEmpty(sq1->getLocationInst()->getX()/squareSize,sq1->getLocationInst()->getY()/squareSize)) &&
		(GameField::isEmpty(sq2->getLocationInst()->getX()/squareSize,sq2->getLocationInst()->getY()/squareSize)) &&
		(GameField::isEmpty(sq3->getLocationInst()->getX()/squareSize,sq3->getLocationInst()->getY()/squareSize)) &&
		(GameField::isEmpty(sq4->getLocationInst()->getX()/squareSize,sq4->getLocationInst()->getY()/squareSize))
	)
	{
		//Debug::log(strdup("rotate successful"));	
		show();
		return true;
	}
	else
	{
		//Debug::log(strdup("Rotate failed - move back!"));
		statusRotation = oldStatusRotation;
		
		sq1->getLocationInst()->setX(oldp1x-(xadjust));
		sq2->getLocationInst()->setX(oldp2x-(xadjust));
		sq3->getLocationInst()->setX(oldp3x-(xadjust));
		sq4->getLocationInst()->setX(oldp4x-(xadjust));
		
		sq1->getLocationInst()->setY(oldp1y);
		sq2->getLocationInst()->setY(oldp2y);
		sq3->getLocationInst()->setY(oldp3y);
		sq4->getLocationInst()->setY(oldp4y);
		
		//(Should I delete oldp1,2,3 & 4 here or will it fry the location???  :S )
		/*
		delete(oldp1);
		delete(oldp2);
		delete(oldp3);
		delete(oldp4);
		*/
		return false;
	}
	
		
	
	
}

//_______________________________________________________________________________
/**
 * show block
 */
void Block::show()
{
	sq1->show();
	sq2->show();
	sq3->show();
	sq4->show();
}

//_______________________________________________________________________________
/**
 * hide block
 */
void Block::hide()
{
	sq1->hide();
	sq2->hide();
	sq3->hide();
	sq4->hide();
}

u32 Block::getColor(int blockType)
{
	switch(blockType)
	{
		case 1:
			return 0XFF0000FF;
		case 2:
			return 0X00FF00FF;
		case 3:
			return 0X0000FFFF;
		case 4:
			return 0XFFFF00FF;
		case 5:
			return 0x00FFFFFF;
		case 6:
			return 0XFF00FFFF;
		case 7:
			return 0XCCCCCCFF;
	}
	
	return 0xFF0000FF;
}


//_______________________________________________________________________________
/**
 * hide block
 */
int Block::top()
{
	int y1 = sq1->getLocation().getY();
	int y2 = sq2->getLocation().getY();
	int y3 = sq3->getLocation().getY();
	int y4 = sq4->getLocation().getY();
	
	
	int min = y1;
	if(y2<min)min=y2;
	if(y3<min)min=y3;
	if(y4<min)min=y4;
	
	return min;
}





void Block::drawDropPosition()
{

	posy1 = sq1->getLocationInst()->getY()/squareSize;
	posy2 = sq2->getLocationInst()->getY()/squareSize;
	posy3 = sq3->getLocationInst()->getY()/squareSize;
	posy4 = sq4->getLocationInst()->getY()/squareSize;	
	
	//DAVES NEW CODE!
	topPos = posy1;
	if(posy2>topPos)topPos=posy2;
	if(posy3>topPos)topPos=posy3;
	if(posy4>topPos)topPos=posy4;
	
	//  |012345679|
	//0 |         |
	//1 |    *    |
	//2 |   ***   |
	//3 |         |
	//4 |         |
	//..|         |
	//18|         |
	//19|         |
	//  -----------
	//topPos contains lowest piece (with the highestY No
	
	
	
	
	
	//------------------------------------------------------------
	
	// OLD WORKING CODE!
	counter=0;
	for(counter = 0;counter<=GameField::getHeight();counter++)
	{
	
		
	//sprintf(debugMessage, "\n------------ [%i] --------------\n", counter);		
	//Debug::log((const char*)debugMessage);
	
	//printf(debugMessage, "\%i,%i,%i,%i\n", posy1,posy2,posy3,posy4);		
	//Debug::log((const char*)debugMessage);
	
		
		if(topPos==GameField::getHeight() || posy1 == GameField::getHeight()||posy2==GameField::getHeight()||posy3==GameField::getHeight()||posy4==GameField::getHeight())
		{
			break;
		}
		else
		{
			posy1++;
			posy2++;
			posy3++;
			posy4++;
			topPos++;
			
		}

	//sprintf(debugMessage, "\%i,%i,%i,%i\n", posy1,posy2,posy3,posy4);		
	//Debug::log((const char*)debugMessage);		
		
		if((GameField::isEmpty(sq1->getLocationInst()->getX()/squareSize,posy1) &&
		GameField::isEmpty(sq2->getLocationInst()->getX()/squareSize,posy2) &&
		GameField::isEmpty(sq3->getLocationInst()->getX()/squareSize,posy3) &&
		GameField::isEmpty(sq4->getLocationInst()->getX()/squareSize,posy4))==false)
		{
			
			posy1--;
			posy2--;
			posy3--;
			posy4--;
			//Debug::log("Gamefield is not empty at the four positions!\n");		
			break;
		}
		
	}
	
	GameField::drawRectangle( sq1->getLocationInst()->getX()+Offset::getOffsetX()+2,(posy1 * squareSize)+Offset::getOffsetY()+2,squareSize-4,squareSize-4,0x444444FF,0);
	GameField::drawRectangle( sq2->getLocationInst()->getX()+Offset::getOffsetX()+2,(posy2 * squareSize)+Offset::getOffsetY()+2,squareSize-4,squareSize-4,0x444444FF,0);
	GameField::drawRectangle( sq3->getLocationInst()->getX()+Offset::getOffsetX()+2,(posy3 * squareSize)+Offset::getOffsetY()+2,squareSize-4,squareSize-4,0x444444FF,0);
	GameField::drawRectangle( sq4->getLocationInst()->getX()+Offset::getOffsetX()+2,(posy4 * squareSize)+Offset::getOffsetY()+2,squareSize-4,squareSize-4,0x444444FF,0);

}



bool Block::checkStartNewBlock()
{
	if(
		GameField::isEmpty(sq1->getLocationInst()->getX()/squareSize+1,sq1->getLocationInst()->getY()/squareSize) &&
		GameField::isEmpty(sq2->getLocationInst()->getX()/squareSize+1,sq2->getLocationInst()->getY()/squareSize) &&
		GameField::isEmpty(sq3->getLocationInst()->getX()/squareSize+1,sq3->getLocationInst()->getY()/squareSize) &&
		GameField::isEmpty(sq4->getLocationInst()->getX()/squareSize+1,sq4->getLocationInst()->getY()/squareSize)
	)
	{
		return true;
	}
	else 
	{
		return false;
	}
	
}
