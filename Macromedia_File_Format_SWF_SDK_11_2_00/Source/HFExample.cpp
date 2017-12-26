// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 11/08/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

File Summary: HFExample.cpp

The mother of all examples. Shows off and tests all the features of the SWF high level
manager. Draws multiple segments, and a button to progress from one segment to the 
next. HLCreateSuperMovie() is the main function, which calls all the Add*Page functions
to write chunks of SWF.

If you are using this example as a learing tool (a good idea) start from the bottom 
of the file and work up.

The simplest examples are in the other HFExample* files. The very simlpest example
is HFExampleCirle.cpp.

****************************************************************************************/

#include <math.h>

#include "HF3SDK.h"
#include "HFExample.h"

const int BITMAP_X = 32;
const int BITMAP_Y = 32;
const int SIZE_PALETTE = 256;
FRGB rgb[SIZE_PALETTE];									// memory for the palette
unsigned char bitmapLossless[BITMAP_X][BITMAP_Y];		// memory for the bitmap


// AddSoundsPage adds 24 frames of a circle going across the screen. When it changes
// color, a PCM compressed sound gets played.

void AddSoundsPage( HFMovie* movie )
{
	const int offset = 49;
    int i;

	// Create a sound in memory
	U16 soundData[ 11000 ];		// about 1 second at 11kHz mono

	// go for 440 cycles/second, which is 440 * 2pi radians per second
	for ( i = 0; i < 11000; i++ )
	{
		// apply an audio wav
		soundData[i] = U16( sin( double(i) * 440.0 * 2 * 3.14 / 11000.0 ) * 20000 + 30000 );
	}

	HFSound* sound = new HFSound( Snd11k, 
								  Snd16Bit, 
								  SndMono, 
								  11000,		// the number of samples
								  soundData,	// the sample memory
								  22000,		// the amount of memory used to store the samples
								  FDTDefineSound::Comp2 );	// Amount of compression.


	HFCircle* circle = new HFCircle( 100*FPIXEL, 100*FPIXEL, 30*FPIXEL );
	FRGBA lightBlue = { 128, 200, 230, 0xff };
	circle->SetSolidFill( lightBlue );

	// The for loop writes the circle's motion across the stage.
	for ( i = 0; i<24; i++ )
	{
		circle->Translate( i * 10 * FPIXEL, 0 );
		circle->SetDepth( i + 1 );

		if ( i==4 || i==14 )
		{
			if ( i==4 )
				circle->SetSolidFill( Green_RGBA );
			else
				circle->SetSolidFill( lightBlue );

			movie->Frame( offset + i )->AddObject( sound );

			movie->Frame( offset + i )->AddObject( circle );
			movie->Frame( offset + i+1 )->RemoveObject( circle );
		}
		else
		{
			movie->Frame( offset + i )->AddObject( circle );
			movie->Frame( offset + i+1 )->RemoveObject( circle );
		}
	}

	delete sound;
	delete circle;
}


// AddShapesPage puts a triangle, a rectangle, and an hourglass shape on the stage, then 
// writes many instances of the objects. Each object, though it shows up many times on the
// screen, only has one defineTag so takes little memory.

