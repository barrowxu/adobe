// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/20/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFMovie.h

	This header-file contains the declarations of high-level movie class.

		class HFMovie;

****************************************************************************************/

#ifndef HFMOVIE_H_
#define HFMOVIE_H_

#include <list>
#include <map>
#include "HFFrame.h"


//! Define a movie.
/*!	A movie contains one or more frames which are to be played in order.
	\sa HFFrame, HFObject
*/

class HFMovie
{
public:
	
	//! Creates a movie.
	/*!	*/
	HFMovie();

	
	/*! */
	~HFMovie();

	
	//! Add a frame object to a movie.
	/*!	This method adds a finished frame to a movie.
		\param	index	The index of the frame to be added.
		\return	The pointer to the frame being added.
	*/
	HFFrame* Frame( int index );

	
	//! Output movie object to file.
	/*!	This method writes the finished movie to a SWF file.
		\param filename The movie will be written to the file specified by filename.
	*/
	void WriteMovie( const char* filename);

	
	//! Set the frame rate, in unit of fps (frame per second).
	/*!	
		\param framerate	The frame rate to be set.
	*/
	void SetFrameRate( SFIXED framerate )	{	frameRate = framerate;   }

	
	//! Set the size of the movie stage.
	/*!	
		\param cx	The width of the movie stage.
		\param cy	The height of the movie stage.
	*/
	void SetSize( int cx, int cy )			{	sizeX = cx; sizeY = cy;  }

	// Internal methods, for use by the Frames.

	// A hack. The objects are created as they are allocated by the frame,
	// but we need that information later to do the depth sort. The placeObjList place object 
	// list contains all the FCTPlaceObject2s so they can be depth sorted in the WriteMovie.
	std::list<AddRemoveEvent>* GetARList( int id )	{ return &arListMap[ id ]; }
	
private:
	std::vector<HFFrame*> frameVector;
	int framesInUse;
	int frameRate;
	int sizeX;
	int sizeY;
	
	// Wow! This one is scary. It as a map of arLists. So it's used like this:
	//   arListMap[ defineTagId ] returns (is...) a list of AddRemoveEvents.
	std::map< int, std::list<AddRemoveEvent> > arListMap;	
};

#endif