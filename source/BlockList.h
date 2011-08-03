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
#include "Block.h"
#include "Point.h"
#include "Offset.h"
#include <vector>
#include "mtrand.h"



#ifndef BLOCKLIST_HPP
#define BLOCKLIST_HPP
class BlockList
{
	public:
		BlockList();
		~BlockList();
		
		std::vector<int> nextBlocks;

		void initialiseQueue();
		int nextQueueItem();
		
		void drawBlocks();
		int holdBlock(int blockType);
		
		
		Block* block1;
		Block* block2;
		Block* block3;
		Block* block4;
		Block* block5;
		Block* block6;
		
		Block* heldBlock;
		int heldBlockType;
		
		
		
		
	private:
		MTRand_int32 mtRand;
		int randomNumber();


};
#endif

