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

#include "Board.hpp"
#include "MainMenu.hpp"
#include "Pause.hpp"

// For sf::Randomizer
#include <SFML/System.hpp>

#include <sstream>
#include <cmath>
#include <iostream>

#include "Config.hpp"
#include "Highscores.hpp"


Board::Board()
: mCurrentLoop(NULL), mScore(0), mLevel(1),
mCombo(0), mSpeed(1.4), mColors(3), mIsMusicPlaying(true),
mCurrentMode(eArcade)
{
	// Start the render
	mRender.Create(sf::VideoMode(800, 600), "Colori");

	// Load resources
	std::string s;
	mBlockImg.LoadFromFile(gPrefix("images/block.png", s));
	mBoardImg.LoadFromFile(gPrefix("images/board.png", s));
	mBigBlockImg.LoadFromFile(gPrefix("images/big_block.png", s));
	mScoreBackImg.LoadFromFile(gPrefix("images/score_back.png", s));
	mMuteImg.LoadFromFile(gPrefix("images/mute.png", s));
	mMute.SetImage(mMuteImg);

	// Font
	mFont.Load(gPrefix("font/numbers.png", s), gPrefix("font/numbers", s));
	mFont.SetRender(&mRender);

	mScoreBack.SetImage(mScoreBackImg);
	mScoreBack.SetPosition(0, 300);

	// Audio


	// Sounds
	mAnimSound.LoadFromFile(gPrefix("sounds/anim.wav", s));
	mComboSound.LoadFromFile(gPrefix("sounds/combo.wav", s));
	mOverSound.LoadFromFile(gPrefix("sounds/over.wav", s));
	mTucSound.LoadFromFile(gPrefix("sounds/tuc.wav", s));
	mSound.SetVolume(30.f);

	mMusicRelax.push_back(gPrefix("music/relax/01-bluzynette.ogg", s));
	mMusicRelax.push_back(gPrefix("music/relax/02-pomponette.ogg", s));
	mMusicRelax.push_back(gPrefix("music/relax/03-musiquette.ogg", s));
	mMusicRelax.push_back(gPrefix("music/relax/06-trotinette.ogg", s));

	mMusicArcade.push_back(gPrefix("music/arcade_time/Skapmat-2.ogg", s));
	mMusicArcade.push_back(gPrefix("music/arcade_time/Skapmat-3.ogg", s));
	mMusicArcade.push_back(gPrefix("music/arcade_time/Skapmat-4.ogg", s));

	mMusic.OpenFromFile(mMusicArcade[1]);
	mMusic.Play();

	// Randomizer's seed
	sf::Randomizer::SetSeed(time(NULL));

	// Resize the matrix
	mMatrix.resize(WIDTH, std::vector<std::list<Block>::iterator*>(HEIGHT));

	// Initial blocks
	CreateNextColumn(COLUMN_SIZE);
	CreateColumn(COLUMN_SIZE);

	// Initial loop
	PushLoop(new MainMenu(&mRender, this));

	//delete mCurrentLoop;
	mMusic.Stop();
	mRender.Close();
}

// Stack method
void Board::PushLoop(Loop *theLoop)
{
	mLoops.push(theLoop);
	mCurrentLoop = theLoop;

	mCurrentLoop->Start(); // Make the loop loop.
	delete mCurrentLoop; // Loop finished

	mLoops.pop();
	if (!mLoops.empty())
	{
		mCurrentLoop = mLoops.top();
	}
}

// Old
void Board::ChangeLoop(Loop *theLoop)
{
	if (mCurrentLoop)
	{
		// There's a loop running
		mCurrentLoop->End();
		delete mCurrentLoop;
	}

	mCurrentLoop = theLoop;
	mCurrentLoop->Start(); // Make the loop loop.
	delete mCurrentLoop;
	mCurrentLoop = NULL;
}

void Board::DrawNextColumn()
{
	// Draw the next column
	for (int i = 0 ; i < mNextColumn.size() ; i ++)
		mRender.Draw(mNextColumn[i].GetAbsoluteSprite(mBlockImg));
}

// Draw everything that is considered background
void Board::DrawBackground()
{
	// Draw the board
	sf::Sprite s;
	s.SetImage(mBoardImg);
	s.SetPosition(START_X, START_Y);
	mRender.Draw(s);

	// Draw the score blocks
	for (std::list<sf::Sprite>::iterator i = mScoreBlocks.begin(); i != mScoreBlocks.end(); i ++)
	{
		mRender.Draw(*i);
	}
}

