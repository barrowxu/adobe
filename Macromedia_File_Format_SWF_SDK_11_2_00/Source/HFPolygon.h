// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 11/04/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFPolygon.h


	This header-file contains the declarations of high-level polygon class.
	Parent class is in the parentheses:

		class HFPolygon; (public HFShape)
		
****************************************************************************************/

#ifndef HFPOLYGON_INCLUDED
#define HFPOLYGON_INCLUDED

#include "HFShape.h"


//! Define a Polygon shape.
/*!	
	Defines a closed polygon of an arbitrary number of sides. You need at least 3 points to define
	a polygon.
	\sa HFShape, HFObject
*/
class HFPolygon : public HFShape
{
  public:
  		//! Creates a polygon from an array of lines.
		/*!	
			\param pointArray		A pointer to an array of SPOINTS, which contains x and y values in twips.
									If the last point does not have the same coordinates as the first point,
									the polygon will automatically be closed. The point array is copied, so
									the memory is not handed over to the HFPolygon object.
			\param numberOfPoints	The number of points in the pointArray.
			\sa HFShape
		*/
		HFPolygon( SPOINT* pointArray, int numberOfPoints );

		//! Creates a polygon that allows points to be added.
		/*!	
			\param originX	The x coordinate of the polygon's origin.
			\param originY	The y coordinate of the polygon's origin.
			\sa HFShape
		*/
		HFPolygon( int originX, int originY );

		//! Add a curved line to the polygon.
		/*!	
			\param controlDX	The x coordinate of the control point for the curve edge.
			\param controlDY	The y coordinate of the control point for the curve edge.
			\param anchorDX		The x coordinate of the anchor point for the curve edge.
			\param anchorDY		The y coordinate of the anchor point for the curve edge.
			\sa HFShape
		*/
		void AddCurvedLine(S32 controlDX, S32 controlDY, S32 anchorDX, S32 anchorDY);
		
		//! Creates a polygon that allows points to be added.
		/*!	
			\param dx	The x coordinate of the new vertex.
			\param dy	The y coordinate of the new vertex.
			\sa HFShape
		*/
		void AddStraightLine( int dx, int dy );

		/*! */
		~HFPolygon();

		//! Creates a polygon that allows points to be added.
		/*!	
			\return	A FShape object of the Polygon - used by the font system.	
			\sa HFShape
		*/
		FShape* CreateFShape();

		// Method for internal use.
		void AddToObjectList(std::list<FObj*> *objList, HFMovie* movie);
  private:
		enum {
			ALLOCATE = 8
		};

		struct PointData 
		{
			bool	straight;
			union	{
					 int x;
					 int anchorDx;
					};
			union	{
					 int y;
					 int anchorDy;
					};
			int controlDx;
			int controlDy;
		};
	
		void AddShapeRecords( FDTDefineShape3*, int fillID, int lineID );		// returns an array of the shape records.
		void CalculateAndSetBounds();

		std::vector<PointData>	pointArray;
		int			numberOfPoints;
};

#endif