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
#include <SFML/Audio.hpp>
#include <list>
#include <stack>

#include "Loop.hpp"
#include "Block.hpp"
#include "PlayLoop.hpp"
#include "Config.hpp"



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
	void DrawColorfulBlocks();
	void DrawStaticBlocks();
	void DrawScore();
	void DrawPause();
	void DrawBackground();
	void DrawCurrentColumn();
	void DrawNextColumn();

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

	// Play sounds
	inline void PlayAnimSound() { mSound.SetBuffer(mAnimSound);  mSound.Play(); }
	inline void PlayComboSound(){ mSound.SetBuffer(mComboSound); mSound.Play(); }
	inline void PlayOverSound() { mSound.SetBuffer(mOverSound);  mSound.Play(); }
	inline void PlayTucSound()  { mSound.SetBuffer(mTucSound);   mSound.Play(); }
	void SetMusic();
	void DoMusic(float theX, float theY);
	void SwitchMute(sf::Event &theEvent);
	inline sf::Sprite *GetMuteSprite() { return &mMute; }

	int GetCombo();
	int GetLevel();
	void SetCombo(int theCombo);
	void SetLevel(int theCombo);
	void AddCombo();
	void AddLevel();
	float GetSpeed();
	inline unsigned int GetScore() { return mScore; }

	// Variants
	enum Modes
	{
		eArcade = 0,
		eColorless,
		eRelax
	};
	inline void SetMode(Modes theMode) { mCurrentMode = theMode;}
	inline Modes GetMode() { return mCurrentMode; }

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
	sf::Image mMuteImg;
	BitmapFont mFont;

	sf::Sprite mScoreBack;
	sf::Sprite mBlockSprite;
	sf::Sprite mMute;

	// Score
	unsigned int mScore;
	int mLevel, mCombo;
	float mSpeed;
	int mColors;

	std::list<sf::Sprite> mScoreBlocks;

	Modes mCurrentMode;

	// Audio
	sf::Music mMusic;

	sf::SoundBuffer mAnimSound;
	sf::SoundBuffer mComboSound;
	sf::SoundBuffer mOverSound;
	sf::SoundBuffer mTucSound;

	sf::Sound mSound;
	bool mIsMusicPlaying;

	// Paths
	std::vector<std::string> mMusicArcade;
	std::vector<std::string> mMusicRelax;

	void SwitchMute();
};

#endif