// Draw the current column (the one the player has control of)
void Board::DrawCurrentColumn()
{
	// Draw the current column
	for (std::list<Block>::iterator i = mColumn.begin(); i != mColumn.end(); i ++)
	{
		// Only if non-negative 'y' position
		if ((*i).GetPosition().y >= 0)
		{
			sf::Sprite spr;
			spr = (*i).GetSprite(mBlockImg);
			spr.SetColor((*i).GetColor());
			mRender.Draw(spr);
		}
	}
}

void Board::DrawStaticBlocks()
{
	if (mCurrentMode == eArcade || mCurrentMode == eRelax)
	{
		DrawColorfulBlocks();
	}
	else
	{
		// White blocks
		for (std::list<Block>::iterator i = mBlocks.begin(); i != mBlocks.end(); i ++)
		{
			mBlockSprite = (*i).GetSprite(mBlockImg);
			mBlockSprite.SetColor(sf::Color::White);
			mRender.Draw(mBlockSprite);
		}
	}
}

void Board::DrawColorfulBlocks()
{
		// Draw the colorful static blocks
		for (std::list<Block>::iterator i = mBlocks.begin(); i != mBlocks.end(); i ++)
		{
			mRender.Draw((*i).GetSprite(mBlockImg));
		}
}


void Board::DrawScore()
{
	// Background
	mRender.Draw(mScoreBack);

	// Score
	std::ostringstream os;
	os <<  mScore;

	mFont.DrawString(os.str().c_str(), 36, 420);
	os.str("");
	os <<  mLevel;
	mFont.DrawString(os.str().c_str(), 220, 510);

}

int Board::GetScoreNeededForLevel(int theLevel)
{
	if (theLevel < 2)
		return 0;

	//return (int)(30*pow(1.5, theLevel-2));
	return (int) ((30+theLevel*2)*theLevel + pow(theLevel, 3));
}

void Board::AddScore(unsigned int theScore)
{
	mScore += theScore;

	// New score block required?
	float scoreLevel = (mScore-GetScoreNeededForLevel(mLevel));
	float scoreBlock = ((GetScoreNeededForLevel(mLevel+1) - GetScoreNeededForLevel(mLevel))/8.f); // != 0
	int blocks = (int) (scoreLevel/scoreBlock);

	while ( blocks > mScoreBlocks.size() )
	{

		// new score block!
		sf::Sprite spr;
		spr.SetPosition(432 + START_X, START_Y - OFFSET + 8*64 - mScoreBlocks.size()*64);
		spr.SetColor(GetRandomColor());
		spr.SetImage(mBigBlockImg);
		mScoreBlocks.push_back(spr);
	}

	// Do check for new level
	while (mScore >= GetScoreNeededForLevel(mLevel+1))
	{
		++ mLevel;


		// Difficulty stuff

		// Very easy:
		if (mCurrentMode == eRelax)
		{
			// Every ten levels add a new color and speed up a little bit
			if (mLevel % 10 == 0 && mColors < COLORS)
			{
				++ mColors;
				mSpeed /= 1.3;
			}
		}
		else
		{
			// New speed or new color?
			// Every five levels add a new color, and let speed go back a level
			if (mLevel % 5 == 0 && mColors < COLORS)
			{
				++ mColors;
				mSpeed *= 1.2;
			}
			else
				mSpeed /= 1.2;
		}

		// Level up! need to erase the score blocks
		mScoreBlocks.clear();
	}
}

float Board::GetSpeed()
{
	return mSpeed;
}

void Board::DrawPause()
{
	// Score
	sf::String pause("Pause");
	pause.SetColor(sf::Color(200, 128, 0));
	pause.Move(300, 300);
	mRender.Draw(pause);
}

void Board::HandleEsc(sf::Event &theEvent)
{
	if (theEvent.Type == sf::Event::KeyReleased)
	{
		// Exit on Esc.
		if (theEvent.Key.Code == sf::Key::Escape)
		{
			if (mCurrentLoop)
			{
				mCurrentLoop->End();
				return;
			}
		}
	}

	// Check if window's event for close
     if (theEvent.Type == sf::Event::Closed)
         mCurrentLoop->End();

}

void Board::HandlePause(sf::Event &theEvent)
{
	if (theEvent.Type == sf::Event::KeyReleased)
	{
		// Pause
		if (theEvent.Key.Code == sf::Key::P)
		{
			PushLoop(new Pause(&mRender, this));
		}
	}
}

