// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 11/04/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFPolygon.cpp


  This source file contains the definition for high-level polygon functions,

		Class						Member Function

	HFPolygon					HFPolygon(SPOINT*, int);
								~HFPolygon();
								void CalculateAndSetBounds();
								HFPolygon(int, int);
								void AddStraightLine(int, int;
								void AddCurvedLine(S32, S32, S32, S32);
								void AddToObjectList(std::list<FObj*>*);
								FShape* CreateFShape();

****************************************************************************************/

#include "HFPolygon.h"
#include "HFColors.h"
#include "FPrimitive.h"

//////////////////////////////////////////////////////////////////////////////////////
//  --------  HFPolygon  -------------------------------------------------------------

// Sleazy trick to initialize the HFShape - create it with 0 bounds then
// set the bounds.
HFPolygon::HFPolygon( SPOINT* _pointArray, int _numberOfPoints ) : HFShape( 0, 0, 0, 0 )
{
	FLASHASSERT( _numberOfPoints > 2 );
	FLASHASSERT( _pointArray );
    int i;

	// Do we need to close?
	if (    _pointArray[0].x == _pointArray[_numberOfPoints-1].x 
	     && _pointArray[0].y == _pointArray[_numberOfPoints-1].y )
	{
		// we are closed
		FLASHASSERT( _numberOfPoints > 3 );
		pointArray.resize( _numberOfPoints );
		numberOfPoints = _numberOfPoints;

		pointArray[0].x = _pointArray[0].x;
		pointArray[0].y = _pointArray[0].y;

		for ( i = 1; i < numberOfPoints; i++ )
		{
			pointArray[i].straight = true;
			pointArray[i].x = _pointArray[i].x - _pointArray[i-1].x;
			pointArray[i].y = _pointArray[i].y - _pointArray[i-1].x;
		}
	}
	else
	{
		// close it
		pointArray.resize( _numberOfPoints+1 );
		numberOfPoints = _numberOfPoints+1;

		pointArray[0].x = _pointArray[0].x;
		pointArray[0].y = _pointArray[0].y;

		for ( i = 1; i < numberOfPoints-1; i++ )	// We need to add a point to the end - fill the
		{												// points we are given.
			pointArray[i].straight = true;
			pointArray[i].x = _pointArray[i].x - _pointArray[i-1].x;
			pointArray[i].y = _pointArray[i].y - _pointArray[i-1].y;
		}
		// Now the extra point.
		pointArray[i].straight = true;
		pointArray[i].x = _pointArray[0].x - _pointArray[i-1].x;
		pointArray[i].y = _pointArray[0].y - _pointArray[i-1].y;
	}
	CalculateAndSetBounds();
}


HFPolygon::~HFPolygon()
{}


void HFPolygon::CalculateAndSetBounds()
{
	int x, y, xmin, xmax, ymin, ymax;

	// Calculate the bounds - the min's and max's
	x = xmin = pointArray[0].x;
	    xmax = pointArray[0].x;
	y = ymin = pointArray[0].y;
	    ymax = pointArray[0].y;

	
	for ( int i = 1; i<numberOfPoints; i++ )
	{
		if ( pointArray[i].straight )
		{
			x += pointArray[i].x;
			y += pointArray[i].y;
		}
		else
		{
			x += pointArray[i].anchorDx;
			y += pointArray[i].anchorDy;
			x += pointArray[i].controlDx;
			y += pointArray[i].controlDy;
		}
		xmin = min( xmin, x );
		xmax = max( xmax, x );
		ymin = min( ymin, y );
		ymax = max( ymax, y );
	}
	SetBounds( xmin, ymin, xmax, ymax );
}

HFPolygon::HFPolygon( int originX, int originY ) : HFShape( 0, 0, 0, 0 )
{
	numberOfPoints = 1;
	pointArray.resize( ALLOCATE );
	pointArray[0].x = originX;
	pointArray[0].y = originY;

	CalculateAndSetBounds();
}

void HFPolygon::AddStraightLine( int dx, int dy )
{
	// Get enough memory
	if ( pointArray.size() <= numberOfPoints )
	{
		pointArray.resize( ( ( numberOfPoints/ALLOCATE ) + 1 ) * ALLOCATE );
	}
	// Add a straight segment
	pointArray[numberOfPoints].straight = true; 
	pointArray[numberOfPoints].x = dx; 
	pointArray[numberOfPoints].y = dy; 
	numberOfPoints++;

	CalculateAndSetBounds();
}


void HFPolygon::AddCurvedLine(S32 controlDX, S32 controlDY, S32 anchorDX, S32 anchorDY)
{
	// Get enough memory
	if ( pointArray.size() <= numberOfPoints )
	{
		pointArray.resize( ( ( numberOfPoints/ALLOCATE ) + 1 ) * ALLOCATE );
	}
	// Add a straight segment
	pointArray[numberOfPoints].straight = false; 
	pointArray[numberOfPoints].controlDx = controlDX; 
	pointArray[numberOfPoints].controlDy = controlDY; 
	pointArray[numberOfPoints].anchorDx = anchorDX; 
	pointArray[numberOfPoints].anchorDy = anchorDY; 
	numberOfPoints++;

	CalculateAndSetBounds();
}


void HFPolygon::AddToObjectList(std::list<FObj*> *objList, HFMovie* movie)
{
	if ( !defineWritten )
	{
		FRect* rect					= new FRect( bounds );
		FDTDefineShape3* shapeTag	= new FDTDefineShape3( rect );
	// 	objectID = shapeTag->ID();
		SetDefineTagId( shapeTag->ID() );

		FillShapeHeader(objList, shapeTag);

		shapeTag->AddShapeRec( new FShapeRecChange( false, true, true, false, true, 
													pointArray[0].x, pointArray[0].y, 
													0, colorFillID, lineStyleID, NULL, NULL) );

		for( int i = 1; i < numberOfPoints; i++ )
		{
			if ( pointArray[i].straight )
			{
				shapeTag->AddShapeRec( new FShapeRecEdgeStraight( pointArray[i].x, 
																  pointArray[i].y ) );
			}
			else
			{
				shapeTag->AddShapeRec( new FShapeRecEdgeCurved( pointArray[i].controlDx, pointArray[i].controlDy,
																pointArray[i].anchorDx,  pointArray[i].anchorDy  ) );
			}
		}
		shapeTag->AddShapeRec( new FShapeRecEnd() );

		//Add the rectangle to the given object list.
		objList->push_back ( shapeTag );
		defineWritten = true;
	}
	if ( !embedded )
	{
		AddPlaceObject2( objList, movie );
	}
}

FShape* HFPolygon::CreateFShape()
{	
	FShape* shape = new FShape();

	shape->AddShapeRec( new FShapeRecChange(	false, false, true, false, true, 
												pointArray[0].x, pointArray[0].y, 
												0, 1, 0, 0, 0 ));

// 	shape->AddShapeRec( new FShapeRecChange(	false, false, true, false, true, 
// 												pointArray[0].x, pointArray[0].y, 
// 												0, 0, 0, 0, 0) );

	for( int i = 1; i < numberOfPoints; i++ )
	{
		if ( pointArray[i].straight )
		{
			shape->AddShapeRec( new FShapeRecEdgeStraight(	pointArray[i].x, 
															pointArray[i].y ) );
		}
		else
		{
			shape->AddShapeRec( new FShapeRecEdgeCurved(	pointArray[i].controlDx, pointArray[i].controlDy,
															pointArray[i].anchorDx,  pointArray[i].anchorDy  ) );
		}
	}
	shape->AddShapeRec( new FShapeRecEnd() );
	return shape;
}
