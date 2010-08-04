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

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SFML/Graphics.hpp>

/*
#define START_X 64
#define START_Y 16
#define BLOCK_SIZE 32
#define WIDTH 10
#define HEIGHT 20
#define NMATCH 3
*/

// Some constants
const float START_X = 288;
const float START_Y = 16;
const float BLOCK_SIZE = 32;
const float WIDTH = 10;
const float HEIGHT = 17;
const float OFFSET = 16;
const int NMATCH = 3;
const int MAX_FRAME = 14; // Starting from zero
const int COLUMN_SIZE = 3;
const int COLORS = 6;

class Block
{
public:
	Block();
	Block(sf::Vector2f thePos, sf::Color theColor);

	sf::Sprite GetSprite(sf::Image &theImage);
	sf::Sprite GetAbsoluteSprite(sf::Image &theImage);
	
	sf::Color GetColor();
	void SetColor(sf::Color theColor);
	
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f thePos);
	
	int GetFrame();
	void SetFrame(int theFrame);
	
	void Move(sf::Vector2f theDir);

private:
	sf::Vector2f mPos;
	sf::Color mColor;
	int mFrame;
};

#endif

