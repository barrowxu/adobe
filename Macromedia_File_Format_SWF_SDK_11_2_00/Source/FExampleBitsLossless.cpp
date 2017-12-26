// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 09/08/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FExampleBitsLossless.cpp

   Creates a one frame movie with:
   
	1) a red background, and
	2) a bitmap of a green square with a blue diagonal line through it.

****************************************************************************************/

#include "F3SDK.h"

void CreateBitsMovie()
{
	const FColor red(0xff, 0, 0);
	const FColor black(0, 0, 0);

	const int SIZE_PALETTE  = 256;		// For this example, we are writing a 256 color image.
	const int BITMAP_X		= 128;		// The size of the test bitmap.
	const int BITMAP_Y		= 128; 
	const int ORIGIN_X		= 300;		// Where the bitmap is located in the flash window. Flash puts
	const int ORIGIN_Y		= 200;		// the origin in the upper left.

	// A container of all the tags in the movie.
	// There are two categories of tags: definition and control. Definition tags manage resources such as 
	// shapes, text, bitmap, and buttons. Control tags control the display list and enable actions such 
	// as stopping or starting the animation. 
	FObjCollection allTags;

	// A tag to define the background color, red.
	FCTSetBackgroundColor* background = new FCTSetBackgroundColor( new FColor( red ) );
	allTags.AddFObj(background);	// Now add the background color tag to the collection of tags.
									// When the player reads this tag, the background will turn red.

	// A Bitmap is needed for this example. Rather than load (and parse) one from disk, a simple bitmap
	// is created here in memory. It is a 1 byte per pixel bitmap with a 256 color palette.

	FRGB rgb[SIZE_PALETTE];							// memory for the palette
	unsigned char bitmap[BITMAP_X][BITMAP_Y];		// memory for the bitmap
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
				bitmap[i][j] = SIZE_PALETTE-1;		// blue on the edges and diagonal
			else
				bitmap[i][j] = ( i + j );			// shades of green everywhere else
		}
	}

	// Finally! The define tag for the lossless bits.
	// The DefineBitsLossless tag is composed of some header information followed by the palette and
	// bitmap data. The bitmap and palette are passed in uncompressed, and are then compressed by the
	// FDTDefineBitsLossless object before being written to the Flash SWF file.
	FDTDefineBitsLossless* bits = new FDTDefineBitsLossless( FDTDefineBitsLossless::bm8Bit,    // format	
															 BITMAP_X,			// width
															 BITMAP_Y,			// height
															 SIZE_PALETTE, 		// number of palette entries
															 rgb,				// address of palette
															 bitmap				// address of image data
														   );

	allTags.AddFObj( bits );	// Now add the the allTags list. Note that it will not appear on the 
								// screen until a DefineShape is created to support it.


	// Now the DefineShape which describes a rectangle is constructed. The rectangle will be filled with 
	// the bitmap and displayed. This is the mechanism for getting the bitmap to appear on-screen.

	// The first step is to create the DefineShape from a rectangle.
	FRect* rectBounds = new FRect( 0, 0, 1*SCoord1, 1*SCoord1 );    // Coordinate values are in TWIPS - it
																	// doesn't seem to matter what these are, as
																	// long as they are a rectangle.
	FDTDefineShape* rectangle = new FDTDefineShape(rectBounds);

    // This is the bitmap fill.
 	FMatrix* matrix1 = new FMatrix( true,			// Has scale terms.
									20*Fixed1,		// A scale of 20 fully fills the rectangle. A larger or
									20*Fixed1,		// smaller value creates a correspondingly sized bitmap.
									false,			// No skew terms
									0, 
									0, 
									ORIGIN_X*SCoord1,	// Translate the bitmap to the origin of the 
									ORIGIN_Y*SCoord1	// rectangle on the screen.
								  );
	FFillStyle* fill1 = new FFillStyleBitmap(	false,			// Not tiled
												bits->ID(),		// The ID of the bitmap.
												matrix1			// A pointer to the matrix.
											);

	// Now the fillstyles just created are added to the DefineShape.
	U32 fillStyle1_ID = rectangle->AddFillStyle(fill1);		// fillStyle1_ID is 2

	// Add black border of 200 twips to line style array.
	U32 blackLineStyleID = rectangle->AddLineStyle(200, new FColor( black));

	//Since we are done creating fill and line styles, indicate so:
	rectangle->FinishStyleArrays();

	// To actually define the rectangle that will be filled with the green bitmap,
	// 6 Shape Records are added:
	//   - the first tells flash that new shape information is coming
	//   - the next four define the bounds of a rectangle
	//   - the last is an end tag.


	// MIKE: this one is yours.
	FShapeRec* rectangleShapeRecords[6];
	rectangleShapeRecords[0] = new FShapeRecChange( false,			
													true,			
													true, 
													false, 
													true, 
													(ORIGIN_X+BITMAP_X)*SCoord1,	// The origin of our rectangle
													(ORIGIN_Y+BITMAP_Y)*SCoord1,	// for the purpose of drawing the lines, below.
													0,					// fillStyle0 is empty
												    fillStyle1_ID,				// the actual bitmap used
													blackLineStyleID, 
													0, 
													0
												  );

	// The edges of the rectangle are constructed from 4 FShapeRecEdge objects. The FShapeRecEdge can 
	// be constructed with either a FEdgeRecStraight or a FEdgeRecCurved. Clearly for this example a
	// FEdgeRecStraight is needed.
	rectangleShapeRecords[1] = new FShapeRecEdgeStraight( -BITMAP_X*SCoord1,	// dX
														  0						// dY
														);
	rectangleShapeRecords[2] = new FShapeRecEdgeStraight(  0, -BITMAP_X*SCoord1 );
	rectangleShapeRecords[3] = new FShapeRecEdgeStraight(  BITMAP_X*SCoord1, 0 );
	rectangleShapeRecords[4] = new FShapeRecEdgeStraight(  0, BITMAP_X*SCoord1 );
	rectangleShapeRecords[5] = new FShapeRecEnd();
	
	//Add the shape records to the rectangle shape object.
	for (i = 0;  i < 6 ;  i++)
		rectangle->AddShapeRec(rectangleShapeRecords[i]);

	//Add the rectangle to the collection.
	allTags.AddFObj(rectangle);

	// MIKE: some of these tags you'll need to explain.

	// Create a place object tag which is the cue to Flash to display the rectangle (which displays the
	// bitmap) on the frame.
	FCTPlaceObject2 *placeRectangle = new FCTPlaceObject2( false, // ~ _hasClipDepth
														   false,
														   true, 
														   false, 
														   1,				// The Z sort depth. One is on the bottom.
														   rectangle->ID(),	// ID of the object to place.
														   0, 
														   0, 
														   0, 
														   0,
														   0
														 );

	//Add the place command to the collection.
	allTags.AddFObj(placeRectangle);

	//The command to show this frame.
	FCTShowFrame *showFrame = new FCTShowFrame();
	allTags.AddFObj(showFrame);

	//Writes the movie, described by the tag collection, to the given file.
	allTags.CreateMovie( "FExampleBitsLossless.swf",	// filename
						  550*SCoord1,		// width of the movie
						  400*SCoord1,		// height of the movie
						  12				// frames per second
					   );
}
