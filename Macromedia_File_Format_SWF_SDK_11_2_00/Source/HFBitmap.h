// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 10/25/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFBitmap.h

	This header-file contains the declarations of high-level bitmap class.
	Parent class is in the parentheses:

		class HFBitmap; (public HFRectangle)
	
****************************************************************************************/

#ifndef HFBITMAP_H_
#define HFBITMAP_H_

#include "HFRectangle.h"

//! Define a bitmap shape.
/*!	
	\sa HFRectangle, HFShape, HFObject
*/
class HFBitmap : public HFRectangle
{
  public:
        //! Creates a JPEG bitmap.
		/*!	
			\param xmin The x coordinate of the upper left corner of the bounding rectangle.
			\param ymin The y coordinate of the upper left corner of the bounding rectangle.
			\param xmax The x coordinate of the bottom right corner of the bounding rectangle.
			\param ymax The y coordinate of the bottom right corner of the bounding rectangle.
			\param tiled		True for tiled fill, false for clipped fill.
			\param bitmap_X		Width of the bitmap in pixel.
			\param bitmap_Y		Height of the bitmap in pixel.
			\param jpeg			Address of JPEG.
			\param jpegSize	Size of the JPEG file in byte.
			\sa HFRectangle, HFShape, HFObject
		*/
		HFBitmap(int xmin, int ymin, int xmax, int ymax,
				 int bitmapX,
				 int bitmapY,
				 const void* jpeg,
				 int jpegSize );

		/*! */
		~HFBitmap()	{}

        //! Creates a Lossless bitmap.
		/*!	
			\param xmin The x coordinate of the upper left corner of the bounding rectangle.
			\param ymin The y coordinate of the upper left corner of the bounding rectangle.
			\param xmax The x coordinate of the bottom right corner of the bounding rectangle.
			\param ymax The y coordinate of the bottom right corner of the bounding rectangle.
			\param tiled		True for tiled fill, false for clipped fill.
			\param bitmapX		Width of the bitmap in pixel.
			\param bitmapY		Height of the bitmap in pixel.
			\param numPaletteEntries	Number of palette entries.
			\param alpha		True for alpha fill, false for non-alpha fill.
			\param bitmap		Address of bitmap.
			\param palette		Address of palette.
			\sa HFRectangle, HFShape, HFObject
		*/
        HFBitmap(	int xmin, int ymin, int xmax, int ymax,
					int	 format,
					int  bitmap_X,
					int  bitmap_Y,
					int	 numPaletteEntries,
					bool alpha,
					const void* bitmap,
					const void* palette 
				 );

  private:
};

#endif