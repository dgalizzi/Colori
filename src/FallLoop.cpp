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

#include "FallLoop.hpp"
#include "DestroyLoop.hpp"
#include <iostream>

FallLoop::FallLoop(sf::RenderWindow *theRender, Board *theBoard)
: Loop(theRender), mBoard(theBoard)
{
	mMatrix = mBoard->GetMatrix();
	Check();
	mClock.Reset();
	
	// If there are floating blocks, a new check is needed.
	mNewCheckNeeded = !mList.empty();
	
	if (!mNewCheckNeeded)
	{
		End(); // No floating blocks
	}
}

void FallLoop::Step()
{
	
	if (mClock.GetElapsedTime() > 0.01f)
	{
		std::list<FloatingBlock>::iterator i = mList.begin();
		while (i != mList.end())
		{
			// Move every block
			(*i).mBlock->Move(sf::Vector2f(0, (*i).mSpeed * (*i).mClock.GetElapsedTime()));
	
			if ((*i).mBlock->GetPosition().y >= (*i).mLastY)
			{
				float x = (*i).mBlock->GetPosition().x;
				(*i).mBlock->SetPosition(sf::Vector2f(x, (*i).mLastY));
				
				// Erase and get the next one
				i = mList.erase(i);
				continue; // Don't increment the iterator twice
			}
			
			++i;
		}
		
		mClock.Reset();
	}
	
	mBoard->DrawBackground();
	mBoard->DrawNextColumn();
	mBoard->DrawCurrentColumn();
	mBoard->DrawColorfulBlocks(); // Colorful blocks, doesn't matter the current mode
	mBoard->DrawScore();	
	mRender->Display();
	mRender->Clear(sf::Color(240, 240, 240));

	if (mList.empty() && mNewCheckNeeded)
	{
		mBoard->PushLoop(new DestroyLoop(mRender, mBoard));
		End();
	}
}

void FallLoop::ProcessEvent(sf::Event &theEvent)
{
	mBoard->HandlePause(theEvent);
}

void FallLoop::Check()
{
	int empty = 0;
	float speed = 0.8f;
	
	// From left to right to top
	for (int j = mMatrix[0].size()-2; j >= 0; j --) // Before the last
	{
		for (int i = 0 ; i < mMatrix.size(); i ++)
		{
			empty = 0;
			
			// Empty cell?
			if (!mMatrix[i][j])
				continue;
				
			// How many empty cells are below
			while ((j+empty+1 < HEIGHT)        // Array's boundary
				&& (!mMatrix[i][j+empty+1]))
			{
				++ empty;
			}
				
			if (empty > 0)
			{
				FloatingBlock f;
				f.mBlock = &(**mMatrix[i][j]);
				f.mToMove = (float)empty;
				f.mLastY = (float)j + f.mToMove;
				f.mSpeed = speed /*sf::Randomizer::Random(0.01f, 0.05f)*/;
				f.mClock.Reset();
				
				//speed /= 1.4f;
				
				//(**mMatrix[i][j]).SetPosition(sf::Vector2f(i, j+empty)); // Instant move
				mList.push_back(f);
				
				// Move the block
				mMatrix[i][j+empty] = mMatrix[i][j];
				mMatrix[i][j] = NULL;
				
				
			}
		}
	}
}
