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

#ifndef BITMAP_FONT_HPP
#define BITMAP_FONT_HPP

#include <string>
#include <SFML/Graphics.hpp>


class BitmapFont
{
public:
	BitmapFont();
	BitmapFont(const char* theImageFileName, const char* theInfoFilename, sf::RenderWindow* theRender = NULL);
	void Load(const char *theImageFileName, const char *theInfoFileName);
	
	sf::Image* GetImage();
	void SetImage(sf::Image &theImage);
	
	void SetRender(sf::RenderWindow* theRender);
	
	void DrawString(const char* theString, float theX, float theY);

private:
	std::string mString;
	sf::Image mImage;
	sf::RenderWindow* mRender;
	
	struct Pair
	{
		int x0, x1;
	};
	void GetPair(char c, int &x0, int &x1);
	
	std::vector<Pair> mPoints;
};

#endif

