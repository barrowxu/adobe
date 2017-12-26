// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 09/08/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FExampleMorph.cpp

   Creates a 66-frame morph movie with:
   1) a light blue background;
   2) the starting triangle with black, straight edges morphed into the ending triangle
   with white, curved edges.
   
****************************************************************************************/

#include "F3SDK.h"
#include "FExample.h"

void MakeMorphMovie (){
	
	
	// Define colors
	// These can be constants because they are copied when passed, they don't require the use dynamic memory like most data types
	// As a rule, pointer parameters take objects created from dynamic memory, otherwise stack objects 
	const FColor lightBlue(0xaa, 0xdd, 0xdd);
	const FColor blackA(0, 0, 0, 0xff);
	const FColor whiteA(0xff, 0xff, 0xff, 0xff);
	
	// By end of procedure this will contain all flash objects created and will make the movie
	FObjCollection flashObjects;
	

	// First flash object created
	// It is a control object which sets the movie's background color
	FCTSetBackgroundColor* background = new FCTSetBackgroundColor( new FColor( lightBlue ) );
	
	// Object is added to collection
	flashObjects.AddFObj(background);
	
	
	// Create second flash object, a definition for a morphing shape (in this case a triangle/"3-lobed-star")
	// Contains appearance information for both the "morph from" and "morph to" shape
	// Here's where we use those arrays we created
	FDTDefineMorphShape* morphingTriangle;
	morphingTriangle = new FDTDefineMorphShape(NewRect(2000, 2000, 8000, 8000),
											   NewRect(2000, 2000, 8000, 8000));
	
	
	// Record morphing triangle's ID for later reference
	U32 triangleID = morphingTriangle->ID();
	
	
	// Add a morph line style (one which contains both "morph from" and "morph to" line style
	// information) to array and record its index (which is automatically returned) for later
	// reference
	U32 blackToWhiteLineIndex = morphingTriangle->AddLineStyle(20, new FColor(blackA),
															  500, new FColor(whiteA));
	
	//Since we are done with styles, indicate so
	morphingTriangle->FinishStyleArrays();
	
	//Here are the shape records which describe the appearance of the morphing shape
	//They are created and added to the morphing triangle
	//The AddShapeRec_1 method takes style information for both shapes and edge information for the "morph from" shape
	//The AddEdgeRec_2 method takes edge information for just the "morph to" 
	
	morphingTriangle->AddShapeRec_1(NewShapeRecChange(false, true, false, false, true,
													  5000, 4000, 0, 0,
													  blackToWhiteLineIndex, 0, 0));
	morphingTriangle->AddShapeRec_1( new FShapeRecEdgeStraight( 1000, 2000 ) );
	morphingTriangle->AddShapeRec_1( new FShapeRecEdgeStraight( 1000, -2000 ) );
	morphingTriangle->AddShapeRec_1( new FShapeRecEdgeStraight( -2000, 0 ) );
	morphingTriangle->AddShapeRec_1( NewEnd() );
	
	
	
	morphingTriangle->AddEdgeRec_2 ( NewShapeRecChange(false, false, false, false, true,
													   5000, 4000, 0, 0, 0,
													   0, 0) );
	morphingTriangle->AddEdgeRec_2( new FShapeRecEdgeCurved(4689,-1648,-3689,3648 )  );
	morphingTriangle->AddEdgeRec_2( new FShapeRecEdgeCurved(-811,3662,-1209,-3662)  );
	morphingTriangle->AddEdgeRec_2( new FShapeRecEdgeCurved(-3974,-3422,4994,1442)  );
	morphingTriangle->AddEdgeRec_2( NewEnd() );

	// morphing triangle is added to collection
	flashObjects.AddFObj(morphingTriangle);

	// Using default constructor, create a transformation matrix that has no transformation information
	FMatrix* transformMatrix = new FMatrix();

	// Create third object, a control object which places the triangle object we just defined
	FCTPlaceObject2* placeTriangleMorph = new FCTPlaceObject2(
													false, // ~ _hasClipDepth
													false,  //   has ratio
													true,  //	has ID		 
													false, //	has move
													1,			// depth
													triangleID, 
													transformMatrix, 
													0,	
													0, 
													0, 
													0 );

	//Add object to collection
	flashObjects.AddFObj(placeTriangleMorph);

	// Create fourth object (a "show frame" control object)
	// Signals to player that everything before it, up to the last show frame object belongs to the current frame
	flashObjects.AddFObj(  (new FCTShowFrame())  );


	
	//Now acomplishing the morph over subsequent frames is a trivial task
	//It is a matter of placing the morph in eash subsequent frame with a different morph ratio
	//The ratio is some number in the range 0 to 65535 indicating amount possition in the morphing sequence
	//A 0 represents the complete "morph from" shape and 65535 represents the complete "morph to" shape
	
	// A for loop is used used here to create remaining frames

	// Number of frames wanted in in morph movie
	// Used in for loop
	U32 nFrames = 66;
	
	// These assignments only explicitly show that once passed, transformMatrix value is no longer usable 
	transformMatrix = 0;	
	placeTriangleMorph = 0; 

	for (int i = 0;  i < 65000; i += (65000 / (nFrames - 1))){

//		transformMatrix = new FMatrix();

		placeTriangleMorph = new FCTPlaceObject2( false,	// ~ _hasClipDepth
												  true,		// has ratio
												  false,	// has Id
												  true,		// has move
												  1,		// depth
												  0,		// character id
												  0,		// matrix 
												  0,		// color transform
												  i,		// ratio
												  NULL,		// name
												  0 );		// clip
		flashObjects.AddFObj(placeTriangleMorph);

	
		flashObjects.AddFObj(  (new FCTShowFrame())  );

	}
	
	// Have collection make movie
	flashObjects.CreateMovie("FExampleMorph.swf", 11000, 8000, 12);

}





// helper functions:
// all create new objects from dynamically alocated memory

FShapeRecChange* NewShapeRecChange(U32 _newStylesFlag, 
								   U32 _lineStyleFlag, 
								   U32 _fillStyle0Flag, 
								   U32 _fillStyle1Flag, 
								   U32 _moveFlag,
								   S32 _deltaX,
								   S32 _deltaY,
								   U32 _fillStyle0,
								   U32 _fillStyle1,
								   U32 _lineStyle,
								   FFillStyleArray* _fillStyleArray,
								   FLineStyleArray* _lineStyleArray){

	return (new FShapeRecChange(_newStylesFlag, _lineStyleFlag, _fillStyle1Flag,
								_fillStyle0Flag, _moveFlag, _deltaX, _deltaY,
								_fillStyle0, _fillStyle1, _lineStyle, 
								_fillStyleArray, _lineStyleArray));
}

FShapeRecEnd* NewEnd(){

	return (new FShapeRecEnd());

}


FRect* NewRect(S32 _xmin, S32 _ymin, S32 _xmax, S32 _ymax){

	return (new FRect(_xmin, _ymin, _xmax, _ymax));

}
