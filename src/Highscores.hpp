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

#ifndef HIGHSCORES_HPP
#define HIGHSCORES_HPP

#include <cstdlib>
#include <fstream>
#include <string>
#include <queue>
#include <sstream>
#include <iostream>

struct High
{
	int score, level;
};

class Highscores
{
public:
	// Default constructor
	Highscores()
	{ }

	// Set a new highscore
	Highscores(int theScore, int theLevel, int theMode)
	{
		// Open file for reading
		std::fstream ifs;
		Open(ifs, std::ios_base::in);
		std::queue<High> q;
		High h;

		// Now the file is open
		if (!ifs) // Or is it?
		{
			// Probably not created yet
			// Initialize all with zero
			h.score = 0;
			h.level = 0;

			q.push(h);
			q.push(h);
			q.push(h);

			std::cout << "Initializing new highscore file." << std::endl;
		}
		else
		{
			// Read all the highscores
			std::string s;

			std::istringstream iss;
			while (std::getline(ifs, s))
			{
				iss.str(s);
				iss >> h.score >> h.level ;
				iss.clear();
				q.push(h);
			}

			// Close the file
			ifs.close();
		}

		// Open it for writing
		std::fstream ofs;
		Open(ofs, std::ios_base::out);

		// Write to the file, and update highscore if required
		int i = 0;
		while (!q.empty())
		{
			if (i == theMode && q.front().score < theScore)
			{
				// New highscore
				ofs << theScore << " " << theLevel << std::endl;
			}
			else
			{
				// No new highscore
				ofs << q.front().score << " " << q.front().level << std::endl;
			}
			// Next!
			q.pop();
			++ i;
		}
	}

	High GetHighscore(int theMode)
	{
		// Open file for reading
		std::fstream ifs;
		Open(ifs, std::ios_base::in);
		High h;
		if (!ifs)
		{
			// File not opened
			h.score = 0;
			h.level = 0;
			return h;
		}
		else
		{
			std::string s;
			std::istringstream iss;
			// Read the indicated line
			for (int i = 0; i <= theMode; i ++)
			{
				std::getline(ifs, s);
			}
			High h;
			iss.str(s);
			iss >> h.score >> h.level ;
			return h;
		}
	}

protected:
	// OS Dependent
	void Open(std::fstream &theStream, std::ios_base::openmode theOpenMode)
	{
#ifdef _WIN32
		DoWindows(theStream, theOpenMode);
#else
		DoLinux(theStream, theOpenMode);
#endif
	}

#ifdef _WIN32
	void DoWindows(std::fstream &theStream, std::ios_base::openmode theOpenMode)
	{
		theStream.open(".colori_highscores", theOpenMode);
	}
#else
	void DoLinux(std::fstream &theStream, std::ios_base::openmode theOpenMode)
	{
		char* home = getenv("HOME");
		std::string s1 = home;
		std::string s2 = "/.colori_highscores";
		std::string s3 = s1 + s2;
		theStream.open(s3.c_str(), theOpenMode);
	}
#endif

};

#endif
