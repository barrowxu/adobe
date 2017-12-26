// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By David Michie.
// First Created On 11/04/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FExampleClip.cpp

   Creates a one-frame clip movie with shapes in different depth:

	1) Depth 4: Red Circle
	2) Depth 3: Blue Rectangle
	3) Depth 2: Green Triangle
	4) Depth 1: Black Ellipse with ClipDepth = 3.

****************************************************************************************/

#include "F3SDK.h"
#include "FExample.h"

//Creates a one frame rectangle movie with a red fill color, a standard 1 pixel wide, 
//black line style, and the given coordinates

void CreateClipMovie()
{

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

///////////////////////////////////////////////////////////////////////////////
	
	//construct a clipRect that defines the shape's bounds 
	FRect* clipRectBounds = new FRect(500, 500, 4500, 4500);  //coordinate values are in TWIPS

	//construct the FDTDefineShape which will be the clipRectangle image
	FDTDefineShape* clipRectangle = new FDTDefineShape(clipRectBounds);

	//record its ID so that we can later refer to it
	U16 clipRectangleID = clipRectangle->ID();

	//construct a black color
	FColor black = FColor(0, 0, 0);
	
	//construct a solid fill style of the given color
	//add the fill style to the clipRectangle
	//you must record the position of the fill style in the fill style array 
	//so that you can later refer to it.  The AddFillStyle function of fillStyle 
	//array returns the position so record that in a field called fillID
	U32 blackfillID = clipRectangle->AddSolidFillStyle( new FColor(black) );
	
	/***
	//add a black, 1 pixel (20 TWIPS) wide line style to clipRectangle, remembering to store the
	// position of the line style just as in the fill style.
	U32 blackLineStyleID = clipRectangle->AddLineStyle(20, new FColor( black ) );
	***/

	//Since you are done creating fill and line styles, indicate so
	clipRectangle->FinishStyleArrays();

	//construct the shape records which will describe the clipRectangle
	//there are FShapeRecChange, FShapeRecEdge, and FShapeRecEnd shapes
	FShapeRec* clipRectangleShapeRecords[6];
	clipRectangleShapeRecords[0] = new FShapeRecChange(false, true, true, false, true, 4500, 500, 0, 
												   blackfillID, 0, 0, 0);
	//Create straight edge object (just a stuct of info), store it in EdgeRecord
	clipRectangleShapeRecords[1] = new FShapeRecEdgeStraight( 0, 4000);
	clipRectangleShapeRecords[2] = new FShapeRecEdgeStraight( -4000, 0);
	clipRectangleShapeRecords[3] = new FShapeRecEdgeStraight( 0, -4000);
	clipRectangleShapeRecords[4] = new FShapeRecEdgeStraight( 4000, 0);
	clipRectangleShapeRecords[5] = new FShapeRecEnd();

	
	//Add the shape records to the clipRectangle shape object
	int i;
	for (i = 0;  i < 6 ;  i++)
		clipRectangle->AddShapeRec(clipRectangleShapeRecords[i]);

	//Add the clipRectangle to the given object collection
	allTags.AddFObj(clipRectangle);

	//create a place object tag which puts the clipRectangle on the display list
	FCTPlaceObject2 *placeClipRectangle = new FCTPlaceObject2(true, false, true, false, 
														  1, clipRectangleID, 0, 0, 0, 0, 3);

	//add the place object tag to the FObjCollection
	allTags.AddFObj(placeClipRectangle);
	
///////////////////////////////////////////////////////////////////////////////

	//Now start creating the rectangle object. You must:
	//Create the bounds rect
	//Create the Shape Record and remember its ID
	//Create the Color for the fill
	//Create the Fill
	//Add the fill to the shape
	//Create the color for the rectangle's line style
	//Create the lineStyle record
	//Create the Edge records that define the rectangle and add them to the shape

	//construct a rect that defines the shape's bounds 
	FRect* rectBounds = new FRect(1000, 1000, 5000, 5000);  //coordinate values are in TWIPS

	//construct the FDTDefineShape which will be the rectangle image
	FDTDefineShape* rectangle = new FDTDefineShape(rectBounds);

	//record its ID so that we can later refer to it
	U16 rectangleID = rectangle->ID();

	//construct a red FColor
	FColor red = FColor(0xff, 0, 0);
	
	//construct a solid fill style of the given color
	//add the fill style to the rectangle
	//you must record the position of the fill style in the fill style array 
	//so that you can later refer to it.  The AddFillStyle function of fillStyle 
	//array returns the position so record that in a field called fillID
	U32 redfillID = rectangle->AddSolidFillStyle( new FColor(red) );
	
	//add a black, 10 pixel (200 TWIPS) wide line style to rectangle, remembering to store the
	// position of the line style just as in the fill style.
	U32 blackLineStyleID = rectangle->AddLineStyle(200, new FColor( black ) );

	//Since you are done creating fill and line styles, indicate so
	rectangle->FinishStyleArrays();

	//construct the shape records which will describe the rectangle
	//there are FShapeRecChange, FShapeRecEdge, and FShapeRecEnd shapes
	FShapeRec* rectangleShapeRecords[6];
	rectangleShapeRecords[0] = new FShapeRecChange(false, true, true, false, true, 5000, 1000, 0, 
												   redfillID, blackLineStyleID, 0, 0);
	//Create straight edge object (just a stuct of info), store it in EdgeRecord
	rectangleShapeRecords[1] = new FShapeRecEdgeStraight( 0, 4000);
	rectangleShapeRecords[2] = new FShapeRecEdgeStraight( -4000, 0);
	rectangleShapeRecords[3] = new FShapeRecEdgeStraight( 0, -4000);
	rectangleShapeRecords[4] = new FShapeRecEdgeStraight( 4000, 0);
	rectangleShapeRecords[5] = new FShapeRecEnd();

	
	//Add the shape records to the rectangle shape object
	for (i = 0;  i < 6 ;  i++)
		rectangle->AddShapeRec(rectangleShapeRecords[i]);

	//Add the rectangle to the given object collection
	allTags.AddFObj(rectangle);

	//create a place object tag which puts the rectangle on the display list
	FCTPlaceObject2 *placeRectangle = new FCTPlaceObject2(false, false, true, false, 
														  2, rectangleID, 0, 0, 0, 0, 0);

	//add the place object tag to the FObjCollection
	allTags.AddFObj(placeRectangle);

//////////////////////////////////////////////////////////////////////////////////////

	//construct a rect that defines the shape's bounds 
	rectBounds = new FRect(0, 0, 2006, 2005);  //coordinate values are in TWIPS

	//construct the FDTDefineShape which will be the circle image
	FDTDefineShape* circle = new FDTDefineShape(rectBounds);

	//record its ID so that we can later refer to it
	U16 circleID = circle->ID();

	//construct a blue FColor
	FColor blue = FColor(0, 0, 0xff);
	
	//construct a solid fill style of the given color
	//add the fill style to the circle
	//you must record the position of the fill style in the fill style array 
	//so that you can later refer to it.  The AddFillStyle function of fillStyle 
	//array returns the position so record that in a field called fillID
	U32 blueFillID = circle->AddSolidFillStyle( new FColor( blue ) );
	
	//add a black, 4 pixel (80 TWIPS) wide line style to circle, remembering to store the
	// position of the line style just as in the fill style.
	blackLineStyleID = circle->AddLineStyle(80, new FColor( black ) );

	//Since you are done creating fill and line styles, indicate so
	circle->FinishStyleArrays();

	//construct the shape records which will describe the circle
	//there are FShapeRecChange, FShapeRecEdge, and FShapeRecEnd shapes
	FShapeRec* circleShapeRecords[10];
	circleShapeRecords[0] = new FShapeRecChange(false, true, true, false, true, 1703, 1702, 0, 
												   blueFillID, blackLineStyleID, 0, 0);
	//Create straight edge object (just a struct of info), store it in EdgeRecord
	circleShapeRecords[1] = new FShapeRecEdgeCurved( -292, 293, -413, 0);
	circleShapeRecords[2] = new FShapeRecEdgeCurved( -413, 0, -293, -293);
	circleShapeRecords[3] = new FShapeRecEdgeCurved( -292, -292, 0, -413);
	circleShapeRecords[4] = new FShapeRecEdgeCurved( 0, -413, 292, -293);
	circleShapeRecords[5] = new FShapeRecEdgeCurved( 293, -292, 413, 0);
	circleShapeRecords[6] = new FShapeRecEdgeCurved( 413, 0, 292, 292);
	circleShapeRecords[7] = new FShapeRecEdgeCurved( 293, 293, 0, 413);
	circleShapeRecords[8] = new FShapeRecEdgeCurved( 0, 413, -293, 292);
	circleShapeRecords[9] = new FShapeRecEnd();

	
	//Add the shape records to the circle shape object
	for (i = 0;  i < 10 ;  i++)
		circle->AddShapeRec(circleShapeRecords[i]);

	//Add the circle to the given object collection
	allTags.AddFObj(circle);

	//create a place object tag which puts the circle on the display list
	FCTPlaceObject2 *placeCircle = new FCTPlaceObject2(false, false, true, false, 
														  3, circleID, 0, 0, 0, 0, 0);

	//add the place object tag to the FObjCollection
	allTags.AddFObj(placeCircle);

	
///////////////////////////////////////////////////////////////////////////////////////

	//construct a rect that defines the shape's bounds 
	rectBounds = new FRect(3000, 3000, 7000, 7000);  //coordinate values are in TWIPS

	//construct the FDTDefineShape which will be the rectangle image
	FDTDefineShape* rectangle2 = new FDTDefineShape(rectBounds);

	//record its ID so that we can later refer to it
	U16 rectangle2ID = rectangle2->ID();

	//construct a red FColor
	FColor green = FColor(0, 0xff, 0);
	
	//construct a solid fill style of the given color
	//add the fill style to the rectangle
	//you must record the position of the fill style in the fill style array 
	//so that you can later refer to it.  The AddFillStyle function of fillStyle 
	//array returns the position so record that in a field called fillID
	U32 greenfillID = rectangle2->AddSolidFillStyle(new FColor(green));
	
	//add a black, 10 pixel (200 TWIPS) wide line style to rectangle2, remembering to store the
	// position of the line style just as in the fill style.
	blackLineStyleID = rectangle2->AddLineStyle(200, new FColor( black ) );

	//Since you are done creating fill and line styles, indicate so
	rectangle2->FinishStyleArrays();

	//construct the shape records which will describe the rectangle
	//there are FShapeRecChange, FShapeRecEdge, and FShapeRecEnd shapes
	FShapeRec* rectangle2ShapeRecords[6];
	rectangle2ShapeRecords[0] = new FShapeRecChange(false, true, true, false, true, 7000, 3000, 0, 
												   greenfillID, blackLineStyleID, 0, 0);
	//Create straight edge object (just a stuct of info), store it in EdgeRecord
	rectangle2ShapeRecords[1] = new FShapeRecEdgeStraight( 0, 4000);
	rectangle2ShapeRecords[2] = new FShapeRecEdgeStraight( -4000, 0);
	rectangle2ShapeRecords[3] = new FShapeRecEdgeStraight( 0, -4000);
	rectangle2ShapeRecords[4] = new FShapeRecEdgeStraight( 4000, 0);
	rectangle2ShapeRecords[5] = new FShapeRecEnd();

	
	//Add the shape records to the rectangle shape object
	for (i = 0;  i < 6 ;  i++)
		rectangle2->AddShapeRec(rectangle2ShapeRecords[i]);

	//Add the rectangle to the given object collection
	allTags.AddFObj(rectangle2);

	//create a place object tag which puts the rectangle on the display list
	FCTPlaceObject2 *placeRectangle2 = new FCTPlaceObject2(false, false, true, false, 
														  4, rectangle2ID, 0, 0, 0, 0, 0);

	//add the place object tag to the FObjCollection
	allTags.AddFObj(placeRectangle2);

/////////////////////////////////////////////////////////////////////////////////////////

	//construct a show frame object
	FCTShowFrame *showFrame = new FCTShowFrame();

	//add the show frame object to the FObj collection;
	allTags.AddFObj(showFrame);

	//now create the movie
	allTags.CreateMovie("FExampleClip.swf", 11000, 8000, 12);
}