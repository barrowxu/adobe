// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/29/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FExampleOval.cpp

   Creates a one frame movie containing an oval with:
   
	1) blue solid fill color,
	2) a standard 1 pixel wide, black line.

****************************************************************************************/

#include "F3SDK.h"
#include "FExample.h"

//Creates a one frame oval movie with a blue fill color, a standard 1 pixel wide, 
//black line style.

void CreateOvalMovie(){
	
	//Create a collection of FObj's, allTags, to contain the FObjs that make the movie
	//Each SWF tag in the movie will be represented by an FObj
	FObjCollection allTags;

	//construct a rect that defines the shape's bounds 
	FRect* rectBounds = new FRect(0, 0, 4000, 2000);
	FDTDefineShape* oval = new FDTDefineShape(rectBounds);

	//record its ID so that we can later refer to it
	U16 ovalID = oval->ID();

	//construct a blue FColor
	//construct a solid fill style of the given color
	U32 blueFillID = oval->AddSolidFillStyle(new FColor(0, 0, 0xff));

	//construct a black color
	FColor black = FColor(0, 0, 0);

	//add a black, 1 pixel (20 TWIPS) wide line style to oval, remembering to store the
	// position of the line style just as in the fill style.
	U32 blackLineStyleID = oval->AddLineStyle(20, new FColor( black ) );

	//Since you are done creating fill and line styles, indicate so
	oval->FinishStyleArrays();

	//construct the shape records which will describe the rectangle
	//there are FShapeRecChange, FShapeRecEdge, and FShapeRecEnd shapes
	FShapeRec* ovalShapeRecords[10];
	ovalShapeRecords[0] = new FShapeRecChange(false, true, true, false, true, 3414, 1707, 0, 
				   blueFillID, blackLineStyleID, 0, 0);

	//Create curved edge object (just a stuct of info), store it in EdgeRecord
	ovalShapeRecords[1] = new FShapeRecEdgeCurved( -586,  293, -828,    0);
	ovalShapeRecords[2] = new FShapeRecEdgeCurved( -828,    0, -586, -293);
	ovalShapeRecords[3] = new FShapeRecEdgeCurved( -586, -293,    0, -414);
	ovalShapeRecords[4] = new FShapeRecEdgeCurved(    0, -414,  586, -293);
	ovalShapeRecords[5] = new FShapeRecEdgeCurved(  586, -293,  828,    0);
	ovalShapeRecords[6] = new FShapeRecEdgeCurved(  828,    0,  586,  292);
	ovalShapeRecords[7] = new FShapeRecEdgeCurved(  586,  293,    0,  414);
	ovalShapeRecords[8] = new FShapeRecEdgeCurved(    0,  414, -586,  293);
	ovalShapeRecords[9] = new FShapeRecEnd();

	//Add the shape records to the rectangle shape object
	for (int i = 0;  i < 10 ;  i++)
		oval->AddShapeRec(ovalShapeRecords[i]);

	//Add the rectangle to the given object collection
	allTags.AddFObj(oval);

	//create a place object tag which puts the oval on the display list
	FCTPlaceObject2 *placeoval = new FCTPlaceObject2(false, // ~ _hasClipDepth
													 false, true, false, 
													 1, ovalID, 0, 0, 0, 0, 0/**/);

	//add the place object tag to the FObjCollection
	allTags.AddFObj(placeoval);

	//construct a show frame object
	FCTShowFrame *showFrame = new FCTShowFrame();

	//add the show frame object to the FObj collection;
	allTags.AddFObj(showFrame);

	//now create the movie
	allTags.CreateMovie("FExampleOval.swf", 11000, 8000, 12);
}
