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

#include "Pause.hpp"
#include "Board.hpp"
#include "Config.hpp"

Pause::Pause(sf::RenderWindow *theRender, Board *theBoard)
: Loop(theRender), mBoard(theBoard)
{
	std::string s;
	mPauseImg.LoadFromFile(gPrefix("images/pause.png", s));
	mPause.SetImage(mPauseImg);
	mPause.SetPosition(300, 300);
}

void Pause::ProcessEvent(sf::Event &theEvent)
{
	mBoard->HandleEsc(theEvent);
	if (theEvent.Type == sf::Event::KeyReleased)
	{
		// Pause
		if (theEvent.Key.Code == sf::Key::P)
		{
			End();
		}
	}	
}

void Pause::Step()
{
	mBoard->DrawBackground();
	mBoard->DrawScore();
	
	// Draw pause
	mRender->Draw(mPause);
	
	mRender->Display();
	mRender->Clear(sf::Color(240, 240, 240));
}


