// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 11/05/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFExampleFont.cpp

   To demonstrate HFFont.
   Creates a one-frame movie with:
   
	1) a black background,
	2) two "FLASH HSALF" string of self-defined "silly font", one of red color in depth two,
	   the other of green color in depth one.		
	
****************************************************************************************/

#include "HF3SDK.h"
#include "HFExample.h"

void HLCreateFontMovie()
{
	// Create shapes for some letters

	// I actually created this font on some notebook paper, to demonstrate 
	// that it is actually fairly easy to do.

	// Letter F. Advance = 800
	HFPolygon* letterF = new HFPolygon( 0, 200 );
	letterF->AddStraightLine( 0, 600 );
	letterF->AddStraightLine( 200, 0 );
	letterF->AddStraightLine( 0, -300 );
	letterF->AddStraightLine( 200, 0 );
	letterF->AddStraightLine( 0, -100 );
	letterF->AddStraightLine( -200, 0 );
	letterF->AddStraightLine( 0, -100 );
	letterF->AddStraightLine( 500, 0 );
	letterF->AddStraightLine( 0, -100 );
	letterF->AddStraightLine( -700, 0 );

	// Letter L. Advance = 700
	HFPolygon* letterL = new HFPolygon( 0, 200 );
	letterL->AddStraightLine( 0, 600 );
	letterL->AddStraightLine( 500, 0 );
	letterL->AddStraightLine( 0, -100 );
	letterL->AddStraightLine( -300, 0 );
	letterL->AddStraightLine( 0, -500 );
	letterL->AddStraightLine( -200, 0 );

	// Letter A. Advance = 900
	HFPolygon* letterA = new HFPolygon( 0, 800 );
	letterA->AddStraightLine( 400, -600 );
	letterA->AddStraightLine( 400, 600 );
	letterA->AddStraightLine( -200, 0 );
	letterA->AddStraightLine( -200, -400 );
	letterA->AddStraightLine( -200, 400 );
	letterA->AddStraightLine( -200, 0 );

	// Letter S. Advance = 700
	HFPolygon* letterS = new HFPolygon( 600, 200 );
	letterS->AddStraightLine(	-400,	0 );
	// top left curve of the S
	letterS->AddCurvedLine(		-150,	40,		// The delta from the previous point to the control point.
								-50,	110 );	// The delta from the contol point to the end point.
	letterS->AddCurvedLine(		 50,	110, 
								150,	40 );
	letterS->AddStraightLine(	200,	0 );
	letterS->AddStraightLine(	0,		200 );
	letterS->AddStraightLine(	-400,	0 );
	letterS->AddStraightLine(	0,		100 );
	letterS->AddStraightLine(	400,	0 );
	letterS->AddCurvedLine(		70,		-60, 
								30,		-140 );		// lower right curve of the S
	letterS->AddCurvedLine(		-30,	-140, 
								-70,	-60 );
	letterS->AddStraightLine(	-200,	0 );
	letterS->AddStraightLine(	0,		-100 );
	letterS->AddStraightLine(	400,	0 );
	letterS->AddStraightLine(	0,		-100 );

	// Letter H. Advance = 700
	HFPolygon* letterH = new HFPolygon( 0, 200 );
	letterH->AddStraightLine( 0, 600 );
	letterH->AddStraightLine( 200, 0 );
	letterH->AddStraightLine( 0, -200 );
	letterH->AddStraightLine( 200, 0 );
	letterH->AddStraightLine( 0, 200 );
	letterH->AddStraightLine( 200, 0 );
	letterH->AddStraightLine( 0, -600 );
	letterH->AddStraightLine( -200, 0 );
	letterH->AddStraightLine( 0, 200 );
	letterH->AddStraightLine( -200, 0 );
	letterH->AddStraightLine( 0, -200 );
	letterH->AddStraightLine( -200, 0 );

	// Letter Space. Advance = 700
	HFPolygon* letterSpace = new HFPolygon( 0, 0 );


	// Now add the letters to the font.
	HFFont* font = new HFFont( "Silly Font" );
	font->AddGlyph( letterF, 'F', 800 );
 	font->AddGlyph( letterL, 'L', 700 );
 	font->AddGlyph( letterA, 'A', 900 );
 	font->AddGlyph( letterS, 'S', 700 );
 	font->AddGlyph( letterH, 'H', 700 );
 	font->AddGlyph( letterSpace, ' ', 500 );


	HFMovie movie;

	HFText* text1 = new HFText( "FLASH HSALF", font );	// Creates the text box, with a bounding
																	// rectangle, a string, and a font id.
	text1->SetDepth( 3 );
	text1->SetSolidFill( Red_RGBA );

// 	text1->Translate( 100*FPIXEL, 100*FPIXEL );

	HFRectangle* boundingBox = new HFRectangle( 0, 0, 800, 1000 );
	boundingBox->SetLineColor( Green_RGBA );
	boundingBox->SetSolidFill( Black_RGBA );
	boundingBox->SetDepth( 1 );
// 	boundingBox->Translate( 100*FPIXEL, 100*FPIXEL );

	movie.Frame( 0 )->SetBackgoundColor( Black_RGBA );
	movie.Frame( 0 )->AddObject( text1 );
	movie.Frame( 0 )->AddObject( boundingBox );

	text1->SetDepth( 2 );
//  	text1->Translate( 10*FPIXEL, 10*FPIXEL );
 	text1->Scale( FloatToFixed( 1.2 ), FloatToFixed( 1.2 ) );
	text1->Rotate( 10 * fixed_1 );
	FRGBA halfGreen = {0, 255, 0, 128};
	text1->SetSolidFill( halfGreen );

	movie.Frame( 0 )->AddObject( text1 );

	movie.WriteMovie( "HFExampleFont.swf" );

	delete font;
	delete letterF;
	delete letterL;
	delete letterA;
	delete letterS;
	delete letterH;
	delete letterSpace;
	delete text1;
	delete boundingBox;
}