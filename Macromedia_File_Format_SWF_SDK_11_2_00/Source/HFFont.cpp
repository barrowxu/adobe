// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 11/05/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFFont.cpp

  This source file contains the definition for high-level font functions,

		Class						Member Function
	
	HFFont						HFFont(const char*);
								void AddGlyph(HFPolygon*, int, int);
								void AddToObjectList(std::list<FObj*>*);
								int GetGlyphCodeFromAscii(int);
								int GetAdvance(int);

****************************************************************************************/

#pragma warning( disable : 4786 )
#include "HFFont.h"
#include "FDTFonts.h"

// void HFFont::AddToFrame( std::list<FObj*> *objList)
// {
// 	// This is a testing hack.
// 	FFragment* fragment = new FFragment( fontData, fontDataSize );	
// 	objList->push_back( fragment );
// }

//////////////////////////////////////////////////////////////////////////////////////
//  --------  HFFont  ----------------------------------------------------------------

HFFont::HFFont( const char* name )
{
	// Create the font tag.
	font = new FDTDefineFont();
	SetDefineTagId( font->ID() );

	fontName = name;
}

void HFFont::AddGlyph( HFPolygon* poly, int unicode, int advance )
{
	Glyph glyph;

	glyph.shape = poly->CreateFShape();
	glyph.unicode = unicode;
	glyph.advance = advance;

	glyphList.push_back( glyph );

// 	delete poly;
}

void HFFont::AddToObjectList( std::list<FObj*> *objList, HFMovie* movie )
{
	// if we are already added, do nothing
	if ( !defineWritten )
	{
		std::list<Glyph>::iterator it;

		// Add the letters to the font
		for ( it = glyphList.begin(); it != glyphList.end(); ++it )
		{
			font->AddShapeGlyph( it->shape );
			it->shape = 0;
		}
		
	// 	indexBits = font->nIndexBits();
		objList->push_back( font );

		// Now that we have a font, we need a defineFontInfo to establish the ascii
		// to font code connection.
	// 	FDTDefineFontInfo* info = new FDTDefineFontInfo(	fontName.c_str(),
	// 														font->ID(),
	// 														ShiftJIS, //ANSI,
	// 														false,
	// 														false
	// 												   );
	// 	for ( it = glyphList.begin(); it != glyphList.end(); ++it )
	// 	{
	// 		info->AddCode( it->code );
	// 	}
	// 
	// 	objList->push_back( info );
		defineWritten = true;
	}
}


int HFFont::GetGlyphCodeFromAscii( int unicode )
{
	int code = 0;
	std::list<Glyph>::iterator it;

	for ( it = glyphList.begin(); it != glyphList.end(); ++it, ++code )
	{
		if ( it->unicode == unicode )
		{
			FLASHASSERT( code < glyphList.size() );
			FLASHASSERT( code >= 0 );
			return code;
		}
	}
	return -1;
}


int HFFont::GetAdvance( int glyphCode )
{
	FLASHASSERT( glyphCode >= 0 );
	FLASHASSERT( glyphCode < glyphList.size() );

	std::list<Glyph>::iterator it;

	for ( it = glyphList.begin(); it != glyphList.end() && glyphCode; ++it, --glyphCode )
	{
		// nothing
	}
	return it->advance;
}
