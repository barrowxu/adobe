// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 09/08/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FExampleButton.cpp

   Creates a two-frame movie with:
   
	1) a white background,
	2) a rectangle button with red (UP), green(Over), blue (Down) and black (hit) in four
	   states on the first frame,
	3) an empty rectangle is shown on the stage center on the second frame,
	4) movie pauses on the first frame until the button is clicked (OverDownToOverUp state
	   transition), then the movie starts to play its second frame, and pause again.

****************************************************************************************/

#include "F3SDK.h"
#include "FExample.h"

void MakeButtonMovie()
{


	  // Define colors.
	const FColor white(0xff, 0xff, 0xff);		// used for background
	const FColor red(0xff, 0, 0);
	const FColor green(0, 0xff, 0);
	const FColor blue(0, 0, 0xff);
	const FColor black(0, 0, 0);

	  //Create a collection of FObj's named allTags which will contain all the FObj's that make the movie
	FObjCollection allTags;

	  // construct first flash tag object (set background color):
	  // construct the set background color tag object which takes a color as an argument
	FCTSetBackgroundColor* background = new FCTSetBackgroundColor( new FColor( white ) );

	  //add the set background color tag to allTags
	allTags.AddFObj(background);


	//construct a flash control tag object which stops the movie on the current frame

	  //construct an empty CTDoAction tag object
	FCTDoAction *doAction1 = new FCTDoAction();
	
	  //add the stop action to the CTDoAction tag object
	doAction1->AddAction(new FActionStop());

	  //add the CTDoAction object to allTags
	allTags.AddFObj(doAction1);


	//construct a DTDefineShape object which will be the button's up image
	//add it to collection object follection
	//remember ID
	U16 buttonUpID = CreateRectangle(&allTags, new FColor( red ), -1159, 1260, -620, 560);
	
	
	
		//construct a DTDefineShape object which will be the button's over image
	U16 buttonOverID = CreateRectangle(&allTags, new FColor( green ), -1159, 1260, -620, 560);
	
	

		//construct a DTDefineShape object which will be the button's down image
	U16 buttonDownID = CreateRectangle(&allTags, new FColor( blue ), -1159, 1260, -620, 560);
	
	
	
		//construct a DTDefineShape object which will be the button's hit image
	U16 buttonHitID = CreateRectangle(&allTags, new FColor( black ), -1159, 1260, -620, 560);
	


		//now define the actual button
	FDTDefineButton2 *theButton = new FDTDefineButton2(0); //flag is 0 to indicate a push button
	U16 theButtonID = theButton->ID();


		//button up record, defines how the button will look like in the up position

	FMatrix *mx = new FMatrix(); //blank matrix(by default identity)
	FCXFormWAlpha *cxf = new FCXFormWAlpha(false, false, 0, 0, 0, 0, 0, 0, 0, 0);
	FButtonRecord2 *bRec = new FButtonRecord2(false, false, false, true, buttonUpID, 1, mx, cxf);
	theButton->AddButtonRecord(bRec);
	
	
		//button over record, defines how the button will look like in the up position
	
	mx = new FMatrix();
	cxf = new FCXFormWAlpha(false, false, 0, 0, 0, 0, 0, 0, 0, 0);
	bRec = new FButtonRecord2(false, false, true, false, buttonOverID, 1, mx, cxf);
	theButton->AddButtonRecord(bRec);
	
	
		//button down record, defines how the button will look like in the over position
	
	mx = new FMatrix();
	cxf = new FCXFormWAlpha(false, false, 0, 0, 0, 0, 0, 0, 0, 0);
	bRec = new FButtonRecord2(false, true, false, false, buttonDownID, 1, mx, cxf);
	theButton->AddButtonRecord(bRec);
	
	
		//button hit record, defines how the button will look like in the hit position
	
	mx = new FMatrix();
	cxf = new FCXFormWAlpha(false, false, 0, 0, 0, 0, 0, 0, 0, 0);
	bRec = new FButtonRecord2(true, false, false, false, buttonHitID, 1, mx, cxf);
	theButton->AddButtonRecord(bRec);

	
		//the button action

	FActionCondition *ac = new FActionCondition();
	ac->AddCondition(OverDownToOverUp);
	ac->AddActionRecord(new FActionPlay());
	theButton->AddActionCondition(ac);

		//add the button to the FObj collection
	allTags.AddFObj(theButton);


	
		//construct a place object tag

		//make an identity matrix (no transformation information)
	FMatrix* matrix = new FMatrix();

		//make a "place object tag", include identity matrix
	FCTPlaceObject2* placeButton = new FCTPlaceObject2( false, // ~ _hasClipDepth
														true, true, false, 
														1, theButtonID, matrix, 0, 0, 0, 0/**/);

		//add the place object tag to the FObj collection
	allTags.AddFObj(placeButton);


		//construct a show frame object
	FCTShowFrame* showFrame = new FCTShowFrame();

		//add the show frame object to the FObj collection;
	allTags.AddFObj(showFrame);

		//create a remove object tag which removes the button from the display list
	FCTRemoveObject2 *remObj = new FCTRemoveObject2(1); //remove layer 1

		//add the remove tag to the FObj collection
	allTags.AddFObj(remObj);

	
		//construct a flash control tag object which stops the movie on the current frame

		//construct an empty CTDoAction tag object
	FCTDoAction *doAction2 = new FCTDoAction();
	
		//add the stop action to the CTDoAction tag object
	doAction2->AddAction(new FActionStop());

		//add the CTDoAction object to allTags
	allTags.AddFObj(doAction2);

		//create a rectangle

	U16 rectangleID = CreateRectangle(&allTags, new FColor( white ), 2020, 4900, 1680, 4000);


		//create a place object tag which puts the rectangle on the display list
	FCTPlaceObject2 *placeRectangle = new FCTPlaceObject2(  false, // ~ _hasClipDepth
															false, true, false, 
															1, rectangleID, 0, 0, 0, 0, 0/**/);

		//add the place object tag to the FObjCollection
	allTags.AddFObj(placeRectangle);

		//construct a show frame object
	showFrame = new FCTShowFrame();

		//add the show frame object to the FObj collection;
	allTags.AddFObj(showFrame);

		//now create the movie
	allTags.CreateMovie("FExampleButton.swf", 11000, 8000, 12 );

}



