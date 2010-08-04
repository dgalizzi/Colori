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

#ifndef FALL_LOOP_HPP
#define FALL_LOOP_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include "Loop.hpp"
#include "Board.hpp"

struct FloatingBlock
{
	Block* mBlock;
	float mToMove;
	float mSpeed;
	float mLastY;
	sf::Clock mClock;
};

class FallLoop : public Loop
{
public:
	FallLoop(sf::RenderWindow *theRender, Board *theBoard);
	
	virtual void Step();
	virtual void ProcessEvent(sf::Event &theEvent);
	
	void Check();
	
private:
	Board *mBoard;
	
	// Matrix of the board
	std::vector< std::vector<std::list<Block>::iterator*> > mMatrix;	
	
	// List of floating blocks
	std::list<FloatingBlock> mList;
	
	// Clock
	sf::Clock mClock;
	
	bool mNewCheckNeeded;
};

#endif
