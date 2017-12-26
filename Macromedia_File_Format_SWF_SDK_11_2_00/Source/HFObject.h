// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/15/1999.
// Lee Thomason: object restructure, define tag id, embedded objects. Docs. 11/1999

/****************************************************************************************

				File Summary: HFObject.h

	This header-file contains the declarations of high-level object class.

		class HFObject;

****************************************************************************************/

#ifndef HFOBJECT_H_
#define HFOBJECT_H_

#include <list>
#include "FObj.h"


class FMatrix;
class FCTPlaceObject2;
class FCTRemoveObject;
class HFMovie;


// For the depths to be reassigned just before serialization, we must record every place
// and remove so as to re-write the depth values. The AddRemoveEvent structure stores 
// this information.

struct AddRemoveEvent
{
	FCTPlaceObject2* place;
	FCTRemoveObject* remove;
	int originalDepth;

	// We need to be able to sort on depths.
	bool operator==( const AddRemoveEvent& rhs )	{ return ( originalDepth == rhs.originalDepth ); }
	bool operator<( const AddRemoveEvent& rhs )		{ return ( originalDepth < rhs.originalDepth ); }
	bool operator>( const AddRemoveEvent& rhs )		{ return ( originalDepth > rhs.originalDepth ); }
};


//! Superclass for all high level objects.
/*!	The HFObject is an abstract class which is the parent class of all high level objects.<br>
	Memory Usage:
	Objects passed to the method calls of the High Level manager by 
	const reference are, of course, unchanged. Example:
	\code
		rect1.SetRadialFill( HunterGreen_RGBA, Black_RGBA );
	\endcode
	The 2 FColor objects, HunterGreen_RGBA and Black_RGBA, are created on the stack, and 
	used to set the radial fill.<br>
	Objects passed in by pointer may be changed, but are not owned by the high 
	level manager. So the high level manager won't delete the objects. Example:
	\code
		HFText* text;
		...
		movie->Frame( 0 )->AddObject( text );
	\endcode
	text is passed to the AddObject method, which may change text. However, it will not be
	deleted by the high level manaeger. So:
	\code
		HFText text;
		...
		movie->Frame( 0 )->AddObject( &text );
	\endcode
	would also be valid code, and does exactly the same thing.<br>
	The behavior of not taking owenership (and deleting) the objects passed 
	to the high level manager is 
	the exact opposite of the low level manager, which ownes the objects passed to 
	it, and will delete them when it serializes the SWF file.<br>
	Also note that large objects - sounds and bitmaps - passed to either the high or low level 
	manager will not be changed by either one. However, the object should persist until the SWF
	file is serialized.<br>
*/

class HFObject
{
  public:
	HFObject();
	virtual ~HFObject();

	//! Set the depth value for current shape.
	/*!	\param _depth The depth value to be set.*/
	void SetDepth( U16 _depth )							{ depth = _depth; }

	//! Get the depth of this shape.
	/*!	\return Return the depth of this shape.	*/
	U16	GetDepth()										{ return depth;	}


	// ---------- Methods for internal use. ---------------------------------------------------
	// Adds the object to the object list - often calls AddPlaceObject2 to write the place tag.
	virtual void AddToObjectList( std::list<FObj*> *objList, HFMovie* movie ) = 0;

	// Writes the RemoveObject tag.
	virtual void HFObject::RemoveFromFrame( std::list<FObj*> *objList, HFMovie* movie );

	int  DefineTagId()					{	FLASHASSERT( objectID >= 0 ); 
											return objectID; }

	// If the shape is part of a more complex objec - like a button - 
	// then it should not write a PlaceObject tag. Calling this and passing 
	// true suppresses the tag.
	void ObjectIsEmbedded( bool _embedded )		{ embedded = _embedded; }

  protected:
	virtual bool		HasMatrix()				{	return false; }
	virtual FMatrix*	CreateMatrix()			{   return 0;	  }

	void SetDefineTagId( int id )		{	objectID = id;	}
	
	// A utility function for the child classes. Adds the FCTPlaceObject2 tag
	// to the object list.
	void AddPlaceObject2( std::list<FObj*> *objList, HFMovie* movie );

	U16		depth;
	bool	defineWritten;		// if true, the define tag has been written. Set to false to write a new one.
	bool	embedded;

  private:
 	int		objectID;
};


#endif