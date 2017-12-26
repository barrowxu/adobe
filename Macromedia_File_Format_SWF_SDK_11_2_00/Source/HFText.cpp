// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 10/27/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFText.cpp

  This source file contains the definition for high-level Text and EditText functions,

		Class						Member Function

	HFText						HFText(const char* , HFFont*); 
								void AddToObjectList(std::list<FObj*>*);
								void CalculateAndSetBounds();

	HFEditText					HFEditText(int, int, int, int, const char*);
								void SetTextColor(const FColor&);
								void SetText(const char*);
								void SetEditable(bool);
								void SetHeight(int);
								void AddToObjectList(std::list<FObj*>*);

****************************************************************************************/

#include "HFShape.h"
#include "HFText.h"
#include "HFFont.h"
#include "FDTFonts.h"
#include "FDTText.h"

//////////////////////////////////////////////////////////////////////////////////////
//  --------  HFSound  ---------------------------------------------------------------
HFText::HFText( const char* _text, HFFont* _font ) 
	: HFShape( 0, 0, 0, 0 )
{
	text = _text;
	font = _font;
	CalculateAndSetBounds();
}


void HFText::AddToObjectList(std::list<FObj*> *objList, HFMovie* movie)
{
	const int fontHeight = 1024;

	// Add the font to the frame - if it is defined, will do nothing.
	font->AddToObjectList( objList, movie );

	// make sure we define only once.
	if ( !defineWritten )
	{
		// create tag that defines the text
		FDTDefineText2* defineText = new FDTDefineText2(	new FRect( bounds ),
															new FMatrix(),
															font->GlyphCount() );

		SetDefineTagId( defineText->ID() );

		// create a record that provides text appearance and format information
		// add it to text definition object
		defineText->AddTextRecord( new FTextChangeRecord(true, true, false, false,
									font->DefineTagId(),
									fontHeight,
									new FColor( solidFillColor ),
									0, 
									0   )  );

		
		// create record that includes a list of which shapes to display and in what order
		FTextGlyphRecord* textGlyphRec = new FTextGlyphRecord();
		
		// list describing text sequence created and added
		for ( int i = 0; i<text.size(); i++ )
		{
			// Find the character in the font;
			char c = text[i];

			int code = font->GetGlyphCodeFromAscii( c );

			if ( code >= 0 )
			{
				textGlyphRec->AddGlyphEntry( code, font->GetAdvance( code ) );
			}
		}
		defineText->AddTextRecord( textGlyphRec );

		//add this object to collection
		objList->push_back( defineText );

		defineWritten = true;
	}
	AddPlaceObject2( objList, movie );
}


void HFText::CalculateAndSetBounds()
{
	// Go through each letter - assume a 1024*1024 bound, and build a 
	// total bounding box.

	int width = 0;
	int x = 0;
	int y = 0;

	// list describing text sequence created and added
	for ( int i = 0; i<text.size(); i++ )
	{
		// Find the character in the font;
		char c = text[i];

		int code = font->GetGlyphCodeFromAscii( c );

		if ( code >= 0 )
		{
			width += font->GetAdvance( code );
		}
	}	
	// Now that we have the width, add the font width to the last character:
// 	width += 1024;

	SetBounds( x, y, x + width, y + 1024 );
}


//////////////////////////////////////////////////////////////////////////////////////
//  --------  HFEditText  ------------------------------------------------------------

HFEditText::HFEditText( int xmin, int ymin, int xmax, int ymax, const char* _text )
	: HFShape( xmin, ymin, xmax, ymax )
{
	textColor	= new FColor( 0, 0, 0, 255 );			// default text color: black, completely opaque
	text		= new FString( (U8*)_text );
	canEdit		= true;									// default: editable
    height		= 240;									// default height in twips: 240
	wordWrap	= false;
}

void HFEditText::SetTextColor( const FColor& _textColor )
{
	delete textColor;
	textColor	= new FColor( _textColor );
}


void HFEditText::SetText( const char* _text )
{
	delete text;
	text		= new FString( (U8*)_text );
}


void HFEditText::SetEditable( bool edit )
{
	canEdit = edit;
}


void HFEditText::SetHeight( int heightInTwips )
{
	height = heightInTwips;
}


void HFEditText::AddToObjectList(std::list<FObj*> *objList, HFMovie* movie )
{
	// Edit text always write a new define text object.
	char buffer[64];

	// Bounds and depth are a unique id - this could be handled better.  FIXME
	sprintf( buffer, "TextField_%ld_%ld_%ld_%ld_%d", bounds.Xmin(), bounds.Ymin(), bounds.Xmax(), bounds.Ymax(), depth );

	FString* variable = new FString( (U8*)buffer );

	FDTDefineEditText* textField = new FDTDefineEditText(	new FRect( bounds ),
															false,		// _hasFont
															false,		// _hasMaxLength
															true,		// _hasTextColor
															!canEdit,	// _readOnly
															false,		// _password
															false,		// _multiline
															wordWrap,	// _wordWrap
															true,		// _hasText
															false,		// _useOutlines
															true,		// _border
															false,		// _noSelect
															true,		// _hasLayout
															0,			// _fontID
															height,		// _fontHeight
															textColor,	// _textColor
															0,	        // _maxLength
															0,			// _alignment
															0,			// _leftMargin
															0,			// _rightMargin
															0,			// _indent
															40,			// _leading
															variable,	// _variableName
															text );		// _initialText



	textColor = 0;
	text = 0;

	SetDefineTagId( textField->ID() );

	objList->push_back( textField );

	AddPlaceObject2( objList, movie );
}




