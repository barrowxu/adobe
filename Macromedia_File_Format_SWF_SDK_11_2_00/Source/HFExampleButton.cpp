// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 11/05/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFExampleButton.cpp

   To demonstrate HFButton, HFActionPlay, HFActionStop, HFActionGetURL.
   Creates a two-frame movie with:
   
	1) a white background,
	2) a rectangle button with red (UP), green(Over), blue (Down) and black (hit) in four
	   states on the first frame,
	3) an empty rectangle is shown on the stage center on the second frame,
	4) the second frame also opens a browser window going to "http://www.yahoo.com/".
	5) movie pauses on the first frame until the button is clicked (OverDownToOverUp state
	   transition), then the movie starts to play its second frame, and pause again.

****************************************************************************************/

#include "HF3SDK.h"
#include "HFExample.h"


void HLCreateButtonMovie()
{
	HFMovie movie;												// construct a movie object

	// rect1: up state of button,
	// rect2: over state of button,
	// rect3: down state of button,
	// rect4: hit state of button.
	HFRectangle* rect1 = new HFRectangle( 0 * FPIXEL, 0 * FPIXEL, 50 * FPIXEL, 20 * FPIXEL );	// up 
	HFRectangle* rect2 = new HFRectangle( 0 * FPIXEL, 0 * FPIXEL, 50 * FPIXEL, 20 * FPIXEL );	// over
	HFRectangle* rect3 = new HFRectangle( 0 * FPIXEL, 0 * FPIXEL, 50 * FPIXEL, 20 * FPIXEL );	// down
	HFRectangle* rect4 = new HFRectangle( 0 * FPIXEL, 0 * FPIXEL, 50 * FPIXEL, 20 * FPIXEL );	// hit
	rect1->SetSolidFill( Red_RGBA );
	rect2->SetSolidFill( Green_RGBA );
	rect3->SetSolidFill( Blue_RGBA );
	rect4->SetSolidFill( Black_RGBA );

	// rect5: to be shown on the second frame.
	HFRectangle* rect5 = new HFRectangle( 100 * FPIXEL, 100 * FPIXEL, 300 * FPIXEL, 200 * FPIXEL );	// target shape

	// Construct a button
	HFButton* button = new HFButton(rect1, rect2, rect3, rect4);

	// Register button's response to certain events.
	HFActionGetURL getUrl("http://www.middlesoft.com/");
	HFActionPlay   play;

	button->QueueEvent( &getUrl, RELEASE);
	button->QueueEvent( &play, RELEASE);

	// Add the button on the first frame.
	movie.Frame(0)->AddObject(button);
	// Stop at the first frame, waiting for events.
	HFActionStop stop;

	movie.Frame(0)->AddAction( &stop );
	
	// Remove the button from the second frame.
	movie.Frame(1)->RemoveObject(button);
	movie.Frame(1)->AddObject(rect5);
	// Stop at the second frame.
	movie.Frame(1)->AddAction( &stop );


	movie.WriteMovie("HFExampleButton.swf");

	delete rect1;
	delete rect2;
	delete rect3;
	delete rect4;
	delete rect5;
	delete button;
}
