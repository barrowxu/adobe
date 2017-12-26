// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/15/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFExampleRectangle.cpp

   To demonstrate HFRectangle.
   Creates a five-frame movie with:
   
	1) a white background,
	2) three overlapping squares,
	3) a solid-fill red rectangle is static in depth 1,
	4) a linear-fill blue-black rectangle is static in depth 2,
	5) a radial-fill yellow-violet rectangle is rotating in depth 3;
    6) all of the rectangles have black, 1 pixel-wide border.
	
****************************************************************************************/

#include "HF3SDK.h"
#include "HFExample.h"

void HLCreateRectangleMovie()
{
	HFMovie movie;												// construct a movie object

	HFRectangle* rect1 = new HFRectangle( 0 * FPIXEL, 0 * FPIXEL, 100 * FPIXEL, 100 * FPIXEL );			// top-left rectangle
	HFRectangle* rect2 = new HFRectangle( 50 * FPIXEL, 50 * FPIXEL, 150 * FPIXEL, 150 * FPIXEL );		// middle rectangle
	HFRectangle* rect3 = new HFRectangle( 100 * FPIXEL, 100 * FPIXEL, 200 * FPIXEL, 200 * FPIXEL );		// bottom-right rectangle

	// set rect1 to solid-fill red.
	rect1->SetSolidFill( Red_RGBA );

	// set rect2 to linear-fill blue-black.
	rect2->SetLinearFill( Blue_RGBA, Black_RGBA );

	// set rect3 to radial-fill yellow-violet.
	rect3->SetRadialFill( Yellow_RGBA, Violet_RGBA );

	// set rect1 in depth 1	(at bottom)
	rect1->SetDepth(1);
	// set rect2 in depth 2 (in the middle)
	rect2->SetDepth(2);
	// set rect3 in depth 3.(on top of all)
	rect3->SetDepth(3);
	
	// "add" rect1 and rect2 to frame1(movie dictionary), then "place" them on frame1
	movie.Frame( 0 )->AddObject( rect1 );
	movie.Frame( 0 )->AddObject( rect2 );
	movie.Frame( 0 )->AddObject( rect3 );

	// rect3 is rotating by itself.
	movie.Frame( 1 )->RemoveObject( rect3 );
	rect3->Rotate(22.5 * fixed_1 );
	movie.Frame( 1 )->AddObject( rect3 );
	movie.Frame( 2)->RemoveObject( rect3 );
	rect3->Rotate(45 * fixed_1);
	movie.Frame( 2 )->AddObject( rect3 );
	movie.Frame( 3 )->RemoveObject( rect3 );
	rect3->Rotate(67.5 * fixed_1 );
	movie.Frame( 3 )->AddObject( rect3 );
	movie.Frame( 4 )->RemoveObject( rect3 );
	rect3->Rotate(90 * fixed_1 );
	movie.Frame( 4 )->AddObject( rect3 );
	
	// write movie to SWF file
	movie.WriteMovie("HFExampleRectangle.swf");

	delete rect1;
	delete rect2;
	delete rect3;
}
