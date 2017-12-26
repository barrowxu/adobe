// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/15/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFRectangle.h

	This header-file contains the declarations of high-level rectangle class.
	Parent class is in the parentheses:

		class HFRectangle; (public HFShape)

****************************************************************************************/

#ifndef HFRECTANGLE_H_
#define HFRECTANGLE_H_

#include "HFShape.h"


//! Define a rectangle shape.
/*!	
	\sa HFShape, HFObject
*/
class HFRectangle : public HFShape
{
  public:
  		//! Creates a rectangle.
		/*!	You need the [x,y] of upper-left and bottom-right corners to build a rectangle.
			\param xmin The x coordinate of the upper left corner of the bounding rectangle.
			\param ymin The y coordinate of the upper left corner of the bounding rectangle.
			\param xmax The x coordinate of the bottom right corner of the bounding rectangle.
			\param ymax The y coordinate of the bottom right corner of the bounding rectangle.	
			\sa HFShape
		*/
		HFRectangle(int xmin, int ymin, int xmax, int ymax);

		/*! */
		~HFRectangle(void){};

		// Method for internal use.
		void AddToObjectList(std::list<FObj*> *objList, HFMovie* movie);

  private:
		int xmin;
		int ymin;
		int xmax;
		int ymax;
};

#endif