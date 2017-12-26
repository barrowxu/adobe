// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/15/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFRectangle.cpp

  This source file contains the definition for high-level rectangle functions,

		Class						Member Function

	HFRectangle					HFRectangle(int, int, int ,int);
								void AddToObjectList(std::list<FObj*>*);

****************************************************************************************/

#include "HFRectangle.h"
#include "HFColors.h"
#include "FPrimitive.h"

//////////////////////////////////////////////////////////////////////////////////////
//  --------  HFRectangle  -----------------------------------------------------------

HFRectangle::HFRectangle( int x1, int y1, int x2, int y2 ) : HFShape( x1, y1, x2, y2 )
{
	xmin = x1;
	ymin = y1;
	xmax = x2;
	ymax = y2;
}


void HFRectangle::AddToObjectList(std::list<FObj*> *objList, HFMovie* movie)
{
	if ( !defineWritten )
	{
		FRect* rect					= new FRect( bounds );
		FDTDefineShape3* shapeTag	= new FDTDefineShape3( rect );

		SetDefineTagId( shapeTag->ID() );

		FillShapeHeader(objList, shapeTag);

		FShapeRec* rectangleShapeRecords[6];
		rectangleShapeRecords[0] = new FShapeRecChange( false, true, true, false, true, 
														bounds.Xmin(), bounds.Ymin(), 
														0, colorFillID, lineStyleID, NULL, NULL);
		rectangleShapeRecords[1] = new FShapeRecEdgeStraight( bounds.Width(),	0				);
		rectangleShapeRecords[2] = new FShapeRecEdgeStraight( 0,				bounds.Height() );
		rectangleShapeRecords[3] = new FShapeRecEdgeStraight( -bounds.Width(),	0				);
		rectangleShapeRecords[4] = new FShapeRecEdgeStraight( 0,				-bounds.Height());
		rectangleShapeRecords[5] = new FShapeRecEnd();
		
		//Add the shape records to the rectangle shape object.
		for ( int i = 0;  i < 6; i++)
			shapeTag->AddShapeRec(rectangleShapeRecords[i]);

		//Add the rectangle to the given object list.
		objList->push_back ( shapeTag );
		defineWritten = true;
	}
	if ( !embedded )
	{
		AddPlaceObject2( objList, movie );
	}
}

