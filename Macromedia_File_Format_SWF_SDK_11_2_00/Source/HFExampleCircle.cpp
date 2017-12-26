// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/26/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFExampleCircle.cpp

   To demonstrate HFCircle.
   Creates a one-frame movie with:
   
	1) a white background,
	2) a big yellow circle with green border at top-left, and 
	3) a small white circle with and black border at bottom right,
	4) both circles use default line-width (20 twips) for their borders.

****************************************************************************************/

#include "HF3SDK.h"
#include "HFExample.h"

void HLCreateCircleMovie()
{
	HFMovie movie;												// construct a movie object
		
	HFCircle* bigCircle = new HFCircle( 100 * FPIXEL, 100 * FPIXEL, 100 * FPIXEL );		// construct a big circle
	HFCircle* smallCircle = new HFCircle( 250 * FPIXEL, 250 * FPIXEL, 15 * FPIXEL );	// construct a small circle

	// set line-color and solid-fill-color for bigCircle
	bigCircle->SetLineColor( Green_RGBA );					
	bigCircle->SetSolidFill( Yellow_RGBA );
	// smallCircle use defaults for line-color and solid-fill-color, so do nothing

	// "add" circle1 and circle2 to frame1(movie dictionary), then "place" them on frame1
	movie.Frame( 0 )->AddObject( bigCircle );
	movie.Frame( 0 )->AddObject( smallCircle );

	// write movie to SWF file
	movie.WriteMovie("HFExampleCircle.swf");

	delete bigCircle;
	delete smallCircle;
}


	