void AddShapesPage( HFMovie* movie )
{
// 	const int offset = 0;
	int i;
	const int offset = 33;

	HFRectangle* rectangle = new HFRectangle( 0, 0, 10000, 2000 );

	// Define the triangle, one method to use the polygon.
	SPOINT triangleData[3] = {	{ 0, 1000 },
								{ 1000, 1000 },
								{ 500, 0 }
							 };

	HFPolygon* triangle = new HFPolygon( triangleData, 3 );

	// Also the polygon class, but the object is built
	// piece by piece rather than being passed in as an array
	// by the constructor.
	HFPolygon* strange = new HFPolygon( 200, 400 );
	strange->AddCurvedLine( -150,  -50, 
							-50,   -150 );
	strange->AddCurvedLine(  50,   -150, 
							 450,  -50 );
	strange->AddCurvedLine(  450,  50, 
							 50,   150 );
	strange->AddCurvedLine(  -50,  150, 
							 -150, 50 );
	strange->AddStraightLine( -600, 200 );
	strange->AddCurvedLine( -150,  50, 
							-50,   150 );
	strange->AddCurvedLine( 50,    150, 
							450,   50 );
	strange->AddCurvedLine( 450,   -50, 
							50,   -150 );
	strange->AddCurvedLine( -50,   -150, 
							-150,   -50 );
	strange->AddStraightLine( -600, -200 );

	strange->SetRadialFill( Green_RGBA, Yellow_RGBA );

	// Create a bunch of rotated rectangles.
	rectangle->SetLinearFill( Yellow_RGBA, Red_RGBA );
	for ( i = 0; i < 16; i += 1 )
	{
		rectangle->Translate( 50*FPIXEL, 100*FPIXEL );
		rectangle->Rotate( i * 10 * fixed_1 );
		rectangle->Scale( fixed_1/2, fixed_1/2 );
		rectangle->SetDepth( 16-i );

		// Add the object to the current frame.
		movie->Frame( offset + i )->AddObject( rectangle );
		// Remove the object from the end of the sequence.
		movie->Frame( offset + 16 )->RemoveObject( rectangle );
	}	

	// Create a bunch of rotated triangles.
	triangle->SetBitmapFillLossless(	FDTDefineBitsLossless::bm8Bit, 
										BITMAP_X, BITMAP_Y, 
										SIZE_PALETTE,
										false,
										bitmapLossless, 
										rgb );
	triangle->Scale( 2*fixed_1, 2*fixed_1 );
	for ( i = 0; i < 16; i += 1 )
	{
		triangle->Translate( 50*FPIXEL, 200*FPIXEL );
		triangle->Rotate( i * 10 * fixed_1 );
		triangle->SetDepth( 32-i );

		movie->Frame( offset + i )->AddObject( triangle );
		movie->Frame( offset + 16 )->RemoveObject( triangle );
	}	

	// Move the hourglass down the screen.
	strange->Scale( 2*fixed_1, 2*fixed_1 );
	for ( i = 0; i < 16; i += 1 )
	{
		strange->Translate( 350*FPIXEL, (100+i*10)*FPIXEL );
		strange->SetDepth( 50-i );
		// Add the object to the current frame.
		movie->Frame( offset + i )->AddObject( strange );
		// Remove the object from next frame.
		movie->Frame( offset + i + 1 )->RemoveObject( strange );
	}

	delete triangle;
	delete strange;
	delete rectangle;
}



// The AddCirclePage places circles, demonstrating fills, line thickness, and
// multiple instances.

void AddCirclePage( HFMovie* movie )
{
	// This function uses 16 frames, beginning at offset.
	const int offset = 17;
    int i;

	HFCircle* circle = new HFCircle( 100*FPIXEL, 80*FPIXEL, 60*FPIXEL );

	// The for loop puts 16 filled green circles on the screen.
	// Each of these circles will write unique shape data, since the
	// fill color changes.
	FRGBA circle_page_color = {0, 0, 0, 255};
 	for ( i = 0; i<16; i++ )
	{
		circle->Translate( 15*i*FPIXEL, 0 );
		circle->SetDepth( i + 2 );

		circle->SetLineWidth( 0 );
		circle_page_color.green = i*16+15;
		circle->SetSolidFill( circle_page_color );

		movie->Frame( offset + i )->AddObject( circle );
		movie->Frame( offset + 16 )->RemoveObject( circle );
	}

	circle->SetLineWidth( 20 );
	circle->SetNoFill();

	// Puts outlined but not filled circles.
	// Since only the matrix changes for these circles, only
	// a placeobject gets written. (Except for the first one.)
	for ( i = 0; i<16; i++ )
	{
		circle->Translate( 15*i*FPIXEL, 150*FPIXEL );

		movie->Frame( offset + i )->AddObject( circle );
		movie->Frame( offset + 16 )->RemoveObject( circle );
	}

	// 3 Bonus circles to show fills.

	// Linear fill
	circle->Translate( 350*FPIXEL, 0*FPIXEL );
	circle->SetDepth( 40 );
	circle->SetLinearFill( Black_RGBA, Red_RGBA );
	movie->Frame( offset + 0 )->AddObject( circle );
	movie->Frame( offset + 16 )->RemoveObject( circle );

	// Gradient fill
	circle->Translate( 350*FPIXEL, 150*FPIXEL );
	circle->SetDepth( 41 );
	circle->SetRadialFill( Black_RGBA, Red_RGBA );
	movie->Frame( offset + 0 )->AddObject( circle );
	movie->Frame( offset + 16 )->RemoveObject( circle );

	// Bitmap fill
	circle->Translate( 0, 0 );
	circle->SetDepth( 42 );
	circle->SetBitmapFillLossless(	FDTDefineBitsLossless::bm8Bit, 
									BITMAP_X, BITMAP_Y, 
									SIZE_PALETTE,
									false,
									bitmapLossless, 
									rgb );

	movie->Frame( offset + 0 )->AddObject( circle );
	movie->Frame( offset + 16 )->RemoveObject( circle );

	delete circle;
}

			

