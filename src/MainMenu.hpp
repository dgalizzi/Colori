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

#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "Loop.hpp"
#include "BitmapFont.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class Board;

class MainMenu : public Loop
{
public:
	MainMenu(sf::RenderWindow *theRender, Board *theBoard);
	~MainMenu();
	
	virtual void ProcessEvent(sf::Event &theEvent);
	virtual void Step();
	
	bool MouseInside(sf::Sprite &theSprite);
	void GetString();

private:
	sf::Image mButtonImg, mSmallButtonImg;
	sf::Image mLogoImg;
	sf::Image mTextBlockImg;
	
	sf::Image mArcadeImg;
	sf::Image mTimeImg;
	sf::Image mRelaxImg;
	sf::Image mHighImg;
	sf::Image mExitImg;
	sf::Image mCreditsImg;
	
	sf::Sprite mButton, mSmallButton;
	sf::Sprite mLogo;
	sf::Sprite mTextBlock;
	
	sf::Sprite mArcade;
	sf::Sprite mTime;
	sf::Sprite mRelax;
	sf::Sprite mHigh;
	sf::Sprite mExit;
	sf::Sprite mCredits;
	
	Board *mBoard;
	
	BitmapFont mFont;
	
	int mMouseX, mMouseY;
	
	std::string mString;
	int mStringX, mStringY;
};

#endif

