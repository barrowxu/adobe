// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 11/05/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFButton.h

	This header-file contains the declarations of high-level button class.
	Parent class is in the parentheses:

		class HFButton; (public HFObject)
	
****************************************************************************************/

#ifndef HFBUTTON_H_
#define HFBUTTON_H_

#include "HFColors.h"
#include "HFObject.h"
#include "HFShape.h"
#include "FPrimitive.h"
#include "FDTShapes.h"
#include "Macromedia.h"
#include "FAction.h"
#include "HFAction.h"
//! Buttons for actions
/*!	The HFButton is a child of HFObject class.
	\sa HFObject.
*/
class HFButton : public HFObject
{
public:
	//! Creates a button using one HFShape object and four colors, one for each button-state
	
	/*!	All four button-states share the same position and shape-outline. This allows a simple-looking
		button to be created quickly.
		\param shape		The outline of the button. Its fillcolor, if any, would be overwritten by the following
							colors in each state.
		\param up_color		Color for up state.
		\param over_color	Color for over state.
		\param down_color	Color for down state.
		\param hit_color	Color for hit state, which is always invisible.		*/
/*	HFButton(	HFShape* shape, 
				up_color, 
				over_color, 
				down_color, 
				hit_color = Black_RGBA	);
*/


	//! Creates a button using four HFShape objects, one for each button-state.
	/*!	This overloaded button constructor allows sophisticated-looking buttons to be created, with one complete
	    HFShape object for each of the four button-states specified explicitly.
		\param shape1	Appearance of up-state.
		\param shape2	Appearance of over-state.
		\param shape3	Appearance of down-state.
		\param shape4	Appearance of hit-state, which is always invisible.		*/
	HFButton(	HFShape* shape1, 
				HFShape* shape2, 
				HFShape* shape3, 
				HFShape* shape4		);

	/*! */
	~HFButton();

	//! This method specifies when to start playing next frame.
	/*!	\param event	What happened	*/
	void QueueEvent(HFAction* action, int event);

	// Method for internal use.
	void AddToObjectList( std::list<FObj*> *objList, HFMovie* movie );

private:
	enum{	UP, 
			OVER, 
			DOWN, 
			HIT
		};

	HFShape* shape[4];
	FActionCondition *ac;

	void AddEvent(int event);
};
#endif
