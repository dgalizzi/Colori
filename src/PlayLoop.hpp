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

#ifndef PLAY_LOOP_HPP
#define PLAY_LOOP_HPP

#include "Loop.hpp"
#include "BitmapFont.hpp"
#include <SFML/System.hpp> // sf::Clock

// Board declaration
class Board;

class PlayLoop : public Loop
{
public:
	PlayLoop(sf::RenderWindow *theRender, Board *theBoard);
	
	virtual void Step();
	virtual void ProcessEvent(sf::Event &theEvent);
	
private:
	Board* mBoard;
	sf::Clock mClock, mInputClock, mNewColumnClock;
};

#endif

