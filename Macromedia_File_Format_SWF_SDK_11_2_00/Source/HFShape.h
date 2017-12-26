// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/15/1999.
// Last Modified On 11/09/1999.
// Lee Thomason: new interface to fills, bitmap implementation. 11/1999

/****************************************************************************************

				File Summary: HFShape.h

	This header-file contains the declarations of high-level shape class.
	Parent class is in the parentheses:

		class HFShape; (public HFObject)

****************************************************************************************/

#ifndef HFSHAPE_H_
#define HFSHAPE_H_

#include "HFColors.h"
#include "HFObject.h"
#include "FPrimitive.h"
#include "FDTShapes.h"

//! Superclass for all high level shapes.
/*!	The HFShape is an abstract class which is the parent class of rectangle, circle, etc. 
	The important function of shape is to provide an interface for setting line, fill,
	and position properites.<br>
	
	Lines: 
	All shapes can be outlined. (Even bitmaps). The line thickness and color can be 
	set.<br>
	
	Fills: 
	There are 5 types of fills: solid color, linear gradient, radial gradient,
	jpeg bitmap, and lossless bitmap. The fills will work even with oddly shaped Shapes.
	However, not all shapes can be filled. (Setting the solid fill of a bitmap, for intance, 
	is probably not a good idea.)<br>
	
	Positioning: 
	Translate, Rotate, Scale. The positioning calls changes the shape
	position relative to its original position. For example,
	Translate( 10, 10 ) followed by Translate( 10, 10 ), would move the 
	object 10 twips down and right from its original position; the 
	effect of a Positioning call is not cumlative.
	\sa HFObject
*/
class HFShape : public HFObject 
{
public:
	
	// The constructor takes a bounding rect from the child object.
	HFShape( int xmin, int ymin, int xmax, int ymax );

	virtual ~HFShape();

	// ---------- Line Styles ----------------------------------
	//! Set the width of the shape outline.
	/*!	If the line width is set to zero, no line is displayed.
		\param _lineWidth The line width in twips.	*/
	void		SetLineWidth( int _lineWidth )					{ lineWidth = _lineWidth;
																  defineWritten = false;  }
	//! Get the line width.
	/*!	\return Return the line width in twips.	*/
	int			GetLineWidth()									{ return lineWidth; }

	//! Set the line color.
	/*!	\param _lineColor The line color. Alpha is currently supported.	*/
	void		SetLineColor( const FRGBA& _lineColor );

	//! Get the line color.
	/*!	\return Return the line color.	*/
	FRGBA		GetLineColor()									{ return lineColor;	}

	// ---------- Fills ----------------------------------

	//! Turns off fill for the object.
	/*! The shape will not be filled, and will only be an outline.
	 */
	void		SetNoFill()										{ fillType = NO_FILL;
																  defineWritten = false;  }

	//! Solid fills the shape.
	/*!	\param fillColor The solid fill color. Alpha is currently supported. */
	void		SetSolidFill( const FRGBA& fillColor );

	//! Get the solid fill color.
	/*!	\return Return the solid fill color.	*/
	FRGBA		GetSolidFillColor()								{ return solidFillColor;  }

	//! Fills the shape with a linear gradient.
	/*! The shape will be filled with a linear gradient from
		the first to the second color. The fill center is 
		defaulted at the center of the shape.
		\param left  The color on the left-most of color-ramp.
		\param right The color on the right-most of color-ramp.
	 */
	void SetLinearFill( const FRGBA& left, const FRGBA& right );

	//! Set the linear fill center. 	
	/*! Coordinates are in untransformed object coordinates. 
		\param centerX The x coordiate of the linear fill center.
		\param centerY The y coordiate of the linear fill center. */
	void SetLinearFillCenter( int centerX, int centerY );

	//! Fills the shape with a radial gradient.
	/*! The shape will be filled with a radial gradient from
		the first to the second color. The fill center is 
		defaulted at the center of the shape.
		\param center  The color on the center of concentric color-ramp circles.
		\param outside The color on the outer-most of concentric color-ramp circles.
	 */
	void SetRadialFill( const FRGBA& center, const FRGBA& outside );

	//! Set the linear fill center. 	
	/*! Coordinates are in untransformed object coordinates. 
		\param centerX The x coordiate of the radial fill center.
	    \param centerY The y coordiate of the radial fill center. */
	void SetRadialFillCenter( int centerX, int centerY );