// AddEditTextPage places 4 edit text fields on the screen that you can type in to.
// The even ones word wrap. (This is of limited use, at this point, since you can 
// not program flash with the high level manager.)

void AddEditTextPage( HFMovie* movie )
{
	HFEditText* editText[4];

	editText[0] = new HFEditText( 50*FPIXEL, 50*FPIXEL, 250*FPIXEL, 150*FPIXEL, "EditText field 1." );
	editText[1] = new HFEditText( 300*FPIXEL, 50*FPIXEL, 500*FPIXEL, 150*FPIXEL, "EditText field 2." );
	editText[2] = new HFEditText( 50*FPIXEL, 250*FPIXEL, 250*FPIXEL, 350*FPIXEL, "EditText field 3." );
	editText[3] = new HFEditText( 300*FPIXEL, 250*FPIXEL, 500*FPIXEL, 350*FPIXEL, "EditText field 4." );
	
	for ( int i = 0; i<4; i++ )
	{
		editText[i]->SetWordWrap( i%2 == 0 );		
		movie->Frame( 16 )->AddObject( editText[i] );		// The add object writes an id to the edit text object,
		movie->Frame( 17 )->RemoveObject( editText[i] );	// so it is important to remove the edit text object while														
															// the id is still valid.
		delete editText[i];
	}
}

// AddTextPage adds the 16 frames of text that starts the Flash demo movie.
// It starts by defining an o-so-beautiful font, then adding some text 
// animation.

void AddTextPage( HFMovie* movie )
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
	letterS->AddCurvedLine(		-150,	40, 
								-50,	110 );		// top left curve of the S
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

	delete letterF;
	delete letterL;
	delete letterA;
	delete letterS;
	delete letterH;
	delete letterSpace;

	HFText* text = new HFText( "FLASH", font );	// Creates the text box, with a bounding
													// rectangle, a string, and a font id.

	// put in 16 frames of green "flash" text animation
	FRGBA text_page_color = {0,255,0,0};
	for( int i = 0; i<16; i++ )
	{
		// A color for the text - more opaque with every frame.
		// Normally, only a PlaceObject2 would be written for every
		// frame, but the color information causes a DefineText and
		// a PlaceObject2 to be written. To be safe, assume that the
		// object id changes every time you call AddObject. 
		if ( i == 15 )
			text->SetSolidFill( Blue_RGBA );
		else{
			text_page_color.alpha = i*32+31;
			text->SetSolidFill( text_page_color );
		}

		// process away...
// 		text->Translate( (20-i)*FPIXEL, 100*FPIXEL );
		text->Rotate( (i-15) * 5 * fixed_1 );
		text->Scale( 2.8 * fixed_1, 5 * fixed_1 );

		movie->Frame( i )->AddObject( text );

		// Remove the frame later in the timeline. Note we need to remove it now,
		// since every time the AddObject is called, the object Id changes. But
		// we can remove in the future, which is what is happening here.
		if ( i + 4 < 16 )	
		{
			movie->Frame( i+4 )->RemoveObject( text );
		}
		else if ( i < 15 )
		{
			movie->Frame( 15 )->RemoveObject( text );
		}
		else
		{
			movie->Frame( 16 )->RemoveObject( text );
		}			
	}

	// Try the case where only the PlaceObject2 is used.
	// This puts up the 3 Red Flash text.
	text->Rotate( 0 );
	text->Scale( 2.0 * fixed_1, fixed_1 );
	FRGBA halfRed = {255,0,0,128};
	text->SetSolidFill( halfRed );

	text->Translate( 80*FPIXEL, 0 );
	text->SetDepth( 20 );
	movie->Frame( 0 )->AddObject( text );
	movie->Frame( 16 )->RemoveObject( text );

	text->Translate( 80*FPIXEL, 120*FPIXEL );
	movie->Frame( 0 )->AddObject( text );
	movie->Frame( 16 )->RemoveObject( text );

	text->Translate( 80*FPIXEL, 240*FPIXEL );
	movie->Frame( 0 )->AddObject( text );
	movie->Frame( 16 )->RemoveObject( text );

	delete text;
	delete font;
}
	
