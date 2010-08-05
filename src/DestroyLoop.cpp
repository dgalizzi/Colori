/* 
** Copyright (c) 2010, Diego D. Galizzi
**
** Permission to use, copy, modify, and/or distribute this software for any
** purpose with or without fee is hereby granted, provided that the above
** copyright notice and this permission notice appear in all copies.
** 
** THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
** WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
** MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
** ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
** WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
** ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
** OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include "DestroyLoop.hpp"
#include "FallLoop.hpp"

#include <iostream>

DestroyLoop::DestroyLoop(sf::RenderWindow *theRender, Board *theBoard)
: Loop(theRender), mBoard(theBoard), mFrame(0)
{
		// Get the matrix
		mMatrix = theBoard->GetMatrix();
		
		Check( 1,  0); // Right 
		//Check( 1, -1); // Right up
		//Check( 0, -1); // Up
		//Check(-1, -1); // Left up
		//Check(-1,  0); // Left
		Check(-1,  1); // Left down
		Check( 0,  1); // Down
		Check( 1,  1); // Right down
		
		mClock.Reset();
		
		// This is a new combo
		mBoard->AddCombo();
}

// true on valid
bool DestroyLoop::CheckBoundary(int x, int y)
{
	return !(x < 0 || x >= mMatrix.size() || y < 0 || y >= mMatrix[0].size());
}

void DestroyLoop::Step()
{
	// Draw the blocks
	mRender->Clear(sf::Color(240, 240, 240));
	mBoard->DrawBackground();
	mBoard->DrawCurrentColumn();
	mBoard->DrawColorfulBlocks(); // Colorful blocks, doesn't matter the current mode
	mBoard->DrawScore();
	mRender->Display();
	
	// Animate the blocks, then destroy them
	if (mClock.GetElapsedTime() > 0.03f)
	{
		mClock.Reset();
		++ mFrame;
		
		// New frame
		for (std::list< std::list<Block>::iterator* >::iterator i = mList.begin(); i != mList.end(); i ++)
		{
			(***i).SetFrame(mFrame);
		}
		
		// Last step?
		if (mFrame >= MAX_FRAME)
		{
		
			// Add score
			mBoard->AddScore( (int) (   mList.size() * (mList.size()/3) * mBoard->GetLevel() * (mBoard->GetCombo()*mBoard->GetCombo())    ));
			
			// Remove the destroyed blocks, using iterators makes possible to erase in constant time
			for (std::list< std::list<Block>::iterator* >::iterator i = mList.begin(); i != mList.end(); i ++)
			{
				mBoard->EraseBlock(**i);
			}
			
			// Make the floating blocks fall
			mBoard->PushLoop(new FallLoop(mRender, mBoard));
			
			// End this loop
			End();	
		}
	}
}

void DestroyLoop::ProcessEvent(sf::Event &theEvent)
{
}

void DestroyLoop::Check(int dirX, int dirY)
{

	sf::Color color;
	int matches; // Count of consecutive colors
	
	// The possible matches
	std::list<std::list<Block>::iterator*> possibleMatches;
	
	// From left to right to bottom
	for (int j = 0; j < mMatrix[0].size() ; j ++)
	{
		for (int i = 0 ; i < mMatrix.size(); i ++)
		{
			if (!mMatrix[i][j])
				continue; // NULL pointer, empty cell.
				
			possibleMatches.clear();
			color = (**mMatrix[i][j]).GetColor();
				
			// Itself
			possibleMatches.push_back(mMatrix[i][j]);
			matches = 1; 
			
			int ii = i+dirX;
			int jj = j+dirY;
			// Check for consecutive matching colors in the desired direction
			while (CheckBoundary(ii, jj) 
			   && (mMatrix[ii][jj]) // check for not-NULL iterator
			   && (**mMatrix[ii][jj]).GetColor() == color)
			{
				possibleMatches.push_back(mMatrix[ii][jj]);
				++ matches; 
				ii += dirX;
				jj += dirY;
			}
				
			
			if (matches >= NMATCH)
			{
				// Append the new matches, only if it doesn't exists already
				std::list<std::list<Block>::iterator*>::iterator it;
				
				for (std::list<std::list<Block>::iterator*>::iterator ii = possibleMatches.begin(); ii != possibleMatches.end() ; ii++)
				{
					it = mList.begin();
					
					// Search if already exists
					while (*it != *ii && it != mList.end())
						++ it;
					
					// If not found
					if (it == mList.end())
					{
						// Add it
						mList.push_back(*ii);
					}
				}
			}
		}
	}
}