	//! Fills the shape with a JPEG image.
	/*!	The JPEG data passed in will be unmodified by this call.
		\param bitmap_X		Width of the bitmap in pixel.
		\param bitmap_Y		Height of the bitmap in pixel.
		\param JPEG			Pointer a JPEG image data.
		\param JPEG_size	Size of the JPEG data in bytes.
		\return Returns the ID of this JPEG bitmap fill. */
	int	SetBitmapFillJpeg(	int bitmap_X,
							int bitmap_Y,
							const void*JPEG,
							int JPEG_size
						 );

	//! Fills the shape with an image compressed without any quality loss.
	/*!	The image data passed in will be unmodified by this call.
		\param format		Format type. See FDTDefineBitsLosslessBase for a list of formats.
		\param bitmap_X		Width of the bitmap in pixel.
		\param bitmap_Y		Height of the bitmap in pixel.
		\param numPaletteEntries	Number of palette entries. 0 for many formats.
		\param alpha		True if alpha data is included. The value of this 
							parameter must be consistent with the format.
		\param bitmap		Address of bitmap in memory.
		\param palette		Address of palette, if applicable.
		\return Return		the ID of this Lossless bitmap fill.	*/
	int	 SetBitmapFillLossless(	int	 format,
								int  bitmap_X,
								int  bitmap_Y,
								int	 numPaletteEntries,
								bool alpha,
								const void* bitmap,
								const void* palette 
							 );
	
	// ---------- Positioning ----------------------------------
	//! Moves the Shape.
	/*! Translate, like all the positioning calls, changes the objects
	 *	position relative to the position it was created at. In other words,
	 *	Translate( 10, 10 ) followed by Translate( 10, 10 ), would move the 
	 *  object 10 twips down and right from its original position; the 
	 *  effect of a Translate call is not cumlative.
		\param x horizontal motion in twips
		\param y vertical (positive down) motion in twips
	 */
	void Translate( int x, int y )		{ translateX = x; translateY = y; }

	//! Rotates the shape about its own center.
	/*!	\param degree Rotation in degrees, using fixed point notation.
	 */
	void Rotate( SFIXED degree )		{ rotation = degree;	}

	//! Scales the shape about its own center.
	/*!	\param _scaleX horizontal scaling in fixed point notation.
		\param _scaleY vertical scaling in fixed point notation.
	 */
	void Scale( SFIXED _scaleX, SFIXED _scaleY )	{ scaleX = _scaleX; scaleY = _scaleY; }	
		
	// Methods for internal use.
	// Called by the frame to add this object to a linked list.
	virtual void AddToObjectList(std::list<FObj*>* objList, HFMovie* movie) = 0;

protected:
 	void AddLinearFillColor( U8 ratio, const FRGBA& linearFillColor );
 	void AddRadialFillColor( U8 ratio, const FRGBA& radialFillColor );

	virtual bool		HasMatrix();
	virtual FMatrix*	CreateMatrix();

	FRect	bounds;

	int		lineWidth;
	FRGBA	lineColor;
	U32		lineStyleID;
	U32		colorFillID;
	int		translateX, translateY;
	SFIXED	rotation;
	SFIXED	scaleX, scaleY;

	int		fillType;

	enum {	NO_FILL,
			SOLID_FILL,
			LINEAR_GRADIENT_FILL,
			RADIAL_GRADIENT_FILL,
			BITMAP_FILL
		 };
	
	// solid fill
	FRGBA		solidFillColor;

	enum { JPEG, LOSSLESS };
	struct BitmapData 
	{
		int		type;
		int		bitmap_X;
		int		bitmap_Y;
// 		void*	data;
		int		JPEG_size;
		FDT*	fdt;
	};

	BitmapData	bitmapFill;

	// Linear and Radial fill
	FMatrix*	fillMatrix;
	FGradient*	fillGradient;
	
	// Tiled Bitmap fill
	U16			tiledFillBitmapID;
	FMatrix		tiledFillBitmapMatrix;

	// Clipped Bitmap fill  ClippedFill
	U16			clippedFillBitmapID;
	FMatrix		clippedFillBitmapMatrix;


	void		SetBounds(int xmin, int ymin, int xmax, int ymax);
	void		FillShapeHeader(std::list<FObj*> *objList, FDTDefineShape3* shapeTag);
};
#endif
