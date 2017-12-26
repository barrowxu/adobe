// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/29/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFOval.h 


	This header-file contains the declarations of high-level oval and circle class.
	Parent class is in the parentheses:

		class HFOval; (public HFShape)
		class HFCircle; (public HFOval)

****************************************************************************************/

#ifndef HFOVAL_H_
#define HFOVAL_H_

#include "HFShape.h"

//! Define an oval shape.
/*!	
	\sa HFCircle, HFShape, HFObject
*/
class HFOval : public HFShape
{
  public:
		//! Creates an oval.
		/*!	
			\param	xMin x coordinate of the upper left corner of the oval.
			\param	yMin y coordinate of the upper left corner of the oval.
			\param  xMax x coordinate of the bottom right corner of the oval.
			\param  yMax y coordinate of the bottom right corner of the oval.
			\sa HFShape, HFObject
		*/
	    HFOval(int xMin, int yMin, int xMax, int yMax);

		/*! */
		~HFOval(void){};

		// Method for internal use.
		void AddToObjectList(std::list<FObj*> *objList, HFMovie* movie);

  protected:
		int xmin;
		int ymin;
		int xmax;
		int ymax;
// 		void FillEdgeRecordArray( FDTDefineShape3* );
};

//! Define a circle shape
/*!	
	\sa HFOval, HFShape, HFObject
*/
class HFCircle : public HFOval
{
  public:
		//! Creates a circle.
		/*!	You need the [x,y] of circle center and radius to build a circle.
			\param	center_x x coordinate of circle center (in twips)
			\param	center_y y coordinate of circle center (in twips)
			\param  radius   radius of the circle
			\sa HFShape
		*/
        HFCircle(int center_x, int center_y, int radius);

		//! Creates a circle.
		/*!	
			\param xmin The x coordinate of the upper left corner of the bounding rectangle.
			\param ymin The y coordinate of the upper left corner of the bounding rectangle.
			\param xmax The x coordinate of the bottom right corner of the bounding rectangle.
			\param ymax The y coordinate of the bottom right corner of the bounding rectangle.	
			\sa HFShape
		*/
        HFCircle(int xmin, int ymin, int xmax, int ymax);

		/*! */
		~HFCircle(void){};
};

#endif