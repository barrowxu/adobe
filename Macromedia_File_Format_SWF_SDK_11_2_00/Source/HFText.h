// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 10/27/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFText.h

	This header-file contains the declarations of high-level text and edit-text class.
	Parent class is in the parentheses:

		class HFText; (public HFShape)
		class HFEditText : (public HFShape);
		
****************************************************************************************/

#ifndef HFTEXT_INCLUDED
#define HFTEXT_INCLUDED

#include "HFObject.h"
#include "FPrimitive.h"

class HFFont;


//! Define a text object.
/*!	
	\sa HFShape, HFObject
*/
class HFText : public HFShape
{
  public:
	  	//! Creates a EditText.
	/*!	
		\param text The initial text in the text field.
		\param font The font used by the text.	
		\sa HFShape
	*/
	HFText( const char* text, HFFont* font );

	// Method for internal use.
	virtual void AddToObjectList(std::list<FObj*> *objList, HFMovie* movie);

  private:
	void CalculateAndSetBounds();

	std::string	text;
	HFFont*		font;
};


//! Define a Text Field.
/*!	
	\sa HFShape, HFObject
*/
class HFEditText : public HFShape
{
  public:
  	//! Creates a EditText.
	/*!	You need the [x,y] of upper-left and bottom-right corners to build a rectangle.
		\param xmin The x coordinate of the upper left corner of the bounding rectangle.
		\param ymin The y coordinate of the upper left corner of the bounding rectangle.
		\param xmax The x coordinate of the bottom right corner of the bounding rectangle.
		\param ymax The y coordinate of the bottom right corner of the bounding rectangle.	
		\param text The initial text in the text field.	
		\sa HFShape
	*/
	HFEditText( int xmin, int ymin, int xmax, int ymax, const char* text );

				
 	//! Set the text color.
	/*!
		\param _textColor	The desired text color.
	*/
	void SetTextColor( const FColor& _textColor );
	

	//! Set the initial text in the text field.
	/*!
		\param text The desired text to be shown.
	*/
	void SetText( const char* text );
	

	//! Determine if the text field is editable.
	/*!
		\param edit	True for editable, false for non-editable.
	*/
	void SetEditable( bool edit );
	

	//! Set the height of the text field.
	/*
		\param	heightInTwips	height of the text field in twips.
	*/
	void SetHeight( int heightInTwips );


	//! Set the height of the text field.
	/*
		\param	wrap	True for has-word-wrap, false for no-word-wrap.
	*/
	void SetWordWrap( bool wrap )			{ wordWrap = wrap; }


	// Method for internal use.
	virtual void AddToObjectList(std::list<FObj*> *objList, HFMovie* movie);

  private:
	FColor*		textColor;
	FString*	text;
// 	FRect*		bounds;

	bool canEdit;
	int	 height;
	int	 textid;
	bool wordWrap;
};

#endif


