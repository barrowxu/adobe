// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 09/08/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FObj.cpp

  This source file contains the definition for all low-level FObj-related functions,
  grouped by classes:

		Class						Member Function
  
	FObj							U32 IsShowFrame();

	FObjCollection					FObjCollection();
									~FObjCollection();
									void AddFObj(FObj*);
									void WriteToSWFStream(FSWFStream*);
									void CreateMovie(char*, SCOORD, SCOORD, U32);
									void WriteFileHeader(U32, SCOORD, SCOORD, U32, FILE*);
									void WriteEndTag(FSWFStream*);
									U16 Increment();

	FFragment						FFragment(void*, int);
									void WriteToSWFStream(FSWFStream*);

****************************************************************************************/

#pragma warning (disable:4786)	

#include "FObj.h"
#include "FPrimitive.h"
#include "FSWFStream.h"


//////////////////////////////////////////////////////////////////////////////////////
//  --------  FObj  ------------------------------------------------------------------

U32 FObj::IsShowFrame(){

	return 0;

}


//////////////////////////////////////////////////////////////////////////////////////
//  --------  FObjCollection  --------------------------------------------------------

//	When constructor is called, the empty FObjList is automatically created.
FObjCollection::FObjCollection(void){

	numOfFrames = 0;

}


//	Removes and deletes every element in the list.

FObjCollection::~FObjCollection(void){
	
	while(!FObjList.empty()){
		
		delete FObjList.front();
		FObjList.pop_front();
	
	}

}

//	The given FObj is added to the end of FObjList

void FObjCollection::AddFObj(FObj *fobj){

	if (fobj->IsShowFrame())  //increment numFrames then store the tag
		numOfFrames++;
	
	FObjList.push_back(fobj);

}


//	Uses a cursor to loop through the entire list and write all of the 
//  list's FObjs to the given SWFStream

void FObjCollection::WriteToSWFStream(FSWFStream *_SWFStream){
	
	std::list<FObj*>::iterator cursor;
	
	for (cursor = FObjList.begin(); cursor != FObjList.end(); cursor++){

		(*cursor)->WriteToSWFStream(_SWFStream);	
	
	}

}

void FObjCollection::CreateMovie( const char* fileName, SCOORD _movieWidth, SCOORD _movieHeight, U32 _frameRate )
{
	FILE* fp = fopen( fileName, "wb" );
	if ( fp )
	{
		FSWFStream stream;

		CreateMovie( &stream, _movieWidth, _movieHeight, _frameRate );
		stream.WriteToFile( fp );
		fclose( fp );
	}
}

// creates a Flash Movie
void FObjCollection::CreateMovie( FSWFStream* swfStream, SCOORD _movieWidth, SCOORD _movieHeight, U32 _frameRate )
{	
	// Carve out space for the header -- always 21 bytes
	for ( int i = 0; i < HEADER_SIZE; i++ )
		swfStream->WriteByte( 0 );

	// This FObjCollection is dumped into swfFileBody
	WriteToSWFStream( swfStream );

	//swfFileBody Terminated with a FCTEnd tag
	WriteEndTag( swfStream );

	// write file header into file
	WriteFileHeader( swfStream->Memory(), swfStream->Size(), _movieWidth, _movieHeight, _frameRate );

	characterID = 0;
}

// creates a Flash Movie
void FObjCollection::CreateSprite( FSWFStream* swfStream, SCOORD _movieWidth, SCOORD _movieHeight, U32 _frameRate )
{	
	// Sprites do not have headers.

	// This FObjCollection is dumped into swfFileBody
	WriteToSWFStream( swfStream );

	//swfFileBody Terminated with a FCTEnd tag
	WriteEndTag( swfStream );

	characterID = 0;
}

// This works differently than the other calls, because it hacks the header information back
// into the beginning of an existing SWF stream.
void FObjCollection::WriteFileHeader( U8* target, 
									  U32 _fileLengthNoHeader, 
									  SCOORD _movieWidth, 
									  SCOORD _movieHeight, 
									  U32 _frameRate )
{
	FSWFStream header;

	header.WriteByte( 'F' );
	header.WriteByte( 'W' );
	header.WriteByte( 'S' );
	header.WriteByte( 4 );

	header.WriteDWord( _fileLengthNoHeader );

	// Write the movie dimensions "by hand" so they will have the correct bit size.
	header.WriteBits( (U32) 15, 5 );	// 5 bits to say each of the following 4 fields will have 15 bits
	header.WriteBits( (U32) 0, 15 );
	header.WriteBits( (U32) _movieWidth, 15 );
	header.WriteBits( (U32) 0, 15 );
	header.WriteBits( (U32) _movieHeight, 15 );
	header.FlushBits();

	// The frame rate is 8.8 - we currently support 8.0
	header.WriteByte(0 );
	header.WriteByte(_frameRate);

	header.WriteWord(numOfFrames);

	// Copy this buffer to the target
	memcpy( target, header.Memory(), HEADER_SIZE );
}


void FObjCollection::WriteEndTag(FSWFStream* _SWFStream){

	_SWFStream->AppendTag( stagEnd, 0, 0 );	
}


// stores the number of flash objects created
U16 FObjCollection::characterID = 0;

// increments the number of flash objects created
U16 FObjCollection::Increment(void){
	return ++characterID;
}



//////////////////////////////////////////////////////////////////////////////////////
//  --------  FFragment  -------------------------------------------------------------

FFragment::FFragment( const void* _data, int _size )
{
	data = _data;
	size = _size;
}

void FFragment::WriteToSWFStream(FSWFStream *_SWFStream)
{
	_SWFStream->WriteLargeData( (U8*)data, size );
}
