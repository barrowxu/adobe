// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 09/08/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FObj.h

	This header-file contains the declarations of low-level FObj-related classes.
	All parent classes are in the parentheses:

		class FObj;
		class FFragment; (public FObj)
		class FObjCollection;

****************************************************************************************/

#ifndef _FOBJ_H_
#define _FOBJ_H_

#include <assert.h>
#include <list>

#pragma warning (disable:4786)	
#include "Macromedia.h"

//All Flash tagged data block objects fall into this category

class FObj
{
public:
	virtual ~FObj()		{}			// Doesn't do anything, just makes all the other destructors virtual

	virtual void WriteToSWFStream(FSWFStream *_SWFStream) = 0;
	virtual U32 IsShowFrame();
};

/*! A class for writing an arbitrary block of data (a SWF fragment, perhaps) to
 *	the SWFStream. The data is assumed to be large, so it is not changed.
 */
class FFragment : public FObj
{
public:
	FFragment( const void *data, int size );
	virtual void WriteToSWFStream(FSWFStream *_SWFStream);

private:
	const void*	data;
	int			size;
};
	

//	Holds a collection of FObj's so that they can be dumped in a SWF format
//Writes tags in the same order as they appear in the collection

//using namespace std;

class FObjCollection{

public:
	
	FObjCollection(void);
	~FObjCollection(void);
	void AddFObj(FObj *fobj);
	void WriteToSWFStream(FSWFStream *_SWFStream);
	void CreateMovie( const char* _fileName, SCOORD _movieWidth = 11000, SCOORD _movieHeight = 8000, U32 _frameRate = 12 );
	void CreateMovie( FSWFStream* stream, SCOORD _movieWidth = 11000, SCOORD _movieHeight = 8000, U32 _frameRate = 12 );
	void CreateSprite( FSWFStream* stream, SCOORD _movieWidth = 11000, SCOORD _movieHeight = 8000, U32 _frameRate = 12 );
	static U16 Increment(void);

private:
	enum {
		HEADER_SIZE = 21
	};

	U32 numOfFrames;
	std::list<FObj*> FObjList;
	void WriteFileHeader(U8* target, U32 _fileLengthNoHeader, SCOORD _movieWidth, SCOORD _movieHeight, 
						 U32 _frameRate );
	void WriteEndTag(FSWFStream* _SWFStream);
	static U16 characterID;

};
#endif