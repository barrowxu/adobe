// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 11/04/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFSound.cpp

  This source file contains the definition for high-level sound functions,

		Class						Member Function

	HFSound						HFSound(FILE*, int);
								HFSound(int, int, int, int, void*, int, int);
								void AddToObjectList(std::list<FObj*>*);

****************************************************************************************/

#include "HFSound.h"
#include "FCT.h"

//////////////////////////////////////////////////////////////////////////////////////
//  --------  HFSound  ---------------------------------------------------------------

HFSound::HFSound( FILE* wavData, int compression )
{
	sound = new FDTDefineSoundWAV( wavData, compression );
	SetDefineTagId( sound->ID() );
}

HFSound::HFSound(	int rate, 
					int size, 
			 		int type, 
					int sampleCount,
					const void* data, 
					int dataSize,
					int compression )
{
	sound = new FDTDefineSoundADPCM( rate, size, type, sampleCount, (U8*)data, dataSize, compression );
	SetDefineTagId( sound->ID() );
}

void HFSound::AddToObjectList(std::list<FObj*> *objList, HFMovie* movie)
{
	// And info about the sound - but don't add yet.
	FSoundInfo* soundInfo = new FSoundInfo( FSoundInfo::SyncNoMultiple, false, false, false, false, 
											0, 0, 0, 0, NULL );
	if ( !defineWritten )
	{
		// The sound streaming header
		FDTSoundStreamHead* head = new FDTSoundStreamHead( sound->Format(), sound->SoundType(), sound->NumSamples() );
		objList->push_back ( head );

		// add the sound now
		objList->push_back ( sound );

		defineWritten = true;
	}
	// a tag to start the sound playing
	FCTStartSound* startSound = new FCTStartSound( sound->ID(), soundInfo );
	objList->push_back ( startSound );
}

