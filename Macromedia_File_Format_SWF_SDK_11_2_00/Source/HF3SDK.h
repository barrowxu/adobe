// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 10/15/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HF3SDK.h

  This header-file includes all the header-files of Flash File Format SDK
  high-level manager and the enumeration of button events.

****************************************************************************************/

#ifndef HF3SDK_H_
#define HF3SDK_H_


#include "F3SDK.h"

#include "HFColors.h"
#include "HFObject.h"
#include "HFShape.h"
#include "HFRectangle.h"
#include "HFOval.h"
#include "HFBitmap.h"
#include "HFText.h"
#include "HFPolygon.h"
#include "HFSound.h"
#include "HFFont.h"

#include "HFButton.h"
#include "HFAction.h"

#include "HFFrame.h"
#include "HFMovie.h"

#include "FFixed.h"

const int FPIXEL = 20;

enum{	MENU_DRAG_OUT			= OverDownToIdle,
		MENU_DRAG_OVER			= IdleToOverDown,

		PUSH_RELEASE_OUTSIDE	= OutDownToIdle,
		PUSH_DRAG_OVER			= OutDownToOverDown,
		PUSH_DRAG_OUT			= OverDownToOutDown,

		RELEASE					= OverDownToOverUp,
		PRESS					= OverUpToOverDown,
		ROLL_OUT				= OverUpToIdle,
		ROLL_OVER				= IdleToOverUp
	};
  
#endif