void Board::HandleMovement(sf::Event &theEvent)
{
	if (theEvent.Type == sf::Event::KeyPressed)
	{
		// Movement
		if (theEvent.Key.Code == sf::Key::Left)
			MoveColumn(sf::Vector2f(-1, 0));
		else if (theEvent.Key.Code == sf::Key::Right)
			MoveColumn(sf::Vector2f(1, 0));
		else if (theEvent.Key.Code == sf::Key::Up)
			RotateColumn();
	}
}

void Board::RotateColumn()
{
	// Only rotate the colors (not the actual blocks), easier like this.

	// Auxiliary list of colors
	std::list<sf::Color> colors;
	for (std::list<Block>::iterator i = mColumn.begin(); i != mColumn.end(); i ++)
		colors.push_back((*i).GetColor());

	// Remove the last color
	sf::Color c = colors.back();
	std::list<sf::Color>::iterator i = colors.end();
	-- i;
	colors.erase(i);

	// and insert at the beginning (thus rotating the colors)
	colors.push_front(c);

	// Finally set the rotated colors to the column
	std::list<Block>::iterator column_i = mColumn.begin();
	std::list<sf::Color>::iterator colors_i = colors.begin();
	while (column_i != mColumn.end())
	{
		(*column_i).SetColor(*colors_i);
		++ column_i;
		++ colors_i;
	}
}

// True on valid move
bool Board::MoveColumn(sf::Vector2f theDir)
{
	// Check if it can move, checking the bottom-most is enough
	if (!CheckValidMove(&(*mColumn.begin()), theDir))
		return false; // Invalid move

	std::list<Block>::iterator i = mColumn.begin();
	while (i != mColumn.end())
	{
		(*i).Move(theDir);
		++ i;
	}

	// true on successful move
	return true;
}

// This method also check for game over
// If any position of the column is negative then
// is game over, this means the block is not complete on the board.
// true on valid move, false on game over.
bool Board::PushColumn()
{
	// Add column to blocks, if any
	std::list<Block>::iterator i = mColumn.begin();
	while (i != mColumn.end())
	{
		// Check if non-negative position
		if ((*i).GetPosition().y >= 0)
		{
			// Non-negative position, now it's safe to put it in the main blocks list
			mBlocks.push_back(*i); // Push a copy
			i = mColumn.erase(i); // Erase and iteration.
		}
		else
		{
			// Game over! sorry
			return false;
		}

	}
	return true;
}

// True on valid
bool Board::CheckValidMove(Block* theBlock, sf::Vector2f theDir)
{
	sf::Vector2f newPos = theBlock->GetPosition() + theDir;

	// Horizontal limit
	if (newPos.x < 0 || newPos.x >= WIDTH)
		return false;

	// Bottom limit
	if (newPos.y >= HEIGHT)
		return false;

	// Collision with another block
	for (std::list<Block>::iterator i = mBlocks.begin(); i != mBlocks.end(); i ++)
	{
		if (newPos == (*i).GetPosition())
			return false; // Collision
	}

	// Valid move
	return true;
}

// True on valid
// Checks the whole column.
/*
bool Board::CheckValidColumn()
{

}
*/


// parameter theSize deprecated, keeped for compatibility
// indicate the size in CreateNextColumn
void Board::CreateColumn(int theSize)
{
	mColumn.clear();

	/*
	// Add to the blocks
	for (int i = 0 ; i < theSize ; i ++)
	{
		mNextColumn[i].SetPosition(sf::Vector2f(4.f, (float)(i-3)));
		mBlocks.push_front(mNextColumn[i]);
	}

	// Set the column
	std::list<Block>::iterator it = mBlocks.begin();
	int i = 0;
	while (i < theSize)
	{
		mColumn.push_back(&(*it));
		++ it;
		++ i;
	}
	*/

	// Set the column
	std::vector<Block>::iterator it = mNextColumn.begin();
	for (int i = 0 ; i < mNextColumn.size() ; i ++)
	{
		mNextColumn[i].SetPosition(sf::Vector2f(4.f, (float)(i-3)));
		mColumn.push_front(mNextColumn[i]);
	}

	CreateNextColumn(COLUMN_SIZE);
}

void Board::CreateNextColumn(int theSize)
{
	mNextColumn.clear();

	// Set the column
	int i = 0;
	while (i < theSize)
	{
		mNextColumn.push_back(Block(sf::Vector2f(368 + START_X, START_Y + 241 + i*BLOCK_SIZE), GetRandomColor()));
		++ i;
	}
}

sf::Color Board::GetRandomColor()
{
	static sf::Color colors[7];
		colors[0] = sf::Color::Red;
		colors[1] = sf::Color::Green;
		colors[2] = sf::Color::Blue;
		colors[3] = sf::Color::Yellow;
		colors[4] = sf::Color::Cyan;
		colors[5] = sf::Color::Magenta;
		colors[6] = sf::Color(255, 165, 0); // Orange

	return colors[sf::Randomizer::Random(0, mColors)];
}


