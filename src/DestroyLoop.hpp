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

#ifndef DESTROY_LOOP_HPP
#define DESTROY_LOPP_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include "Loop.hpp"
#include "Board.hpp"

class DestroyLoop : public Loop
{
public:
	// Check the blocks that need to be destroyed
	DestroyLoop(sf::RenderWindow *theRender, Board *theBoard);
	
	
	void Check(int dirX, int dirY);
	
	bool CheckBoundary(int x, int y);
	
	// Draw the destroying animation/effects
	virtual void Step();
	
	// Escape and pause
	virtual void ProcessEvent(sf::Event &theEvent);

private:
	// List of iterators that point to the blocks that will be destroyed.
	std::list< std::list<Block>::iterator* > mList;
	
	// Matrix of the board
	std::vector< std::vector<std::list<Block>::iterator*> > mMatrix;
	
	Board* mBoard;
	sf::Clock mClock;
	int mFrame;
};

#endif

