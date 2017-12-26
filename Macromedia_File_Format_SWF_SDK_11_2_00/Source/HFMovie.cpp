// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/19/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFMovie.cpp

  This source file contains the definition for high-level movie functions,

		Class						Member Function

	HFMovie						HFMovie();
								~HFMovie();
								HFFrame* Frame(int);
								void WriteMovie(char*);

****************************************************************************************/

#pragma warning ( disable : 4786 )

#include "HFMovie.h"
#include "FCT.h"

//////////////////////////////////////////////////////////////////////////////////////
//  --------  HFMovie  ---------------------------------------------------------------

HFMovie::HFMovie()
{
	framesInUse = 0;
	frameRate = 12;
	sizeX = 11000;
	sizeY = 8000;
}


HFMovie::~HFMovie()
{
	for ( int i = 0; i<frameVector.size(); i++ )
	{
		delete( frameVector[i] );
	}
}


HFFrame* HFMovie::Frame( int index )
{
	int current = frameVector.size();
	int i;
	
	if ( index + 1 > framesInUse )
	{
		framesInUse = index + 1;
	}

	// If the index is larger than the current # of frames, allocate more.
	if ( index >= frameVector.size() )
	{
		frameVector.resize( index + 8 );	// give ourselves some extra space.

		for ( i = current; i < frameVector.size(); i++ )
		{
			frameVector[i] = new HFFrame( this );
		}
	}
	return frameVector[index];
}


void HFMovie::WriteMovie( const char* filename)
{
	int i, depth;
	std::list<AddRemoveEvent> arList;
	std::list<FObj*>*	objectList;
	HFFrame* frame;

	// iterators:
	std::map< int, std::list<AddRemoveEvent> >::iterator mapIt;
	std::list<AddRemoveEvent>::iterator						it;

	// We must sort the depths so that each one is unique. Each depth is a reusable, however.
	// So if something is added at 8, and then removed at 8, then 8 is available.
	// Currently, this algorithm is trivial and just consumes depth. The largest movie in the
	// example has 130 or so shapes, far less than the 32k or 64k limit.

	// Collect all the arLists into one.
	for( mapIt = arListMap.begin(); mapIt != arListMap.end(); ++mapIt )
	{
		arList.merge( mapIt->second );
	}
	
	FLASHOUTPUT( "Depth sorting: %d shapes\n", arList.size() );

	// This sorts on the original depth (see struct AddRemoveEvent). The ordering of equal depths
	// is undefined.
	arList.sort();

	// Write new depths, and write the data back to the objects.
	for ( it = arList.begin(), depth = 0; it != arList.end(); ++it, ++depth )
	{
		AddRemoveEvent& ar = *it;

		if ( ar.place )
			ar.place->SetDepth( depth );

		if ( ar.remove )
			ar.remove->SetDepth( depth );
	}
	FLASHOUTPUT( "Depth sorting: complete\n" );


	// Now the depths are correct, so we can write the movie.
	FObjCollection allTags;
	FCTShowFrame *showFrame;


	// Process each frame in the frame list.

	for ( i = 0; i<framesInUse; i++ )
	{
		frame = frameVector[i];
		objectList = frame->GetObjList();

		// Process each object in the current frame's object list.
		while( !objectList->empty() )
		{
			// Add the object to the collection, then delete it from the object list.
			allTags.AddFObj( objectList->front() );
			objectList->pop_front();
		}
		
		// Add showFrame tag at the end of each frame.
		showFrame = new FCTShowFrame();
		allTags.AddFObj(showFrame);
	}

	// write movie to "filename" with 550x400 (pixels) stage and frame rate 2 fps.
	allTags.CreateMovie( filename, sizeX, sizeY, frameRate );
	
	// Delete the stored objects:
	for ( i = 0; i<frameVector.size(); i++ )
	{
		delete( frameVector[i] );
	}
	
	// and then clear the vector
	frameVector.resize( 0 );
	framesInUse = 0;
}
