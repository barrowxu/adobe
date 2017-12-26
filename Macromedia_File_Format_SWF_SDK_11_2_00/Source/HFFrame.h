// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/20/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFFrame.h

	This header-file contains the declarations of high-level frame class.

		class HFFrame;
	
****************************************************************************************/

#ifndef HFFRAME_H_
#define HFFRAME_H_

#include <list>
#include "HFShape.h"
#include "FObj.h"
#include "HFAction.h"

class HFMovie;


//! Define a frame of a movie.
/*!	
	\sa HFMovie, HFObject
*/
class HFFrame
{
public:
	//! Creates a frame.
	/*!
		\param parent	A pointer to the HFMovie object containing the frame.
	*/
	HFFrame( HFMovie* parent );
	
	/*! */
	~HFFrame();

	//! Add an object to a frame's character list.
	/*!	
		\param object	A pointer to the high-level object to be added.
	*/
	void AddObject( HFObject* ojbect);

	//! Remove an object from a frame's display list.
	/*!	
		\param object	A pointer to the high-level object to be removed.
	*/
	void RemoveObject( HFObject* object);

	//! Set the background color of current frame.
	/*!	The backgound color of the following frames is not going to change until
		this method is called with a different color value.
		\param color_RGBA The background color (in RGBA) to be set.
	*/
	void SetBackgoundColor( FRGBA color_RGBA);

	//! Add an action at the end of the current frame.
	/*! 
		\param action	A pointer to the high-level action to be added.
	*/
	void AddAction(HFAction* action);

	// Internal use.
	// The list of objects written from this frame.
	std::list<FObj*>*				GetObjList() { return &objList; } ;	

private:
	std::list<FObj*>				objList;
	HFMovie*						parentMovie;
};

#endif