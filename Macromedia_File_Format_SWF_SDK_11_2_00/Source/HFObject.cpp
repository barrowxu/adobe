// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/15/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFObject.cpp

****************************************************************************************/

#pragma warning( disable : 4786 )

#include "HFObject.h"
#include "HFMovie.h"
#include "FCT.h"


//////////////////////////////////////////////////////////////////////////////////////
//  --------  HFObject  --------------------------------------------------------------

HFObject::HFObject()
{
	objectID = -1;
	depth    = 1;
	defineWritten = false;
	embedded = false;
}


HFObject::~HFObject()
{
}


// A utility function for the objects to use. It writes the PlaceObject2 tag
// to put objects on the stage.

void HFObject::AddPlaceObject2( std::list<FObj*> *objList, HFMovie* movie )
{
	FMatrix* matrix = 0;
	
	if ( HasMatrix() )
	{
		matrix = CreateMatrix();
	}

	FCTPlaceObject2 *placeObject = new FCTPlaceObject2(
										false,	// has clip depth
										false,	// has ratio
										true,	// has char id
										false,	// has move
										GetDepth(), 
										DefineTagId(), 
										matrix, 
										NULL,	// color xform
										0,		// ratio
										NULL,	// name
										0);		// clip depth

	objList->push_back( placeObject );


	// Record this add for the depth processing later.
	AddRemoveEvent ar;
	ar.place = placeObject;
	ar.remove = 0;
	ar.originalDepth = GetDepth();
// 	ar.newDepth = -1;

	// Now things get strange - since the HFObjects have less scope than the movie, for example:
	// HFMovie movie;
	// {
	//		HFRectangle rect(.....);
	//		movie.Frame( 0 )->AddObject( &rect );
	// }
	// movie.Write(.....)
	// 
	// is valid code. So nothing that needs to persist can be stored in the 
	// objects. So the arLists are stored in the movie, and accessed by the define tag id.

	std::list<AddRemoveEvent> *arList = movie->GetARList( DefineTagId() );
	arList->push_back( ar );
}

void HFObject::RemoveFromFrame( std::list<FObj*> *objList, HFMovie* movie )
{
 	FCTRemoveObject *removeObject = new FCTRemoveObject( DefineTagId(),  GetDepth());

	objList->push_back( removeObject );


	// Record this add for the depth processing later.
	// There should be an add in our arList, for which this remove matches.
	std::list<AddRemoveEvent> *arList = movie->GetARList( DefineTagId() );

	FLASHASSERT( arList->size() > 0 );	// If you get this assert, it means this objects is being
										// removed but was never added.
		
	AddRemoveEvent& ar = arList->back();

	FLASHASSERT( ar.place );			// If you get these asserts, it probably means the object is being
	FLASHASSERT( ar.remove == NULL );    // doubly removed. Or there is an error with the id's.

	ar.remove = removeObject;
}