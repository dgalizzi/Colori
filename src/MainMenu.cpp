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

#include "MainMenu.hpp"
#include "Board.hpp"
#include "PlayLoop.hpp"
#include "Config.hpp"

MainMenu::MainMenu(sf::RenderWindow *theRender, Board *theBoard)
: Loop(theRender), mBoard(theBoard)
{
	std::string s;
	
	mLogoImg.LoadFromFile(gPrefix("images/logo.png", s));
	mButtonImg.LoadFromFile(gPrefix("images/button.png", s));
	mSmallButtonImg.LoadFromFile(gPrefix("images/small_button.png", s));
	mExitImg.LoadFromFile(gPrefix("images/exit.png", s));
	mTextBlockImg.LoadFromFile(gPrefix("images/textBlock.png", s));
	mCreditsImg.LoadFromFile(gPrefix("images/credits.png", s));

	mArcadeImg.LoadFromFile(gPrefix("images/arcade.png", s));
	mTimeImg.LoadFromFile(gPrefix("images/timeAttack.png", s));
	mRelaxImg.LoadFromFile(gPrefix("images/relax.png", s));
	mHighImg.LoadFromFile(gPrefix("images/high.png", s));
		
	mLogo.SetImage(mLogoImg);
	mLogo.SetPosition(16, 16);
		
	mTextBlock.SetImage(mTextBlockImg);
	mTextBlock.SetPosition(370, 170);
	
	
	// Texts buttons
	mArcade.SetImage(mArcadeImg);
	mArcade.SetPosition(42, 120);
	
	mTime.SetImage(mTimeImg);
	mTime.SetPosition(42, 120*2);
	
	mRelax.SetImage(mRelaxImg);
	mRelax.SetPosition(42, 120*3);
	
	mHigh.SetImage(mHighImg);
	mHigh.SetPosition(42, 120*4);
	
	mButton.SetImage(mButtonImg);
	mSmallButton.SetImage(mSmallButtonImg);
	
	mExit.SetImage(mExitImg);
	mExit.SetPosition(650, 450);
	
	mCredits.SetImage(mCreditsImg);
	mCredits.SetPosition(650, 0);
	
	
	// Font
	mFont.Load(gPrefix("font/font.png", s), gPrefix("font/font", s));
	mFont.SetRender(mRender);
}

MainMenu::~MainMenu()
{ }

void MainMenu::ProcessEvent(sf::Event &theEvent)
{
	mBoard->HandleEsc(theEvent);
	
	// Mouse click
	if (theEvent.Type == sf::Event::MouseButtonReleased)
	{
		mBoard->SetMode(Board::eArcade);
		mBoard->PushLoop(new PlayLoop(mRender, mBoard));
	}
	
	
//
	if (theEvent.Type == sf::Event::KeyReleased)
	{
		// Exit on Esc.
		if (theEvent.Key.Code == sf::Key::Escape)
		{
			End();
		}
	}
}

bool MainMenu::MouseInside(sf::Sprite &theSprite)
{
	return (theSprite.GetSubRect().Contains(mMouseX-theSprite.GetPosition().x, mMouseY-theSprite.GetPosition().y));
}

void MainMenu::GetString()
{
	// Mouse cursor position
	mMouseX = mRender->GetInput().GetMouseX();
	mMouseY = mRender->GetInput().GetMouseY();
	
	// 
	
	// Reset colors
	mArcade.SetColor(sf::Color::Red);
	mTime.SetColor(sf::Color::Red);
	mRelax.SetColor(sf::Color::Red);
	mHigh.SetColor(sf::Color::Red);
	mCredits.SetColor(sf::Color::Red);
	mExit.SetColor(sf::Color::Red);

	if (MouseInside(mArcade))
	{
		mString = "The classic mode, start easy,\nfew colors and low speed.\nThe difficulty will increase over\ntime. Match colors, do combos,\nand achieve a new high score!";
		mStringX = 392;
		mStringY = 205;
		mArcade.SetColor(sf::Color::Blue);
	}
	else if (MouseInside(mTime))
	{
		mString = "You only get to see the colors\nof the blocks you are controlling.\nOnce these blocks are down they\nbecome gray! Try to remember\nthem to get a high score!";
		mStringX = 392;
		mStringY = 205;
		mTime.SetColor(sf::Color::Blue);
	}
	else if (MouseInside(mRelax))
	{
		mString = "Just sit, play and relax. Enjoy the\nmusic and play without pressure.\nThe game will not get harder\nas you play, take your time.";
		mStringX = 392;
		mStringY = 225;
		mRelax.SetColor(sf::Color::Blue);
	}
	else if (MouseInside(mHigh))
	{
		mString = "Highscores:";
		mStringX = 412;
		mStringY = 205;
		mHigh.SetColor(sf::Color::Blue);
	}
	else if (MouseInside(mExit))
	{
		mString = "Good luck!";
		mStringX = 412;
		mStringY = 205;
		mExit.SetColor(sf::Color::Blue);
	}
	else if (MouseInside(mCredits))
	{
		mString = "Programming and design by\n     Diego D. Galizzi\n\nMusic by\n     BiBoPoF\n     Christian Bjoerklund";
		mStringX = 412;
		mStringY = 205;
		mCredits.SetColor(sf::Color::Blue);
	}
	else
	{
		mString = "Welcome to COLORI!\nA game where you have to\nmatch colors. You can play the\nclassic mode, against time or\njust sit and play a relaxing mode.\nHave fun!";
		mStringX = 396;
		mStringY = 206;
	}
}

void MainMenu::Step()
{
	// Background
	mRender->Clear(sf::Color(240, 240, 240));
	
	// Stuff
	mRender->Draw(mLogo);
	mRender->Draw(mTextBlock);
	
	// Credits and exit buttons
	mSmallButton.SetPosition(650, 450);
	mRender->Draw(mSmallButton);
	mSmallButton.SetPosition(650, 0);
	mRender->Draw(mSmallButton);
	
	mRender->Draw(mCredits);
	mRender->Draw(mExit);
	
	// Draw the string
	GetString();
	mFont.DrawString(mString.c_str(), mStringX, mStringY);
		
	// Four button
	mButton.SetPosition(42, 120);
	for (int i = 0 ; i < 4 ; i ++)
	{
		mRender->Draw(mButton);
		mButton.Move(0, 120);
	}
	
	mRender->Draw(mArcade);
	mRender->Draw(mTime);
	mRender->Draw(mRelax);
	mRender->Draw(mHigh);
	
	mRender->Display();
	
	
}

