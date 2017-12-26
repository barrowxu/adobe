// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 11/04/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFExampleSound.cpp

   To demonstrate HFSound.
   Creates a multiple-frame movie with:
   
	1) a stream of sound playing.

****************************************************************************************/

#include "HF3SDK.h"
#include "HFExample.h"
#include <math.h>

void HLCreateSoundMovie()
{	
	HFMovie movie;
	HFSound* sound = 0;					

	// Create a sound from memory
	U16 soundData[ 11000 ];		// about 1 second at 11kHz mono

	// go for 440 cycles/second, which is 440 * 2pi radians per second
	for ( int i = 0; i < 11000; i++ )
	{
		soundData[i] = U16( sin( double(i) * 440.0 * 2 * 3.14 / 11000.0 ) * 30000 + 30000 );
	}

	sound = new HFSound( Snd11k, Snd16Bit, SndMono, 11000, soundData, 22000, FDTDefineSound::Comp2 );

	HFActionStop* action = new HFActionStop();
	movie.Frame( 0)->AddObject( sound );
	movie.Frame( 16)->AddObject( sound );
	movie.Frame( 50)->AddAction( action );

	delete action;
	delete sound;

	movie.WriteMovie("HFExampleSound.swf");
}
