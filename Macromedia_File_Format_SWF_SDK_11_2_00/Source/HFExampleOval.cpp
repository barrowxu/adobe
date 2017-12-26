// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/29/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFExampleOval.cpp

   To demonstrate HFOval.
   Creates a four-frame movie with:
   
	1) a white background,
	2) an oval appearing, disappearing, showing with red fill color, then disappearing again.
	3) the inital oval has empty body (white solid fill) and green, 1 pixel-wide border.
	
****************************************************************************************/

#include "HF3SDK.h"
#include "HFExample.h"

void HLCreateOvalMovie()
{	
	HFMovie movie;
	
	// Create an oval.
	HFOval oval( 100 * FPIXEL, 100 * FPIXEL, 150 * FPIXEL, 200 * FPIXEL );
	
// frame-1
	oval.SetLineColor( Green_RGBA );					
	movie.Frame( 0 )->AddObject( &oval );

// frame-2
	movie.Frame( 1 )->RemoveObject( &oval );

// frame-3
	oval.SetSolidFill( Red_RGBA );					
	movie.Frame( 2 )->AddObject( &oval );

// frame-4
	movie.Frame( 3 )->RemoveObject( &oval );

	movie.WriteMovie("HFExampleOval.swf");
}
