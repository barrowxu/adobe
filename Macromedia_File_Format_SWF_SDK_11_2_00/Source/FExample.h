// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 09/08/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FExample.h

  This header-file includes all the function prototypes of low-level examples to demo
  Flash File Format SDK low-level manager.


****************************************************************************************/

#ifndef _F_EXAMPLE_H_ 
#define _F_EXAMPLE_H_ 

void CreateRectangleMovie();
void MakeButtonMovie();
void CreateSoundMovie();
void CreateBitsMovie();
void CreateJPegMovie();
void MakeMorphMovie();
void MakeSpriteMovie();
void CreateOverlapMovie();
void CreateTwoShapes();
void CreateTwoColorTriangleMovie();
void CreateCircleMovie();
void CreateTextFieldMovie();
void CreateOvalMovie();
void CreateClipMovie();
void CreateFontMovie();

U16 CreateRectangle(FObjCollection *objCollection, FColor* fillColor, 
							   SCOORD xmin, SCOORD xmax, SCOORD ymin, SCOORD ymax);


FShapeRecChange* NewShapeRecChange(U32 _newStylesFlag, 
								   U32 _lineStyleFlag, 
								   U32 _fillStyle0Flag, 
								   U32 _fillStyle1Flag, 
								   U32 _moveFlag,
								   S32 _deltaX,
								   S32 _deltaY,
								   U32 _fillStyle1,
								   U32 _fillStyle0,
								   U32 _lineStyle,
								   FFillStyleArray* _fillStyleArray,
								   FLineStyleArray* _lineStyleArray);

FShapeRecEnd* NewEnd();

FRect* NewRect(S32 _xmin, S32 _ymin, S32 _xmax, S32 _ymax);

#endif