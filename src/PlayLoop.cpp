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

#include "PlayLoop.hpp"
#include "Board.hpp"
#include "DestroyLoop.hpp"
#include "GameOver.hpp"

PlayLoop::PlayLoop(sf::RenderWindow *theRender, Board *theBoard)
: Loop(theRender), mBoard(theBoard)
{
	// Clocks
	mClock.Reset();
	mInputClock.Reset();
	mNewColumnClock.Reset();
}

void PlayLoop::ProcessEvent(sf::Event &theEvent)
{
	mBoard->HandleEsc(theEvent);
	mBoard->HandlePause(theEvent);
	mBoard->HandleMovement(theEvent);
	mBoard->SwitchMute(theEvent);
}

void PlayLoop::Step()
{


	mRender->Clear(sf::Color(240, 240, 240));
	mBoard->DrawBackground();
	mBoard->DoMusic(16, 16);
	mBoard->DrawNextColumn();
	mBoard->DrawCurrentColumn();
	mBoard->DrawStaticBlocks();
	mBoard->DrawScore();
	mRender->Display();



	// Wait a second if it is a new column
	//if (mNewColumnClock.GetElapsedTime() < 1.f && !mRender->GetInput().IsKeyDown(sf::Key::Down))
		//return;

	// Move column down
	if (mClock.GetElapsedTime() > mBoard->GetSpeed() ||
		(mRender->GetInput().IsKeyDown(sf::Key::Down) && mInputClock.GetElapsedTime() > 0.05f))
	{
		mClock.Reset();
		mInputClock.Reset();

		// Move down
		if (!mBoard->MoveColumn(sf::Vector2f(0, 1)))
		{
			// Invalid move, bottom or collision

			// Add the column to the main blocks list and check for game over.
			if (mBoard->PushColumn())
			{
				// Play the 'tuc' sound
				mBoard->PlayTucSound();

				mBoard->PushLoop(new DestroyLoop(mRender, mBoard));

				// Clear combo
				mBoard->SetCombo(0);

				// Ask for new column
				mBoard->CreateColumn(COLUMN_SIZE);

				// Give the player just a second to recover
				//mNewColumnClock.Reset();
			}
			else
			{
				// Game over!
				mBoard->PlayOverSound();
				mBoard->PushLoop(new GameOver(mRender, mBoard));
				End(); // End this loop
				mBoard->Clear();
			}
		}
	}
}
