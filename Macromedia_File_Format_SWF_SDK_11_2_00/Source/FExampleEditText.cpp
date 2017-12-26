// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu
// First Created On 10/26/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FExampleEditText.cpp

   Creates a one Edit Text frame movie with:
   
	1) a square text field, which is in single line mode and contains string "start"
	   initially.
	
****************************************************************************************/

#include "F3SDK.h"
#include "FExample.h"

void CreateTextFieldMovie()
{
	//Create a collection of FObj's, allTags, to contain the FObjs that make the movie
	//Each SWF tag in the movie will be represented by an FObj
	FObjCollection allTags;

// Construct first flash tag object (set background color):

	//define a color for the background
	const FColor white(0xff, 0xff, 0xff);

	//construct the SetBackgroundColor object which takes a color as an argument
	//All routines beginning with FCT create Flash Control Tags
	FCTSetBackgroundColor* background = new FCTSetBackgroundColor( new FColor( white ) );

	//add the SetBackgroundColor tag to allTags
	allTags.AddFObj(background);


    
 	char* fontname = "Times New Roman";
 	
    FDTDefineFont2* font = new FDTDefineFont2(	fontname,
 												FDT::ANSI,
 												false, 
 												false);
 
 	allTags.AddFObj(font);
    
	// Construct the bounding square.
	FRect* rectBounds	= new FRect(1000, 1000, 2000, 2000);
	// Construct black color for text.
	FColor* black		= new FColor( 0, 0, 0, 255 );
	// Variable name for text field.
	FString* var_name	= new FString( (U8*)"TextField1" );
	// Initial text string int the text field. 
	FString* init		= new FString( (U8*)"start" );
	
	// Construct a EditText SWF tag.
	FDTDefineEditText* textField = new FDTDefineEditText(	rectBounds,	
															true,		// _hasFont
															false,		// _hasMaxLength
															true,		// _hasTextColor
															false,		// _readOnly
															false,		// _password
															false,		// _multiline
															false,		// _wordWrap
															true,		// _hasText
															false,		// _useOutlines
															true,		// _border
															false,		// _noSelect
															true,		// _hasLayout
															1,			// _fontID
															240,		// _fontHeight
															black,		// _textColor
															0,		// _maxLength
															0,			// _alignment
															0,			// _leftMargin
															0,			// _rightMargin
															0,			// _indent
															40,			// _leading
															var_name,	// _variableName
															init);		// _initialText
	U16 textFieldID = textField->ID();			// remember this tag's ID.
	allTags.AddFObj(textField);					// Add the text field to the moive's character list.

	// Now place the text field onto the frame.
	FCTPlaceObject2 *placeTextField = new FCTPlaceObject2(false, // ~ _hasClipDepth
		false, true, false, 1, textFieldID, 0, 0, 0, 0, 0/**/);
	allTags.AddFObj(placeTextField);
	
	// Show frame in the movie.
	FCTShowFrame *showFrame = new FCTShowFrame();
	allTags.AddFObj(showFrame);

	// Create the SWF file with 550x400 stage and frame rate 12 fps.
	allTags.CreateMovie("FExampleEditText.swf", 11000, 8000, 12);
}
