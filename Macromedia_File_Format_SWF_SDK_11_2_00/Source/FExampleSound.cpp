// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 09/08/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FExampleSound.cpp

   Creates a one frame movie:
   
	1) with a yellow background, and
	2) playa sound file "audio.wav".

****************************************************************************************/

#include "F3SDK.h"
#include "FExample.h"

void CreateSoundMovie()
{
	const FColor yellow(0xff, 0xff, 0);	// for the background
	FObjCollection allTags;					// all the objects that make the movie
	FDTDefineSound* sound;

	// Construct and add the background. Note that only a contral tag is needed
	FCTSetBackgroundColor* background = new FCTSetBackgroundColor( new FColor( yellow ));
	allTags.AddFObj(background);

	// Create a sound.
	FILE* fp = fopen( "audio.wav", "rb" );
	if ( fp )
	{
		sound = new FDTDefineSoundWAV( fp, FDTDefineSoundWAV::Comp5 );
		fclose( fp );

		// And info about the sound - but don't add yet.
		FSoundInfo* soundInfo = new FSoundInfo( FSoundInfo::SyncNoMultiple, false, false, false, false, 
												0, 0, 0, 0, 0 );

		// The sound streaming header
		FDTSoundStreamHead* head = new FDTSoundStreamHead( sound->Format(), sound->SoundType(), sound->NumSamples() );
		allTags.AddFObj( head );

		// add the sound now
 		allTags.AddFObj( sound );

		// a tag to start the sound playing
		FCTStartSound* startSound = new FCTStartSound( sound->ID(), soundInfo );
 		allTags.AddFObj( startSound );
	}
	else
	{
		FLASHPRINT( "Error - audio.wav not found." );
	}

	//construct a show frame object
	FCTShowFrame *showFrame = new FCTShowFrame();

	//add the show frame object to the FObj collection;
	allTags.AddFObj(showFrame);

	//now create the movie
	allTags.CreateMovie("FExampleSound.swf", 11000, 8000, 12);
}