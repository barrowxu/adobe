// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/20/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFFrame.cpp

  This source file contains the definition for high-level frame functions,

		Class						Member Function

	HFFrame						HFFrame(HFMovie*);
								~HFFrame();
								void AddObject(HFObject*);
								void RemoveObject(HFObject*);
								void SetBackgroundColor(FRGB);
								AddAction(HFAction*);

****************************************************************************************/

#pragma warning( disable : 4786 )

#include "HFFrame.h"
#include "HFMovie.h"
#include "FCT.h"

//////////////////////////////////////////////////////////////////////////////////////
//  --------  HFFrame  ---------------------------------------------------------------

HFFrame::HFFrame( HFMovie* parent )
{
	parentMovie = parent;
}


HFFrame::~HFFrame(void)
{
	while(!objList.empty()){
		delete objList.front();
		objList.pop_front();
	}
}


void HFFrame::AddObject( HFObject* object )
{
	// Generally, objects need to be placed. But not all do 
	object->AddToObjectList( &objList, parentMovie );
}


void HFFrame::RemoveObject( HFObject* object)
{

	object->RemoveFromFrame( &objList, parentMovie );
}


void HFFrame::SetBackgoundColor(FRGBA color_RGBA)
{
	// Convert RGBA to RGB. Background color really doesn't need alpha channel.
	FColor* color_RGB = new FColor(color_RGBA.red, color_RGBA.green, color_RGBA.blue);
	FCTSetBackgroundColor* background = new FCTSetBackgroundColor( color_RGB );

	objList.push_back( background );
}


void HFFrame::AddAction(HFAction* action)
{
	FCTDoAction *doAction = new FCTDoAction();
	action->AddToAction(doAction);
	objList.push_back( doAction );
}