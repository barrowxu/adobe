// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/25/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFExampleSquare.cpp

	A random mish-mash of test cases we use internally. It is suggested you avoid, avoid,
	avoid.

   To demonstrate HFRectangle, HFBitmap, HFPolygon.
   Creates a one-frame movie with:

	1) a brass background,
	2) a small square with white (default) solid fill and 1 pixel, black border;
	3) a red square with red solid fill and 10 pixel, maroon border;
	3) a JPEG bitmap of a square containing letter "J";
	4) a Lossless bitmap of a green square with a blue diagonal line through it and a blue
	   border;
	5) a square EditText field initially containing string "This is an EditText object.";
	6) a triangle with empty body, and 1 pixel black border;
	7) a pentagon with red-violet radial fill color, and 1 pixel black border.

****************************************************************************************/

#include "HF3SDK.h"
#include "HFExample.h"


void HLCreateSquareMovie(){
	HFMovie movie;												// construct a movie object

	// rectangle1 is red solid fill and has 10 pixel maroon border.
	HFRectangle* rectangle1 = new HFRectangle( 0 * FPIXEL, 0 * FPIXEL, 200 * FPIXEL, 200 * FPIXEL );
	rectangle1->SetSolidFill( Red_RGBA );
	rectangle1->SetLineWidth(10 * FPIXEL);
	rectangle1->SetLineColor( Maroon_RGBA );
	rectangle1->SetDepth(2);
	rectangle1->Translate( 100 * FPIXEL, 0 );

//	HFRectangle* rectangle2 = new HFRectangle( 250 * FPIXEL, 0 * FPIXEL, 450 * FPIXEL, 200 * FPIXEL );

	// rectangle3 is the small square with white (default) solid fill and 
	//1 pixel, black border;
	HFRectangle* rectangle3 = new HFRectangle( 0 * FPIXEL, 250 * FPIXEL, 100 * FPIXEL, 350 * FPIXEL );

	const int BITMAP_X		= 128;		// The size of the test bitmap.
	const int BITMAP_Y		= 128; 

	// Load in a JPeg
	FILE* fp = fopen( "bm128.jpg", "rb" );
	FLASHASSERT( fp );

	// get the file size
	fseek( fp, 0, SEEK_END );
	int jpegSize = ftell( fp );
	fseek( fp, 0, SEEK_SET );

	// load the jpeg to memory
	unsigned char bitmap[BITMAP_X*BITMAP_Y*3];		// more memory than we need for a jpeg image

	fread( bitmap, 1, jpegSize, fp );

	fclose(fp);
// 	rectangle2->SetFillBitmap(false, BITMAP_X, BITMAP_Y, bitmap, jpegSize);

	// The JPEG bitmap of a square containing letter "J".
	HFBitmap* bitmapShape = new HFBitmap( 250 * FPIXEL, 50 * FPIXEL, 450 * FPIXEL, 250 * FPIXEL, BITMAP_X, BITMAP_Y, bitmap, jpegSize );
// 	bitmapShape->SetLineWidth( 40 );
// 	bitmapShape->SetLineColor( Green_RGBA );

	const int SIZE_PALETTE = 256;
	FRGB rgb[SIZE_PALETTE];									// memory for the palette
	unsigned char bitmapLossless[BITMAP_X][BITMAP_Y];		// memory for the bitmap
	int i, j;

	// Fill the palette with a green gradient.
	for ( i = 0; i<SIZE_PALETTE; i++ )
	{
		rgb[i].red = 0;
		rgb[i].green = i;
		rgb[i].blue = 0;
	}

	// One palette is made blue, so that the bitmap can be outlined in a blue box.
	rgb[SIZE_PALETTE-1].red   = 0;
	rgb[SIZE_PALETTE-1].green = 0;
	rgb[SIZE_PALETTE-1].blue  = 255;

	// Creates a bitmap in memory. The bitmap is black in the upper left and
	// green in the lower right. Edges and the diagonal are drawn in green.
	for ( i=0; i<BITMAP_X; i++ )
	{
		for ( j=0; j<BITMAP_Y; j++ )
		{
			if ( i == j															// the diagonal
			     || i == 0 || j == 0 || i == (BITMAP_X-1) || j == (BITMAP_Y-1)  // the edges  
			   )
				bitmapLossless[i][j] = SIZE_PALETTE-1;		// blue on the edges and diagonal
			else
				bitmapLossless[i][j] = ( i + j );			// shades of green everywhere else
		}
	}

	// The Lossless bitmap of a green square with a blue diagonal line through it and a blue border.
	HFBitmap* bitmapShape2 = new HFBitmap(	 300 * FPIXEL, 200 * FPIXEL, 500 * FPIXEL, 400 * FPIXEL, 
											FDTDefineBitsLossless::bm8Bit,
											BITMAP_X, BITMAP_Y, 
											SIZE_PALETTE,
											false,
											bitmapLossless, 
											rgb );
	// EditText square
	HFEditText* editText = new HFEditText( 50 * FPIXEL, 50 * FPIXEL, 250 * FPIXEL, 250 * FPIXEL, "This is an EditText object." );

	// Polygon
	SPOINT triangleData[] = {	{ 25 * FPIXEL, 75 * FPIXEL },
								{ 75 * FPIXEL, 75 * FPIXEL },
								{ 50 * FPIXEL, 25 * FPIXEL }
							};
	HFPolygon* triangle = new HFPolygon( triangleData, 3 );

	// Polygon
	SPOINT pentagonData[] = {	{ 150 * FPIXEL, 75 * FPIXEL },
								{ 200 * FPIXEL, 100 * FPIXEL },
								{ 175 * FPIXEL, 125 * FPIXEL },
								{ 125 * FPIXEL, 125 * FPIXEL },
								{ 100 * FPIXEL, 100 * FPIXEL }
							};
	HFPolygon* pentagon = new HFPolygon( pentagonData, 5 );
	pentagon->SetRadialFill( Red_RGBA, Violet_RGBA );

// 	HFFont* font = 0;
// 	FILE* fontp = fopen( "font.frg", "rb" );
// 	if ( fontp )
// 	{
// 		char fontData[20801];
// 
// 		fread( fontData, 20801, 1, fontp );
// 		font = new HFFont( fontData, 20801 );
// 	}
// 
	rectangle1->SetDepth(3);
	bitmapShape->SetDepth(4);
	rectangle3->SetDepth(5);
	bitmapShape2->SetDepth(6);
	editText->SetDepth(7);
	triangle->SetDepth( 8 );
	pentagon->SetDepth( 9 );

	movie.Frame( 0 )->AddObject( rectangle1 );
	movie.Frame( 0 )->AddObject( bitmapShape );
	movie.Frame( 0 )->AddObject( rectangle3 );
	movie.Frame( 0 )->AddObject( bitmapShape2 );
	movie.Frame( 0 )->AddObject( editText );
	movie.Frame( 0 )->AddObject( triangle );
	movie.Frame( 0 )->AddObject( pentagon );
// 	movie.Frame( 0 )->AddObject( font );

	// Set the background color of frame1 to brass and add it to movie.
	movie.Frame( 0 )->SetBackgoundColor( Brass_RGBA );

	// Create the movie.
	movie.WriteMovie( "HFExampleSquare.swf" );

	delete pentagon;
	delete triangle;
	delete editText;
	delete rectangle1;
	delete rectangle3;
	delete bitmapShape;
	delete bitmapShape2;
}