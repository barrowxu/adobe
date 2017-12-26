// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 09/08/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FExampleJPeg.cpp

   Creates a one frame movie with:
   
	1) a red background, and
	2) a lossless bitmap of a green square with a red diagonal line through it.

****************************************************************************************/

#include "F3SDK.h"


void CreateJPegMovie()
{
	const FColor red(0xff, 0, 0);

	const int BITMAP_X		= 128;		// The size of the test bitmap.
	const int BITMAP_Y		= 128; 
	const int ORIGIN_X		= 300;
	const int ORIGIN_Y		= 200;

	// A container of all the tags in the movie.
	FObjCollection allTags;

	// A tag to define the background color, red.
	FCTSetBackgroundColor* background = new FCTSetBackgroundColor( new FColor( red ) );
	allTags.AddFObj(background);	// Now add the background color tag to the collection of tags.


	// Load in a JPeg
	FILE* fp = fopen( "bm128.jpg", "rb" );
	FLASHASSERT( fp );

	if ( fp )
	{
		// get the file size
		fseek( fp, 0, SEEK_END );
		int jpegSize = ftell( fp );
		fseek( fp, 0, SEEK_SET );

		// load the jpeg to memory
		unsigned char bitmap[BITMAP_X*BITMAP_Y*3];		// more memory than we need for a jpeg image

		fread( bitmap, 1, jpegSize, fp );

		// The define tag for the jpeg.
		FDTDefineBitsJPEG2* bits = new FDTDefineBitsJPEG2( bitmap,		// address of image data
														   jpegSize		// and how big it is												     );
														 );
		allTags.AddFObj( bits );

		//Construct the FDTDefineShape which will be the rectangle image
		FRect* rectBounds = new FRect( 0, 0, 1*SCoord1, 1*SCoord1 );    // Coordinate values are in TWIPS - it
																		// doesn't seem to matter what these are, as
																		// long as they are a rectangle.
		FDTDefineShape* rectangle = new FDTDefineShape(rectBounds);

		//This first matrix seems to be required by Flash.
		FMatrix* matrix0 = new FMatrix( true, 10*Fixed1, 10*Fixed1, false, 0, 0, 0, 0 );
		FFillStyle* fill0 = new FFillStyleBitmap( false, 0xffff, matrix0 );

		// This is the actual bitmap.
 		FMatrix* matrix1 = new FMatrix( true,				// has scale.
										20*Fixed1,			// the scale of 20 seems to work - don't know why.
										20*Fixed1,		
										false,				// no skew.
										0, 
										0, 
										ORIGIN_X*SCoord1,	// translate to the origin of the rectangle
										ORIGIN_Y*SCoord1 
									  );
		FFillStyle* fill1 = new FFillStyleBitmap(	false,			// not tiled
													bits->ID(),		// use the bitmap we just created
													matrix1			// use the matrix we just created
												);

		// Now the fillstyles (bitmaps) are added to the FDTDefineShape.
		rectangle->AddFillStyle(fill0);
		rectangle->AddFillStyle(fill1);
		
		//Since we are done creating fill and line styles, indicate so:
		rectangle->FinishStyleArrays();;

		FShapeRec* rectangleShapeRecords[6];
		rectangleShapeRecords[0] = new FShapeRecChange( false,						
														true, 
														true, 
														false, 
														true, 
														(ORIGIN_X+BITMAP_X)*SCoord1, 
														(ORIGIN_Y+BITMAP_Y)*SCoord1, 
														0, 
														2, 
														0, 
														0, 
														0
													  );
		rectangleShapeRecords[1] = new FShapeRecEdgeStraight( -BITMAP_X*SCoord1, 0 );
		rectangleShapeRecords[2] = new FShapeRecEdgeStraight( 0, -BITMAP_Y*SCoord1  );
		rectangleShapeRecords[3] = new FShapeRecEdgeStraight( BITMAP_X*SCoord1, 0  );
		rectangleShapeRecords[4] = new FShapeRecEdgeStraight( 0, BITMAP_Y*SCoord1  );
		rectangleShapeRecords[5] = new FShapeRecEnd();
		
		//Add the shape records to the rectangle shape object
		for ( int i = 0;  i < 6 ;  i++)
			rectangle->AddShapeRec(rectangleShapeRecords[i]);

		//Add the rectangle to the given object collection
		allTags.AddFObj(rectangle);

		//create a place object tag which puts the rectangle on the display list
		FCTPlaceObject2 *placeRectangle = new FCTPlaceObject2(false, // ~ _hasClipDepth
															  false, true, false, 
															  10, rectangle->ID(), 0, 0, 0, 0, 0/**/);

		//add the place object tag to the FObjCollection
		allTags.AddFObj(placeRectangle);

		//construct a show frame object
		FCTShowFrame *showFrame = new FCTShowFrame();
		allTags.AddFObj(showFrame);

		//now create the movie
		allTags.CreateMovie("FExampleJpeg.swf", 11000, 8000, 12);

		fclose( fp );
	}
}
