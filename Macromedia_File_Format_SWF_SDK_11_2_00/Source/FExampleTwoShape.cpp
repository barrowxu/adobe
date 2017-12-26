// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/14/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FExampleTwoShape.cpp

   Creates a one frame movie with:
   
	 1) two rectangles each in a separate defineShape record, 
	 2) bottom one uses red fill color, 
	 3) top one uses blue fill color,
	 4) both use a standard 1 pixel wide, black line style.
	 
	Results are: the first object put on a certain depth level is on top, 
	later added object on the same level gets blocked by the previous object
	if they overlap somewhat.
 

****************************************************************************************/

#include "F3SDK.h"
#include "FExample.h"

void CreateTwoShapes(){

	//Create a collection of FObj's, allTags, to contain the FObjs that make the movie
	//Each SWF tag in the movie will be represented by an FObj
	FObjCollection allTags;

// Construct first flash tag object (set background color):
	//define a color for the background
	const FColor white(0xff, 0xff, 0xff);

	//construct the SetBackgroundColor object which takes a color as an argument
	//All routines beginning with FCT create Flash Control Tags
	FCTSetBackgroundColor* background = new FCTSetBackgroundColor(new FColor( white));

	//add the SetBackgroundColor tag to allTags
	allTags.AddFObj(background);

//Now start creating the first rectangle object with red fill color. 
	//construct a rect that defines the shape's bounds 
	FRect* rectBounds1 = new FRect(0, 0, 2000, 2000);  //coordinate values are in TWIPS

	//construct the FDTDefineShape which will be the rectangle image
	FDTDefineShape* rectangle1 = new FDTDefineShape(rectBounds1);

	//record its ID so that we can later refer to it
	U16 rectangleID1 = rectangle1->ID();

	//construct a red FColor
	FColor red = FColor(0xff, 0, 0);
	
	//construct a solid fill style of the given color
	//add the fill style to the rectangle
	//you must record the position of the fill style in the fill style array 
	//so that you can later refer to it.  The AddFillStyle function of fillStyle 
	//array returns the position so record that in a field called fillID
	U32 redfillID = rectangle1->AddSolidFillStyle(new FColor( red));
	
	//construct a black color
	FColor black1 = FColor(0, 0, 0);

	//add a black, 1 pixel (20 TWIPS) wide line style to rectangle1, remembering to store the
	// position of the line style just as in the fill style.
	U32 blackLineStyleID1 = rectangle1->AddLineStyle(20, new FColor( black1 ) );

	//Since you are done creating fill and line styles, indicate so
	rectangle1->FinishStyleArrays();

	//construct the shape records which will describe the rectangle
	//there are FShapeRecChange, FShapeRecEdge, and FShapeRecEnd shapes
	FShapeRec* rectangleShapeRecords1[6];
	rectangleShapeRecords1[0] = new FShapeRecChange(false, true, true, false, true, 2000, 0, 0, 
												   redfillID, blackLineStyleID1, 0, 0);
	//Create straight edge object (just a stuct of info), store it in EdgeRecord
	rectangleShapeRecords1[1] = new FShapeRecEdgeStraight( 0, 2000);
	rectangleShapeRecords1[2] = new FShapeRecEdgeStraight( -2000, 0);
	rectangleShapeRecords1[3] = new FShapeRecEdgeStraight( 0, -2000);
	rectangleShapeRecords1[4] = new FShapeRecEdgeStraight( 2000, 0);
	rectangleShapeRecords1[5] = new FShapeRecEnd();

	
	//Add the shape records to the rectangle shape object
	for (int i = 0;  i < 6 ;  i++)
		rectangle1->AddShapeRec(rectangleShapeRecords1[i]);

	//Add the rectangle to the given object collection
	allTags.AddFObj(rectangle1);

	//create a place object tag which puts the rectangle on the display list
	FCTPlaceObject2 *placeRectangle1 = new FCTPlaceObject2(false, // ~ _hasClipDepth
														   false, true, false, 
														   1, rectangleID1, 0, 0, 0, 0, 0/**/);

	//add the place object tag to the FObjCollection
	allTags.AddFObj(placeRectangle1);



//Now start creating the second rectangle object with blue fill color. 
	
	//construct a rect that defines the shape's bounds 
	FRect* rectBounds2 = new FRect(1000, 1000, 3000, 3000);  

	//construct the FDTDefineShape which will be the rectangle image
	FDTDefineShape* rectangle2 = new FDTDefineShape(rectBounds2);

	//record its ID so that we can later refer to it
	U16 rectangleID2 = rectangle2->ID();

	//construct a blue FColor
	FColor blue = FColor(0, 0, 0xff);
	
	//construct a solid fill style of the given color
	//add the fill style to the rectangle
	//you must record the position of the fill style in the fill style array 
	//so that you can later refer to it.  The AddFillStyle function of fillStyle 
	//array returns the position so record that in a field called fillID
	U32 bluefillID = rectangle2->AddSolidFillStyle(new FColor( blue));
	
	//construct a black color
	FColor black2 = FColor(0, 0, 0);

	//add a black, 1 pixel (20 TWIPS) wide line style to rectangle2, remembering to store the
	// position of the line style just as in the fill style.
	U32 blackLineStyleID2 = rectangle2->AddLineStyle(20, new FColor( black2 ) );

	//Since you are done creating fill and line styles, indicate so
	rectangle2->FinishStyleArrays();

	//construct the shape records which will describe the rectangle
	//there are FShapeRecChange, FShapeRecEdge, and FShapeRecEnd shapes
	FShapeRec* rectangleShapeRecords2[6];
	rectangleShapeRecords2[0] = new FShapeRecChange(false, true, true, false, true, 3000, 1000, 0, 
												   bluefillID, blackLineStyleID2, 0, 0);
	//Create straight edge object (just a stuct of info), store it in EdgeRecord
	rectangleShapeRecords2[1] = new FShapeRecEdgeStraight( 0, 2000);
	rectangleShapeRecords2[2] = new FShapeRecEdgeStraight( -2000, 0);
	rectangleShapeRecords2[3] = new FShapeRecEdgeStraight( 0, -2000);
	rectangleShapeRecords2[4] = new FShapeRecEdgeStraight( 2000, 0);
	rectangleShapeRecords2[5] = new FShapeRecEnd();


	//Add the shape records to the rectangle shape object
	for (int k = 0;  k < 6 ;  k++)
		rectangle2->AddShapeRec(rectangleShapeRecords2[k]);

	//Add the rectangle to the given object collection
	allTags.AddFObj(rectangle2);

	//create a place object tag which puts the rectangle on the display list
	FCTPlaceObject2 *placeRectangle2 = new FCTPlaceObject2( false, // ~ _hasClipDepth
															false, true, false, 
														    1, rectangleID2, 0, 0, 0, 0, 0/**/);

//add the place object tag to the FObjCollection
	allTags.AddFObj(placeRectangle2);

	//construct a show frame object
	FCTShowFrame *showFrame = new FCTShowFrame();

	//add the show frame object to the FObj collection;
	allTags.AddFObj(showFrame);

	//now create the movie
	allTags.CreateMovie("FExampleTwoShape.swf", 11000, 8000, 12);

}