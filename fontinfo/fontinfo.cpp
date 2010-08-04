#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
using namespace std;

bool CheckY(sf::Image &theImage, int theX)
{
	if (theX >= theImage.GetWidth())
		return false;

	for (int y = 0 ; y < theImage.GetHeight() ; y ++)
	{
		if (theImage.GetPixel(theX, y).a != 0) // non-Transparent pixel?
			return false;
	}
	
	return true;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		cout << "Usage: fontinfo string filename" << endl;
		return 1;
	}
	
	string s(argv[1]);
	string f(argv[2]);
	
	cout << s << endl;
	
	sf::Image font;
	if (!font.LoadFromFile(f))
	{
		cout << "Image not found: " << f << endl;
		return 1;
	}
	
	
	// Find the first char
	int x0 = 0;
	for ( ; x0 < font.GetWidth(); x0 ++)
	{
		if (!CheckY(font, x0))
			break;
	}
	
	int x1;
	for (int i = 0 ; i < font.GetWidth() ; i ++)
	{
		if (CheckY(font, i) || i+1 == font.GetWidth())
		{
			x1 = i;
			
			// Write
			cout << x0 << " " << x1 << endl;
			
			// Avoid next spaces
			while (CheckY(font, i))
				++ i;

			x0 = i;
		}
	}
		
	return 0;
}

