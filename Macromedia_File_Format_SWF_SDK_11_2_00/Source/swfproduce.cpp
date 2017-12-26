// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 09/08/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: swfproduce.cpp

	This source file contains the main function for generating all the example movie files
	for both high-level and low level managers.

****************************************************************************************/

#include "F3SDK.h"
#include "FExample.h"
#include "HF3SDK.h"
#include "HFExample.h"

int main(int argc, char *argv[])
{
	MakeButtonMovie();
	MakeMorphMovie();
	MakeSpriteMovie();

	CreateRectangleMovie();
	CreateCircleMovie();
	CreateSoundMovie();
	CreateBitsMovie();
	CreateJPegMovie();
		// 	CreateOverlapMovie();
		// 	CreateTwoShapes();
	CreateTwoColorTriangleMovie();
	CreateOvalMovie();
	CreateClipMovie();
	CreateFontMovie();

	HLCreateRectangleMovie();
	
	HLCreateSquareMovie();
	HLCreateCircleMovie();
	HLCreateOvalMovie();
	HLCreateSoundMovie();
	HLCreateFontMovie();
	HLCreateButtonMovie();
	CreateTextFieldMovie();
	HLCreateSuperMovie();
	return (0);
}



