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

#include "GameOver.hpp"
#include "Config.hpp"

GameOver::GameOver(sf::RenderWindow *theRender, Board *theBoard)
: Loop(theRender), mBoard(theBoard)
{
	mClock.Reset();
	mBlocks = mBoard->GetBlocks();
	mIter = mBlocks.begin();
	
	std::string s;
	mGameOverImg.LoadFromFile(gPrefix("images/game_over.png", s));
	
	mGameOver.SetImage(mGameOverImg);
	mGameOver.SetPosition(200, 600);
}

void GameOver::Step()
{
	mBoard->DrawBlocks();
	mBoard->DrawScore();
	
	if (mIter == mBlocks.end())
	{
		if (mClock.GetElapsedTime() > 0.005f)
		{
			mGameOver.Move(0, -1);
			if (mGameOver.GetPosition().y <= 150)
			{
				// Wait a second
				while (mClock.GetElapsedTime() < 1.f);
				End();
			}
			mClock.Reset();
		}
			
		mRender->Draw(mGameOver);
	}
	else
	{
		// Uncolor the blocks, one by one
		if (mClock.GetElapsedTime() > 0.04f)
		{
			(*mIter)->SetColor(sf::Color::White);
			++ mIter;
			mClock.Reset();
		}
	}
	

	
	mRender->Display();
	mRender->Clear(sf::Color(240, 240, 240));
}

void GameOver::ProcessEvent(sf::Event &theEvent)
{
}
