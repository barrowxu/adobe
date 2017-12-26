// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 09/08/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FExampleFont.cpp

	 Demonstrates the three-step creation process involved in displaying text.
	 Also demonstreates color transforms and transformation matricies
 
     Creates a one frame font movie with:
   
	 1) a black background, and
	 2) a text string "bob" in red.


****************************************************************************************/


#include "F3SDK.h"

void CreateFontMovie(){

	//define colors
	const FColor black(0,0,0);
	const FColor redA(0xff, 0, 0, 0xff);
	// const float pi = 3.141592;
	
	// object to which flash control and definition objects are added
	//creates movie at the procedure's end
	FObjCollection flashObjects;

	//create a new set-background color object and add it to the object collection
	flashObjects.AddFObj(new FCTSetBackgroundColor( new FColor( black ) ) );

	// create flash object that defines the font appearance
	FDTDefineFont* arial_b_o = new FDTDefineFont();
	
	//record this objects character ID for use later
	U16 arial_b_oID = arial_b_o->ID();
	
	//create shape of letter "b"
	FShape* letter_b = new FShape();
//  	letter_b->AddShapeRec( new FShapeRecChange(false, false, true, false, true, 0, 0, 0, 1, 0, 0, 0));
// 	letter_b->AddShapeRec( new FShapeRecEdgeStraight( 0, 600 ) );
// 	letter_b->AddShapeRec( new FShapeRecEdgeStraight( 600, 0 ) );
// 	letter_b->AddShapeRec( new FShapeRecEdgeStraight( 0, -600 ) );
// 	letter_b->AddShapeRec( new FShapeRecEdgeStraight( -600, 0 ) );

	letter_b->AddShapeRec( new FShapeRecChange(false, false, true, false, true, 157, -733, 0, 1, 0, 0, 0));
	letter_b->AddShapeRec( new FShapeRecEdgeStraight( 0, 262 ) );
	letter_b->AddShapeRec( new FShapeRecEdgeCurved( 57, -72, 89, 0 ) );
	letter_b->AddShapeRec( new FShapeRecEdgeCurved( 49, 0, 44, 20 ) );
	letter_b->AddShapeRec( new FShapeRecEdgeCurved( 43, 20, 29, 36 ) );
	letter_b->AddShapeRec( new FShapeRecEdgeCurved( 28, 35, 16, 51 ) );
	letter_b->AddShapeRec( new FShapeRecEdgeCurved( 16, 50, 0, 58 ) );
	letter_b->AddShapeRec( new FShapeRecEdgeCurved( 0, 136, -68, 75 ) );
	letter_b->AddShapeRec( new FShapeRecEdgeCurved( -67, 74, -95, 0 ) );
	letter_b->AddShapeRec( new FShapeRecEdgeCurved( -94, 0, -53, -78 ) );
	letter_b->AddShapeRec( new FShapeRecEdgeStraight( 0, 66  ) );
	letter_b->AddShapeRec( new FShapeRecEdgeStraight( -84, 0 ) );
	letter_b->AddShapeRec( new FShapeRecEdgeStraight( 0, -733 ) );
	letter_b->AddShapeRec( new FShapeRecEdgeStraight( 90, 0 ) );
	letter_b->AddShapeRec( new FShapeRecChange(false, false, false, false, true, 150, -269, 0, 0, 0, 0, 0));
	letter_b->AddShapeRec( new FShapeRecEdgeCurved( 0,95,26,43 ) );
	letter_b->AddShapeRec( new FShapeRecEdgeCurved( 42,69,73,0 ) );
	letter_b->AddShapeRec( new FShapeRecEdgeCurved(59,0,43,-51 ) );
	letter_b->AddShapeRec( new FShapeRecEdgeCurved(43,-51,0,-102 ) );
	letter_b->AddShapeRec( new FShapeRecEdgeCurved(0,-104,-41,-49 ) );
	letter_b->AddShapeRec( new FShapeRecEdgeCurved(-42,-50,-58,0 ) );
	letter_b->AddShapeRec( new FShapeRecEdgeCurved(-59,0,-43,52 ) );
	letter_b->AddShapeRec( new FShapeRecEdgeCurved(-43,51,0,97 ) );
	letter_b->AddShapeRec( new FShapeRecEnd() );
	
	//add b to the font definition object
	arial_b_o->AddShapeGlyph(letter_b);
	
	//create shape of letter "o"
	FShape* letter_o = new FShape();
	letter_o->AddShapeRec( new FShapeRecChange(false, true, true, false, true, 127, -265, 0, 1, 0, 0, 0) );
	letter_o->AddShapeRec( new FShapeRecEdgeCurved(0,102,44,51) );
	letter_o->AddShapeRec( new FShapeRecEdgeCurved(45,50,67,0) );
	letter_o->AddShapeRec( new FShapeRecEdgeCurved(67,0,45,-51) );
	letter_o->AddShapeRec( new FShapeRecEdgeCurved(44,-51,0,-104) );
	letter_o->AddShapeRec( new FShapeRecEdgeCurved(0,-99,-44,-50) );
	letter_o->AddShapeRec( new FShapeRecEdgeCurved(-45,-51,-67,0) );
	letter_o->AddShapeRec( new FShapeRecEdgeCurved(-67,0,-45,50) );
		letter_o->AddShapeRec( new FShapeRecEdgeCurved(-44,51,0,102) );
	letter_o->AddShapeRec( new FShapeRecChange(false, false, false, false, true, 116, -484, 0, 0, 0, 0, 0));
	letter_o->AddShapeRec( new FShapeRecEdgeCurved(69,-59,98,0) );
	letter_o->AddShapeRec( new FShapeRecEdgeCurved(110,0,69,72) );
	letter_o->AddShapeRec( new FShapeRecEdgeCurved(70,72,0,126) );
	letter_o->AddShapeRec( new FShapeRecEdgeCurved(0,103,-31,59) );
	letter_o->AddShapeRec( new FShapeRecEdgeCurved(-31,58,-58,33) );
	letter_o->AddShapeRec( new FShapeRecEdgeCurved(-59,32,-70,0) );
	letter_o->AddShapeRec( new FShapeRecEdgeCurved(-111,0,-69,-71) );
	letter_o->AddShapeRec( new FShapeRecEdgeCurved(-69,-72,0,-134) );
	letter_o->AddShapeRec( new FShapeRecEdgeCurved(0,-148,82,-71) );
	letter_o->AddShapeRec( new FShapeRecEnd() );
	
	//add o to the font definition object
	arial_b_o->AddShapeGlyph(letter_o);

	//add to object container
	flashObjects.AddFObj(arial_b_o);

	
	// create a second definition object which provides a mapping from the previous object's letter shapes to a TTF or ATM font
	FDTDefineFontInfo* arial_b_o_Info;
	arial_b_o_Info = new FDTDefineFontInfo("Arial", arial_b_oID, FDT::ShiftJIS, false, false);

	// codes added in an order correspending to addition of shapes above, a corresponding order provides the mapping
	arial_b_o_Info->AddCode(98);
	arial_b_o_Info->AddCode(111);

	// add object to collection
	flashObjects.AddFObj(arial_b_o_Info);
	

	
	
	// create tag that defines the text
	FDTDefineText2* b_o_b = new FDTDefineText2( new FRect(0, 0, 2000, 2000), //new FRect(94, 273, 3303, 1321),
												new FMatrix(),
												arial_b_o->NumberOfGlyphs() );
	
	

	// create a record that provides text appearance and format information
	// add it to text definition object
	b_o_b->AddTextRecord( new FTextChangeRecord(true, true, false, false,
											   arial_b_oID,
											   1440,
											   new FColor( redA ),
											   0, 
										       1304 )  );

	
	// create record that includes a list of which shapes to display and in what order
	FTextGlyphRecord* textGlyphRec = new FTextGlyphRecord();
	
	// list describing text sequence created and added
	textGlyphRec->AddGlyphEntry( 0, 800 ); // 0 is the b in the font we just defined
	textGlyphRec->AddGlyphEntry( 1, 800 ); // 1 is the o
	textGlyphRec->AddGlyphEntry( 0, 800 ); // and 0 is the b again
	b_o_b->AddTextRecord( textGlyphRec );

	//record this text's Id for reference later	
	U16 bobID = b_o_b->ID();
	
	//add this object to collection
	flashObjects.AddFObj(b_o_b);

	
	
	FMatrix* textTransform;
	
	
	// make a matrix that moves an object to a position located at (50,50)
	textTransform = new FMatrix(false, 0, 0, false, 0, 0, 1000, 1000);
	
	// make a palce object definition tag with transforming matrix we just addded
	// add it to object collection
	flashObjects.AddFObj( new FCTPlaceObject2(false, // ~ _hasClipDepth
											  true, 
											  true, 
											  false, 
											  1, 
											  bobID, textTransform, 
											  0, 0, 0, 0/**/) );
	//add showframe object to collection
	flashObjects.AddFObj(new FCTShowFrame() ); 

	//create movie, but use overloaded call that takes frame size and a frame rate (need to slow down motion of font its too fast)
	flashObjects.CreateMovie("FExampleFont.swf", 11000, 8000, 12);

}
