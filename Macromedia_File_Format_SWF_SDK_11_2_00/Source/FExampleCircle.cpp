// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu
// First Created On 10/07/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FExampleCircle.cpp

   Creates a one frame movie containing a circle with:
   
	1) blue solid fill color,
	2) a standard 1 pixel wide, black line.

****************************************************************************************/

#include "F3SDK.h"
#include "FExample.h" 

void CreateCircleMovie(){

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


//Now start creating the circle object. You must:
	//Create the bounds rect
	//Create the Shape Record and remember its ID
	//Create the Color for the fill
	//Create the Fill
	//Add the fill to the shape
	//Create the color for the circle's line style
	//Create the lineStyle record
	//Create the Edge records that define the circle and add them to the shape

	//construct a rect that defines the shape's bounds 
	FRect* rectBounds = new FRect(0, 0, 2006, 2005);  //coordinate values are in TWIPS

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
	U32 blueFillID = circle->AddSolidFillStyle(new FColor( blue ) );
	
	//construct a black color
	FColor black = FColor(0, 0, 0);

	//add a black, 1 pixel (20 TWIPS) wide line style to circle, remembering to store the
	// position of the line style just as in the fill style.
	U32 blackLineStyleID = circle->AddLineStyle(20, new FColor( black ) );

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
	for (int i = 0;  i < 10 ;  i++)
		circle->AddShapeRec(circleShapeRecords[i]);

	//Add the circle to the given object collection
	allTags.AddFObj(circle);

	//create a place object tag which puts the circle on the display list
	FCTPlaceObject2 *placeCircle = new FCTPlaceObject2( false, // ~ _hasClipDepth
														false, true, false, 
														1, circleID, 0, 0, 0, 0, 0/**/);

	//add the place object tag to the FObjCollection
	allTags.AddFObj(placeCircle);

	//construct a show frame object
	FCTShowFrame *showFrame = new FCTShowFrame();

	//add the show frame object to the FObj collection;
	allTags.AddFObj(showFrame);

	//now create the movie
	allTags.CreateMovie("FExampleCircle.swf", 11000, 8000, 12);

}