void HLCreateSuperMovie()
{
	// The movie object - contains all the frames and objects for this Flash demo.
	HFMovie movie;
	
	
	// ----- Creating a bitmap for testing --------
	// Bitmaps are used over and over - and since bitmap memory is not owned or
	// deleted by either the high or low level manager, we can share.
	int i, j;

	// Fill the bitmap palette with a green gradient.
	for ( i = 0; i<SIZE_PALETTE; i++ )
	{
		rgb[i].red = 0;
		rgb[i].green = i;
		rgb[i].blue = 0;
	}

	// Creates a bitmap in memory. The bitmap is black in the upper left and
	// green in the lower right. Edges and the diagonal are drawn in green.
	for ( i=0; i<BITMAP_X; i++ )
	{
		for ( j=0; j<BITMAP_Y; j++ )
		{
			bitmapLossless[i][j] = ( (i%4) * 62 + (j%4) * 62 );			// shades of green everywhere else
		}
	}

	// --------- Creating a shared button ------------------
	// First create the button that is on every page:
	// This code creates the 4 rectangles that make up the button.
	// 1) the Normal button
	HFRectangle rect1( 450 * FPIXEL, 350 * FPIXEL, 540 * FPIXEL, 390 * FPIXEL );
	// 2) mouse over button
	HFRectangle rect2( 450 * FPIXEL, 350 * FPIXEL, 540 * FPIXEL, 390 * FPIXEL );
	// 3) button down
	HFRectangle rect3( 450 * FPIXEL, 350 * FPIXEL, 540 * FPIXEL, 390 * FPIXEL );
	// 4) button hit object, which is never visible but defines the hit area.
	HFRectangle rect4( 450 * FPIXEL, 350 * FPIXEL, 540 * FPIXEL, 390 * FPIXEL );

	// Radial fill the buttons we see.
	rect1.SetRadialFill( HunterGreen_RGBA, Black_RGBA );
	rect2.SetRadialFill( Green_RGBA, Black_RGBA );
	rect3.SetRadialFill( Blue_RGBA, Black_RGBA );
	rect4.SetSolidFill( Black_RGBA );

	// And finally, create the button.
	HFButton* button = new HFButton( &rect1, &rect2, &rect3, &rect4);

	// Place the button and put it on top, high in the sorting order.
	// It will be on every page.
	button->SetDepth( 200 );

	// There is a drawback to buttons: the actions they take are part of the button 
	// define. So it is not possible (in this version...) to use a button, change its 
	// programming, and then use it again. That is why the button only plays, and the
	// flash movie always stops.

	HFActionPlay play;
	HFActionStop stop;

	button->QueueEvent( &play, RELEASE );
	movie.Frame( 0 )->AddObject( button );

	// --------- Make the movie ------------------
	// Set up movie properties
	movie.Frame( 0 )->SetBackgoundColor( White_RGBA );
	movie.SetFrameRate( 8 );	// 8 frames per second - we use the default size, 550x400

	
	// Now we call sub pages to test various features:
	AddTextPage( &movie );		// Regular text test.		Frames  0-15
	AddEditTextPage( &movie );	// Editable text.			Frame     16
	AddCirclePage( &movie );	// Circles, fills.			Frame  17-32
	AddShapesPage( &movie );	// Polygons and squares		Frames 33-48
	AddSoundsPage( &movie );	// Polygons and squares		Frames 49-72

	movie.Frame( 15 )->AddAction( &stop );
	movie.Frame( 16 )->AddAction( &stop );
	movie.Frame( 32 )->AddAction( &stop );
	movie.Frame( 48 )->AddAction( &stop );
	movie.Frame( 72 )->AddAction( &stop );

	delete button;

	movie.WriteMovie( "HFExample.swf" );
}
