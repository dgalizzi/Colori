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

#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include <stack>

#include "Loop.hpp"
#include "Block.hpp"
#include "PlayLoop.hpp"

/*
	Loops:
		* Input: Accepts all input
		* Pause: Draw a "Game paused" text and only accepts 'P' as input (to unpause).
		* Checking matches: Destroy matching blocks, escape and pause input.
		* Falling: After destroying blocks, leat the floating blocks fall. Check again needed.
*/


class Board
{
public:
	Board();

	// Drawing methods
	void DrawBlocks();
	void DrawColorfulBlocks();
	void DrawStaticBlocks();
	void DrawScore();
	void DrawPause();
	
	// Handle input
	void HandleEsc(sf::Event &theEvent);
	void HandlePause(sf::Event &theEvent);
	void HandleMovement(sf::Event &theEvent);
	
	// Change the current loop
	void ChangeLoop(Loop *theLoop);
	void PushLoop(Loop *theLoop);
	
	// Returns the matrix of the board
	std::vector< std::vector< std::list<Block>::iterator* > > GetMatrix();
	void BuildMatrix();
	bool PushColumn();
	
	// Returns a list of the board (order unknown)
	std::list< Block* > GetBlocks();
	
	// Blocks stuff
	void EraseBlock(std::list<Block>::iterator);
	void CreateColumn(int theSize);
	void CreateNextColumn(int theSize);
	bool MoveColumn(sf::Vector2f theDir);
	void RotateColumn();
	bool CheckValidMove(Block* theBlock, sf::Vector2f theDir);
	sf::Color GetRandomColor();
	
	int GetScoreNeededForLevel(int theLevel);
	void AddScore(unsigned int theScore);
	void Clear(); // Clear the blocks and data
	
	
	int GetCombo();
	int GetLevel();
	void SetCombo(int theCombo);
	void SetLevel(int theCombo);
	void AddCombo();
	void AddLevel();
	float GetSpeed();
	
	// Variants
	enum Modes
	{
		eArcade = 0,
		eColorless,
		eRelax
	};
	inline void SetMode(Modes theMode) { mCurrentMode = theMode;}
	
protected:
	std::list<Block> mBlocks;
	std::list<Block> mColumn;
	std::vector<Block> mNextColumn;
	Loop *mCurrentLoop;
	std::stack<Loop*> mLoops;
	
	// The render
	sf::RenderWindow mRender;
	
	// A matrix of the full board with pointers to iterators, NULL pointer means empty cell
	std::vector< std::vector< std::list<Block>::iterator* > > mMatrix;
	
	// Images
	sf::Image mBlockImg;
	sf::Image mBoardImg;
	sf::Image mBigBlockImg;
	sf::Image mScoreBackImg;
	BitmapFont mFont;
	
	sf::Sprite mScoreBack;
	sf::Sprite mBlockSprite;
	
	// Score
	unsigned int mScore;
	int mLevel, mCombo;
	float mSpeed;
	int mColors;
	
	std::list<sf::Sprite> mScoreBlocks;
	
	Modes mCurrentMode;
};

#endif
