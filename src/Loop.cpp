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

#include "Loop.hpp"


Loop::Loop(sf::RenderWindow *theRender)
: mRender(theRender), mIsRunning(true)
{ }

Loop::~Loop()
{
    //dtor
}

void Loop::Start()
{
    // Start the game loop
     while (mIsRunning)
     {
         // Process events
         sf::Event Event;
         while (mRender->GetEvent(Event))
         {
             ProcessEvent(Event);
         }
         
         // Step
         Step();
         
         // Update the window
         //mRender->Display();
     }
}

void Loop::Step()
{ }

void Loop::End()
{
    mIsRunning = false;
}

void Loop::ProcessEvent(sf::Event &theEvent)
{ }

sf::RenderWindow* Loop::GetRender() const
{
    return mRender;
}

void Loop::SetRender(sf::RenderWindow *theRender)
{
	mRender = theRender;
}
