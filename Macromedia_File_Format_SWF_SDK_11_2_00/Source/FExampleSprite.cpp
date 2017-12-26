// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 09/08/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FExampleSprite.cpp

   Creates a one frame sprite movie with:
   
	1) a red square sprite flickering in white background.
	
****************************************************************************************/

#include "F3SDK.h"
#include "FExample.h"

void MakeSpriteMovie(){

	const FColor red(0xff, 0, 0); 
	const FColor black(0, 0, 0);

	U32 xmin, xmax, ymin, ymax;
	xmin = 1000;
	ymin = 1000;
	xmax = 4000;
	ymax = 4000;

	//construct a rectangle that defines the shape's bounds 
	FRect* rectBounds = new FRect(xmin, ymin, xmax, ymax);  //coordinate values are in TWIPS

	//construct the FDTDefineShape which will be the rectangle image
	FDTDefineShape* rectangle = new FDTDefineShape(rectBounds);

	//record its ID so that we can later refer to it
	U16 rectangleID = rectangle->ID();

	//construct a solid fill style of the given color
	//add the fill style to the rectangle
	//you must record the position of the fill style in the fill style array 
	//so that you can later refer to it.  the Add funcion of rectangle returns
	//the position so record that in a field called fillID
	U32 fillID = rectangle->AddSolidFillStyle(new FColor( red));
	
	//add a black, 1 pixel (20 TWIPS) wide line style to rectangle, remembering to store the
	// position of the line style just as in the fill style.
	U32 blackLineStyleID = rectangle->AddLineStyle(20, new FColor( black ) );

	//since we are done with styles, indicate so
	rectangle->FinishStyleArrays();
	

	//construct the shape records which will describe the button down image
	FShapeRec* rectangleShapeRecords[6];
	rectangleShapeRecords[0] = new FShapeRecChange(false, true, true, false, true, xmax, ymin, 0, 
												   fillID, blackLineStyleID, 0, 0);
	rectangleShapeRecords[1] = new FShapeRecEdgeStraight( 0, ymax-ymin  );
	rectangleShapeRecords[2] = new FShapeRecEdgeStraight( xmin-xmax, 0 );
	rectangleShapeRecords[3] = new FShapeRecEdgeStraight( 0, ymin-ymax );
	rectangleShapeRecords[4] = new FShapeRecEdgeStraight( xmax-xmin, 0 );
	rectangleShapeRecords[5] = new FShapeRecEnd();

	
	//Add the shape records to the rectangle shape object
	for (int i = 0;  i < 6 ;  i++)
		rectangle->AddShapeRec(rectangleShapeRecords[i]);

	FObjCollection flashObjects;

	flashObjects.AddFObj(rectangle);

	FMatrix* transformMatrix = new FMatrix();

	// Create third object, a control object which places the triangle object we just defined
	FCTPlaceObject2* placeRectangle = new FCTPlaceObject2(false, // ~ _hasClipDepth
													 true, true, false,
													 1, rectangleID, transformMatrix, 0, 0, 0, 0 /**/);

	
	FDTSprite* theSprite = new FDTSprite();

	theSprite->AddFObj(placeRectangle);
	//flashObjects.AddFObj(placeRectangle);

	theSprite->AddFObj( new FCTShowFrame() );
	//flashObjects.AddFObj( new FCTShowFrame() );

	U16 spriteID = theSprite->ID();


	flashObjects.AddFObj(theSprite);

	transformMatrix = new FMatrix();

	// Create third object, a control object which places the triangle object we just defined
	FCTPlaceObject2* placeSprite = new FCTPlaceObject2( false, // ~ _hasClipDepth
														true, true, false,
														1, spriteID, transformMatrix, 0, 0, 0, 0/**/);

	flashObjects.AddFObj(placeSprite);

	flashObjects.AddFObj( new FCTShowFrame() );

	FCTRemoveObject2* remove = new FCTRemoveObject2(1);

	flashObjects.AddFObj(remove);



	flashObjects.AddFObj( new FCTShowFrame() );
	

	flashObjects.CreateMovie("FExampleSprite.swf");
	


}
