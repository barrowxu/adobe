// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 10/25/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFBitmap.cpp

  This source file contains the definition for high-level bitmap functions,

		Class						Member Function
	
	  HFBitmap					HFBitmap(int, int, int, int, void*, int);
								HFBitmap(int, int, int, int, int, int, int, int, bool,
										 void*, void*);

****************************************************************************************/

#include "HFBitmap.h"


//////////////////////////////////////////////////////////////////////////////////////
//  --------  HFBitmap  --------------------------------------------------------------

// JPEG bitmap.
HFBitmap::HFBitmap(	 int _xmin, int _ymin, int _xmax, int _ymax,
					 int _bitmapX,
					 int _bitmapY,
					 const void* _jpeg,
					 int _jpegSize )

	: HFRectangle( _xmin, _ymin, _xmax, _ymax )		// set bounding rectangle.
{
	SetBitmapFillJpeg( _bitmapX, _bitmapY, _jpeg, _jpegSize );
	lineWidth = 0;
}


// Lossless bitmap.
HFBitmap::HFBitmap(	int xmin, int ymin, int xmax, int ymax,
					int	 format,
					int  bitmap_X,
					int  bitmap_Y,
					int	 numPaletteEntries,
					bool alpha,
					const void* bitmap,
					const void* palette 
				 )
 	: HFRectangle( xmin, ymin, xmax, ymax )			// Set bounding rectangle.
{
	SetBitmapFillLossless( format, bitmap_X, bitmap_Y, numPaletteEntries, alpha, bitmap, palette );
	lineWidth = 0;
}