void Board::BuildMatrix()
{
	// Delete matrix if already exists!
	for (unsigned int i = 0 ; i < mMatrix.size(); i ++)
		for (unsigned int j = 0 ; j < mMatrix[i].size() ; j ++)
			if (mMatrix[i][j] != NULL)
				delete mMatrix[i][j];

	// Fill the matrix with NULL iterators
	for (unsigned int i = 0 ; i < mMatrix.size(); i ++)
		for (unsigned int j = 0 ; j < mMatrix[i].size() ; j ++)
			mMatrix[i][j] = NULL;

	// Put the blocks in it
	sf::Vector2f pos;
	for (std::list<Block>::iterator i = mBlocks.begin(); i != mBlocks.end(); i ++)
	{
		pos = (*i).GetPosition(); // Get the position of the block
		std::list<Block>::iterator *ii = new std::list<Block>::iterator(i);

		// EXTREME careful here! The position should never be negative at this point!
		mMatrix[(int)pos.x][(int)pos.y] = ii; // The adress of the iterator
	}
}

std::vector< std::vector<std::list<Block>::iterator* > > Board::GetMatrix()
{
	BuildMatrix();
	return mMatrix;
}

// Returns a list of the board (order unknown)
std::list< Block* > Board::GetBlocks()
{
	std::list< Block* > l;
	for (std::list<Block>::iterator i = mBlocks.begin(); i != mBlocks.end(); i ++)
		l.push_back(&(*i));
	return l;
}



void Board::EraseBlock(std::list<Block>::iterator theIterator)
{
	mBlocks.erase(theIterator);
}

void Board::Clear()
{
	mBlocks.clear();
	mColumn.clear();
	mScoreBlocks.clear();

	mScore = 0;
	mLevel = 1;
	mCombo = 0;
	mSpeed = 1.4;
	mColors = 3;

	// Initial blocks
	CreateNextColumn(COLUMN_SIZE);
	CreateColumn(COLUMN_SIZE);
}

int Board::GetCombo()
{
	return mCombo;
}

int Board::GetLevel()
{
	return mLevel;
}

void Board::SetCombo(int theCombo)
{
	mCombo = theCombo;
}

void Board::SetLevel(int theLevel)
{
	mLevel = theLevel;
}

void Board::AddCombo()
{
	++ mCombo;

	if (mCombo > 2)
		PlayComboSound();
}

void Board::AddLevel()
{
	++ mLevel;
}

void Board::DoMusic(float theX, float theY)
{
	mMute.SetPosition(theX, theY);
	mMute.SetSubRect(sf::IntRect(!mIsMusicPlaying*75, 0, !mIsMusicPlaying*75 + 75, mMuteImg.GetHeight()));
	mRender.Draw(mMute);

	// If done start playing again
	if (mMusic.GetStatus() == sf::Sound::Stopped)
	{
		SetMusic();
	}
}

void Board::SwitchMute(sf::Event &theEvent)
{
	if (theEvent.Type == sf::Event::MouseButtonReleased)
	{
		// Mouse cursor position
		int x = mRender.GetInput().GetMouseX();
		int y = mRender.GetInput().GetMouseY();
		if (mMute.GetSubRect().Contains(x-mMute.GetPosition().x+!mIsMusicPlaying*75, y-mMute.GetPosition().y))
		{
			SwitchMute();
		}
	}
	else if (theEvent.Type == sf::Event::KeyReleased)
	{
		// Pause
		if (theEvent.Key.Code == sf::Key::M)
		{
			SwitchMute();
		}
	}
}

void Board::SwitchMute()
{
	mIsMusicPlaying = !mIsMusicPlaying;

	if (mMusic.GetStatus() == sf::Sound::Playing)
	{
		mSound.SetVolume(0.f);
		mMusic.Pause();
	}
	else
	{
		mSound.SetVolume(30.f);
		mMusic.Play(); // Resume
	}
}

void Board::SetMusic()
{
	if (mIsMusicPlaying)
	{
		if (mCurrentMode == eArcade || mCurrentMode == eColorless)
			mMusic.OpenFromFile(mMusicArcade[sf::Randomizer::Random(0, mMusicArcade.size()-1)]);
		else
			mMusic.OpenFromFile(mMusicRelax[sf::Randomizer::Random(0, mMusicRelax.size()-1)]);

		mMusic.Play();
	}
}
