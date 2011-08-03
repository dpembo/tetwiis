/**
 *
 * Tetwiis
 * (C)2009 http://www.pembo.co.uk
 *
 **/
 

//------------------------------------------------------------------------------
// Headers
//------------------------------------------------------------------------------
# include "BlockList.h"

//------------------------------------------------------------------------------
// Externals
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Globals
//------------------------------------------------------------------------------


//_______________________________________________________________________________
/**
 * constructor
 */
BlockList::BlockList()
{
	heldBlockType = -1;
	
}
 
//_______________________________________________________________________________
/**
 * destructor
 */
BlockList::~BlockList()
{
}


int BlockList::randomNumber()
{
	//return (rand()%7) +1;
	
	return (mtRand()%7)+1;
	
}

void BlockList::initialiseQueue()
{
	mtRand.seed((rand()%999999));
	nextBlocks.clear();
	nextBlocks.push_back(randomNumber());
	nextBlocks.push_back(randomNumber());
	nextBlocks.push_back(randomNumber());
	nextBlocks.push_back(randomNumber());
	nextBlocks.push_back(randomNumber());
	nextBlocks.push_back(randomNumber());

}

int BlockList::nextQueueItem()
{
	int result;
	result = nextBlocks.back() + 0;
	nextBlocks.pop_back();
	nextBlocks.insert(nextBlocks.begin(),randomNumber() );
	return result;
}


void BlockList::drawBlocks()
{
	int additionalYOffset1 = 0;
	int additionalYOffset2 = 0;
	int additionalYOffset3 = 0;
	int additionalYOffset4 = 0;
	int additionalYOffset5 = 0;
	int additionalYOffset0 = 0;
	
	int additionalXOffset1 = 0;
	int additionalXOffset2 = 0;
	int additionalXOffset3 = 0;
	int additionalXOffset4 = 0;
	int additionalXOffset5 = 0;
	int additionalXOffset0 = 0;
	
	int additionalXOffset = 0;
	int additionalYOffset = 0;
	
	//Move down J and L blocks by one block!
	if(nextBlocks.at(5)==3 || nextBlocks.at(5)==4)additionalYOffset5 = 23;
	if(nextBlocks.at(4)==3 || nextBlocks.at(4)==4)additionalYOffset4 = 23;
	if(nextBlocks.at(3)==3 || nextBlocks.at(3)==4)additionalYOffset3 = 23;
	if(nextBlocks.at(2)==3 || nextBlocks.at(2)==4)additionalYOffset2 = 23;
	if(nextBlocks.at(1)==3 || nextBlocks.at(1)==4)additionalYOffset1 = 23;
	if(nextBlocks.at(0)==3 || nextBlocks.at(0)==4)additionalYOffset0 = 23;
	
	if(nextBlocks.at(5)==1) additionalXOffset5 = -9;
	if(nextBlocks.at(4)==1) additionalXOffset4 = -9;
	if(nextBlocks.at(3)==1) additionalXOffset3 = -9;
	if(nextBlocks.at(2)==1) additionalXOffset2 = -9;
	if(nextBlocks.at(1)==1) additionalXOffset1 = -9;
	if(nextBlocks.at(0)==1) additionalXOffset0 = -9;
	
	if(nextBlocks.at(5)==3) additionalXOffset5 = 8;
	if(nextBlocks.at(4)==3) additionalXOffset4 = 8;
	if(nextBlocks.at(3)==3) additionalXOffset3 = 8;
	if(nextBlocks.at(2)==3) additionalXOffset2 = 8;
	if(nextBlocks.at(1)==3) additionalXOffset1 = 8;
	if(nextBlocks.at(0)==3) additionalXOffset0 = 8;
	
	if(nextBlocks.at(5)==4) additionalXOffset5 = -8;
	if(nextBlocks.at(4)==4) additionalXOffset4 = -8;
	if(nextBlocks.at(3)==4) additionalXOffset3 = -8;
	if(nextBlocks.at(2)==4) additionalXOffset2 = -8;
	if(nextBlocks.at(1)==4) additionalXOffset1 = -8;
	if(nextBlocks.at(0)==4) additionalXOffset0 = -8;
	
	Point p1(400 + additionalXOffset5 - Offset::getOffsetX(),65 + additionalYOffset5  - Offset::getOffsetY());
	Point p2(480 + additionalXOffset4 - Offset::getOffsetX(),65 + additionalYOffset4 - Offset::getOffsetY());
	Point p3(560 + additionalXOffset3 - Offset::getOffsetX(),65 + additionalYOffset3 - Offset::getOffsetY());
	Point p4(560 + additionalXOffset2 - Offset::getOffsetX(),65+90+ additionalYOffset2 - Offset::getOffsetY());
	Point p5(560 + additionalXOffset1 - Offset::getOffsetX(),65+90+90+ additionalYOffset1 - Offset::getOffsetY());
	Point p6(560 + additionalXOffset0 - Offset::getOffsetX(),65+90+90+90+ additionalYOffset0 - Offset::getOffsetY());
	
	
	//p1 = new Point(500,30);
	//block1 = new Block(p1,nextBlocks.at(5));
	block1 = new Block(p1,nextBlocks.at(5));
	block2 = new Block(p2,nextBlocks.at(4));
	block3 = new Block(p3,nextBlocks.at(3));
	block4 = new Block(p4,nextBlocks.at(2));
	block5 = new Block(p5,nextBlocks.at(1));
	block6 = new Block(p6,nextBlocks.at(0));
	
	block1->show();
	block2->show();
	block3->show();
	block4->show();
	block5->show();
	block6->show();
	
	delete(block1);
	delete(block2);
	delete(block3);
	delete(block4);
	delete(block5);
	delete(block6);
	
	if(heldBlockType>0)
	{
	
		if(heldBlockType==3 || heldBlockType==4)additionalYOffset = 23;
		if(heldBlockType==1) additionalXOffset = -9;
		if(heldBlockType==3) additionalXOffset = 8;
		if(heldBlockType==4) additionalXOffset = -8;
	
		Point h1(72 - Offset::getOffsetX() + additionalXOffset, 65 + additionalYOffset - Offset::getOffsetY());
		
		heldBlock = new Block(h1,heldBlockType);
		heldBlock->show();
		delete(heldBlock);
	}

}

int BlockList::holdBlock(int blockType)
{
	int tmp;
	tmp=heldBlockType;
	heldBlockType = blockType;
	return tmp;
}