//Creates a rectangle shape object with the given fill color, a standard 1 pixel wide, black line
//style, and the given coordinates, and adds it to the given FObj collection.

U16 CreateRectangle(FObjCollection *objCollection, FColor* fillColor, SCOORD xmin, SCOORD xmax, SCOORD ymin, SCOORD ymax){

	//create a rectangle

	//construct a rect that defines the shape's bounds 
	FRect* rectBounds = new FRect(xmin-10, ymin-10, xmax+10, ymax+10);  //coordinate values are in TWIPS

	//construct the FDTDefineShape which will be the rectangle image
	FDTDefineShape* rectangle = new FDTDefineShape(rectBounds);

	//record its ID so that we can later refer to it
	U16 rectangleID = rectangle->ID();


	//construct a solid fill style of the given color, and 
	//add the fill style to the rectangle
	//you must record the position of the fill style in the fill style array 
	//so that you can later refer to it.  the AddFillStyle funcion of fillStyle array returns
	//the position so record that in a field called fillID
	U32 fillID = rectangle->AddSolidFillStyle(fillColor);
	
	//add a black, 1 pixel (20 TWIPS) wide line style to rectangle, remembering to store the
	// position of the line style just as in the fill style.
	U32 blackLineStyleID = rectangle->AddLineStyle(20, new FColor(0, 0, 0));

	//since you are done with fill and line styles, indicate so
	rectangle->FinishStyleArrays();
	
	//construct the shape records which will describe the button down image
	FShapeRec* rectangleShapeRecords[6];
	rectangleShapeRecords[0] = new FShapeRecChange(false, true, true, false, true, xmax, ymin, 0, 
												   fillID, blackLineStyleID, 0, 0);
	rectangleShapeRecords[1] = new FShapeRecEdgeStraight( 0, ymax-ymin);
	rectangleShapeRecords[2] = new FShapeRecEdgeStraight( xmin-xmax, 0);
	rectangleShapeRecords[3] = new FShapeRecEdgeStraight( 0, ymin-ymax);
	rectangleShapeRecords[4] = new FShapeRecEdgeStraight( xmax-xmin, 0 );
	rectangleShapeRecords[5] = new FShapeRecEnd();

	
	//Add the shape records to the rectangle shape object
	for (int i = 0;  i < 6 ;  i++)
		rectangle->AddShapeRec(rectangleShapeRecords[i]);

	//Add the rectangle to the given object collection
	objCollection->AddFObj(rectangle);

	//return the ID of the rectangle.
	return rectangleID;

}