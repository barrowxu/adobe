// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/18/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FExampleTwoColorTriangle.cpp

   Creates a one frame two color triangle movie with:
   
	1) a standard 1 pixel wide, black line style, drawing the first two edges with red 
	   and the last edge in blue. However, the result is unexpected.
 
****************************************************************************************/

#include "F3SDK.h"
#include "FExample.h"

void CreateTwoColorTriangleMovie(){

	FObjCollection allTags;

	// background color
	const FColor white(0xff, 0xff, 0xff);
	FCTSetBackgroundColor* background = new FCTSetBackgroundColor(new FColor( white));
	allTags.AddFObj(background);
	
	// Set bounding rectangle.
	FRect* rectBounds = new FRect(2800, 2260, 6019, 4980);
	FDTDefineShape* triangle = new FDTDefineShape(rectBounds);
	U16 triangleID = triangle->ID();

	// Define two fill colors: red and blue.
	FColor red = FColor(0xff, 0, 0);
	FColor blue = FColor(0, 0, 0xff);
	U32 redfillID = triangle->AddSolidFillStyle(new FColor( red));
	U32 bluefillID = triangle->AddSolidFillStyle(new FColor( blue));

	// Define the line style: black, 1 pixel (20 twips) wide.
	FColor black = FColor(0, 0, 0);
	//add a black, 1 pixel (20 TWIPS) wide line style to triangle, remembering to store the
	// position of the line style just as in the fill style.
	U32 blackLineStyleID = triangle->AddLineStyle(20, new FColor( black ) );
	triangle->FinishStyleArrays();

	// Constructing the triangle shape.
	// Draw the first two edges with red color fill.
	FShapeRec* triangleShapeRecords[6];
	triangleShapeRecords[0] = new FShapeRecChange(false, true, true, false, true, 6019, 3920, 0, 
												   redfillID, blackLineStyleID, 0, 0);
	triangleShapeRecords[1] = new FShapeRecEdgeStraight( -1819, -1660);
	triangleShapeRecords[2] = new FShapeRecEdgeStraight( -1400, 2720);
	// Draw the last edge with blue color fill.
	triangleShapeRecords[3] = new FShapeRecChange(false, false, true, false, true, 2800, 4980, 0, 
												   bluefillID, 0, 0, 0);

	triangleShapeRecords[4] = new FShapeRecEdgeStraight(3219, -1060);
	triangleShapeRecords[5] = new FShapeRecEnd();

	for (int i = 0;  i < 6 ;  i++)
		triangle->AddShapeRec(triangleShapeRecords[i]);

	//Add the triangle to the given object collection
	allTags.AddFObj(triangle);

	//create a place object tag which puts the triangle on the display list
	FCTPlaceObject2 *placeTriangle = new FCTPlaceObject2(   false, // ~ _hasClipDepth
															false, true, false, 
														    1, triangleID, 0, 0, 0, 0, 0/**/);

	//add the place object tag to the FObjCollection
	allTags.AddFObj(placeTriangle);

	//construct a show frame object
	FCTShowFrame *showFrame = new FCTShowFrame();

	//add the show frame object to the FObj collection;
	allTags.AddFObj(showFrame);

	//now create the movie
	allTags.CreateMovie("FExampleTwoColorTriangle.swf", 11000, 8000, 12);

}