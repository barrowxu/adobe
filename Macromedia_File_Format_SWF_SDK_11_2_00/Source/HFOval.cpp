// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/29/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFOval.cpp

  This source file contains the definition for high-level oval and circle functions,

		Class						Member Function

	HFOval						HFOval(int, int, int, int);
								void AddToObjectList(std::list<FObj*>*);

	HFCircle					HFCircle(int, int, int);
								HFCircle(int, int, int, int);

****************************************************************************************/

#include "HFOval.h"
#include "HFColors.h"
#include "FPrimitive.h"

//////////////////////////////////////////////////////////////////////////////////////
//  --------  HFOval  ----------------------------------------------------------------

HFOval::HFOval(int _xMin, int _yMin, int _xMax, int _yMax)
 : HFShape( _xMin, _yMin, _xMax, _yMax )
{
	xmin = _xMin;
	ymin = _yMin;
	xmax = _xMax;
	ymax = _yMax;
}


void HFOval::AddToObjectList(std::list<FObj*> *objList, HFMovie* movie) 
{
	if ( !defineWritten )
	{
		FRect* rect					= new FRect( bounds );
		FDTDefineShape3* shapeTag	= new FDTDefineShape3( rect );

		SetDefineTagId( shapeTag->ID() );

		FillShapeHeader(objList, shapeTag);

		const double C1 = 0.1465;			// magic number for coefficient1
		const double C2 = 0.2070;			// magic number for coefficient2
		int dx = xmax - xmin;				// dx is width diameter
		int dy = ymax - ymin;				// dy is height diameter
		const double begin = 0.8535;		// starting position to draw (bounding square is 1x1)
		int startX = int (xmin + begin * dx);		// X coordinate of the starting position in twips
		int startY = int (ymin + begin * dy);		// Y coordinate of the starting position in twips
			
		// connect a serie of curves to draw the circle
		shapeTag->AddShapeRec ( new FShapeRecChange(false, true, true, false, true, startX, startY, 0, 
													colorFillID, lineStyleID, NULL, NULL) );
		shapeTag->AddShapeRec ( new FShapeRecEdgeCurved( -C1*dx,  C1*dy, -C2*dx,      0) );
		shapeTag->AddShapeRec ( new FShapeRecEdgeCurved( -C2*dx,      0, -C1*dx, -C1*dy) );
		shapeTag->AddShapeRec ( new FShapeRecEdgeCurved( -C1*dx, -C1*dy,      0, -C2*dy) );
		shapeTag->AddShapeRec ( new FShapeRecEdgeCurved(      0, -C2*dy,  C1*dx, -C1*dy) );
		shapeTag->AddShapeRec ( new FShapeRecEdgeCurved(  C1*dx, -C1*dy,  C2*dx,      0) );
		shapeTag->AddShapeRec ( new FShapeRecEdgeCurved(  C2*dx,      0,  C1*dx,  C1*dy) );
		shapeTag->AddShapeRec ( new FShapeRecEdgeCurved(  C1*dx,  C1*dy,      0,  C2*dy) );
		shapeTag->AddShapeRec ( new FShapeRecEdgeCurved(      0,  C2*dy, -C1*dx,  C1*dy) );
		shapeTag->AddShapeRec ( new FShapeRecEnd() );
		
		objList->push_back ( shapeTag );
		defineWritten = true;
	}
	if ( !embedded )
	{
		AddPlaceObject2( objList, movie );
	}
}


//////////////////////////////////////////////////////////////////////////////////////
//  --------  HFCircle  --------------------------------------------------------------

HFCircle::HFCircle( int center_x, int center_y, int radius )
 : HFOval( center_x - radius, center_y - radius,
            center_x + radius, center_y + radius )
{
	xmin = center_x - radius;		// x coordinate of the upper left corner of the bounding rectangle
	ymin = center_y - radius;		// y coordinate of the upper left corner of the bounding rectangle
	xmax = center_x + radius;		// x coordinate of the bottom right corner of the bounding rectangle
	ymax = center_y + radius;		// y coordinate of the bottom right corner of the bounding rectangle
}	


HFCircle::HFCircle(int _xMin, int _yMin, int _xMax, int _yMax)
 : HFOval( _xMin, _yMin, _xMax, _yMax )
{
	xmin = _xMin;
	ymin = _yMin;
	xmax = _xMax;
	ymax = _yMax;
}
