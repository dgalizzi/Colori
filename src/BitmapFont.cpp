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

#include "BitmapFont.hpp"
#include <fstream>
#include <iostream>

BitmapFont::BitmapFont()
: mRender(NULL)
{ }

BitmapFont::BitmapFont(const char *theImageFileName, const char *theInfoFileName, sf::RenderWindow* theRender)
: mRender(theRender)
{
	Load(theImageFileName, theInfoFileName);
}

void BitmapFont::Load(const char *theImageFileName, const char *theInfoFileName)
{
	std::ifstream f(theInfoFileName, std::ios_base::in);
	
	if (!f.is_open())
	{
		std::cout << "File: " << theInfoFileName << " failed to open." << std::endl;
		return;
	}
	
	// The first line is the string
	f >> mString;

	Pair p;
	while (f >> p.x0)
	{
		f >> p.x1;
		mPoints.push_back(p);
	}
	
	mImage.LoadFromFile(theImageFileName);
	f.close();
}

void BitmapFont::GetPair(char c, int &x0, int &x1)
{
	// Find c
	for (int i = 0 ; i < mString.length() ; i ++)
	{
		if (mString[i] == c)
		{
			// Found, set the pair
			x0 = mPoints[i].x0;
			x1 = mPoints[i].x1;
		}
	}
}

void BitmapFont::DrawString(const char* theString, float theX, float theY)
{
	sf::Sprite spr;
	spr.SetImage(mImage);
	spr.SetPosition(theX, theY);
	spr.SetColor(sf::Color::Magenta);
	
	// Draw the string
	std::string s(theString);
	int x0, x1;
	for (int i = 0 ; i < s.length() ; i ++)
	{
		if (s[i] == '\n')
		{
			spr.Move(0, mImage.GetHeight()+8); // Space between lines
			spr.SetPosition(theX, spr.GetPosition().y);
			continue;
		}
		else if (s[i] != ' ')
		{
			GetPair(s[i], x0, x1);
			
	
			// Left, Top, Right, Bottom
			spr.SetSubRect(sf::IntRect(x0, 0, x1+1, mImage.GetHeight()));
			mRender->Draw(spr);
		}
		else
		{
			spr.Move(6, 0);
			continue;
		}
		
		spr.Move(x1-x0 + 2, 0);
	}
}

sf::Image* BitmapFont::GetImage()
{
	return &mImage;
}
void BitmapFont::SetImage(sf::Image &theImage)
{
	mImage = theImage;
}

void BitmapFont::SetRender(sf::RenderWindow* theRender)
{
	mRender = theRender;
}

