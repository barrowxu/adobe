// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 11/04/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFSound.h

	This header-file contains the declarations of high-level sound class.
	Parent class is in the parentheses:

		class HFSound; (public HFObject)

****************************************************************************************/

#ifndef HFSOUND_INCLUDED
#define HFSOUND_INCLUDED

#include "Macromedia.h"
#include "FDTSounds.h"
#include "HFObject.h"

//! Define a sound object.
/*!	
	\sa HFObject
*/
class HFSound : public HFObject
{
  public:
	//! Create a sound object from wav file data.
  	/*!	
		\param wavData		A FILE pointer to the WAV file to be played.	
		\param compression	The compression type, default is Comp5.
	*/
	HFSound( FILE* wavData, int compression = FDTDefineSound::Comp5 );

	//! Create a sound object from general data.
  	/*!	
		\param rate			Snd5k, Snd11k, Snd22k, Snd44k
		\param size			Snd8Bit, Snd16Bit
		\param type			SndMono, Snd Stereo
		\param sampleCount	How many samples ore in the sound data.
		\param data			A pointer to the data block.
		\param dataSize		The number of bytes of data.
		\param compression	The compression type, default is Comp5. See FDTDefineSound for more options.
	*/
	HFSound(	int rate, 
				int size, 
			 	int type, 
				int sampleCount,
				const void* data, 
				int dataSize,
				int compression = FDTDefineSound::Comp5 );

	// Method for internal use.
 	virtual void AddToObjectList(std::list<FObj*> *objList, HFMovie* movie);

  private:
	FDTDefineSound* sound;
};



#endif

