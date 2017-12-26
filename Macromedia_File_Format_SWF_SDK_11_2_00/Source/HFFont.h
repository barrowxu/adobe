// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 11/05/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFFont.h

	This header-file contains the declarations of high-level button class.
	Parent class is in the parentheses:

		class HFButton; (public HFObject)

****************************************************************************************/

#ifndef HFFONT_INCLUDED
#define HFFONT_INCLUDED

#include "HFObject.h"
#include "FPrimitive.h"
#include "HFPolygon.h"

class FDTDefineFont;


//! Define a font.
/*!	The HFFont is a child of HFObject class.
	\sa HFObject.
*/
class HFFont : public HFObject
{
  public:
// 	HFFont( void* dataDefineFont2, int size );

	//! Creates a font.
	/*!	
		\param name The name of the font.
		\sa HFObject
	*/
	HFFont( const char* name );


	//! Add a glyph to the font.
	/*!	A font is built from other shapes. (Normally polygons.) The polygons should be built inside
		a 1024x1024 box, with their origin at 0,0. <br>
		The AddGlypth method takes a shape (for example, one that looks like the letter A) and adds 
		it to the font set with a unicode value and an advance.
		\param shape	The polygon defining the glyph to be added.
		\param code		The unicode (or ascii, ect.) value associated with the font. (For example, the 
						code for a shape that looks like an A would be 65.)
		\param advance	The distance between the left of this letter, and the left edge of the next letter.
						If our letter a was about 500 twips wide, its advance might be 600 twips or so.
		\sa HFObject
	*/
	void AddGlyph( HFPolygon* shape, int code, int advance );


	//! Return how many glyphs in the font.
	/*!	
		\return			The number of glyphs in the font.
		\sa HFObject
	*/
	int  GlyphCount()				{ return glyphList.size(); }


	//! Gets a glyph code from an ascii/unicode value. Returns -1 if not in font.
	/*!	Normally, a user will never call this function.
	    The glyph code is the internal code for the font. It is an index, so the
		first letter you add will be internal code 0, even if it is ascii 65. 
		\param unicode	Unicode or ascii value.
		\return			The internal code.
	*/
	int  GetGlyphCodeFromAscii( int unicode );	

	
	//! Returns the advance for a give glyph code.
	/*!	Normally, a user will never call this function.
		Given an internal code, returns the advance.
		\param  glyphCode	Internal glyph code. See GetGlyphCodeFromAscii.
		\return				Advance value.
		\sa HFObject
	*/
	int  GetAdvance( int glyphCode );
	
	// Method for internal use.
	virtual void AddToObjectList( std::list<FObj*> *objList, HFMovie* movie );

  private:
	struct Glyph
	{
		FShape*	shape;	// pointer to the FShape data of the polygon.
		int		unicode;
		int		advance;
	};
	std::list<Glyph>	glyphList;
	int					indexBits;
	FDTDefineFont*		font;
	std::string			fontName;
};


#endif