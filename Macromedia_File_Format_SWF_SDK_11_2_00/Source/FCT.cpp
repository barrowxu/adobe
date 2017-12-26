// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Lee Thomason.
// First Created On 09/08/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FCT.cpp

  This source file contains the definition for the low-level Control-Tag related functions,
  grouped by classes, which are all derived from class FCT:


		Class						Member Function

		FCTDoAction				FCTDoAction(void);
								~FCTDoAction();
								void AddAction(FActionRecord*);
								void WriteToSWFStream(FSWFStream*);

		FCTFrameLabel			FCTFrameLabel(FString*);
								~FCTFrameLabel();
								void WriteToSWFStream(FSWFStream*);

		FCTPlaceObject			FCTPlaceObject(U16, U16, FMatrix*, FCXForm*);
								~FCTPlaceObject();
								void WriteToSWFStream(FSWFStream*);

		FCTPlaceObject2			FCTPlaceObject2(U16, U16, U16, U16, U16, U16, FMatrix*,
												FCXForm*, U16, FString*, U16);
								~FCTPlaceObject2();
								void WriteToSWFStream(FSWFStream*);

		FCTProtect				FCTProtect();
								void WriteToSWFStream(FSWFStream*);

		FCTRemoveObject			FCTRemoveObject(U16, U16);
								void WriteToSWFStream(FSWFStream*);

		FCTRemoveObject2		FCTRemoveObject2(U16);
								void WriteToSWFStream(FSWFStream*);

		FCTSetBackgroundColor	FCTSetBackgroundColor(FColor*);
								~FCTSetBackgroundColor();
								void WriteToSWFStream(FSWFStream*);

		FCTShowFrame			FCTShowFrame();
								U32 IsShowFrame();
								void WriteToSWFStream(FSWFStream*);

		FCTStartSound			FCTStartSound(U16, FSoundInfo*);
								~FCTStartSound();
								void WriteToSWFStream(FSWFStream*);


****************************************************************************************/

#include "FCT.h"
#include "FDTShapes.h"
#include "FDTSounds.h"

//////////////////////////////////////////////////////////////////////////////////////
//  --------  FCTDoAction ------------------------------------------------------------

FCTDoAction::FCTDoAction(void){
}


FCTDoAction::~FCTDoAction(){

	while (!actionRecordList.empty()){

		delete actionRecordList.front();
		
		actionRecordList.pop_front();

	}

}

void FCTDoAction::AddAction(FActionRecord* _actionRecord){
	
	actionRecordList.push_back(_actionRecord);
}




void FCTDoAction::WriteToSWFStream(FSWFStream* _SWFStream){
	
	FSWFStream body;

	std::list<FActionRecord*>::iterator cursor;
	for (cursor = actionRecordList.begin();  cursor != actionRecordList.end();   cursor++){

		(*cursor)->WriteToSWFStream(&body);

	}

	body.WriteByte(0);

	_SWFStream->AppendTag( stagDoAction, body.Size(), &body );	
}


//////////////////////////////////////////////////////////////////////////////////////
//  --------  FCTFrameLabel ----------------------------------------------------------

FCTFrameLabel::FCTFrameLabel(FString *_frameName){
	frameName = _frameName;
}

FCTFrameLabel::~FCTFrameLabel(){
	delete frameName;
}

void FCTFrameLabel::WriteToSWFStream(FSWFStream* _SWFStream){
	FSWFStream body;
	frameName->WriteToSWFStream(&body, true);
	
	_SWFStream->AppendTag( stagFrameLabel, body.Size(), &body );	
}


//////////////////////////////////////////////////////////////////////////////////////
//  --------  FCTPlaceObject ----------------------------------------------------------

FCTPlaceObject::FCTPlaceObject(	U16 _characterID, 
								U16 _depth, 
								FMatrix* _matrix, 
								FCXForm* _colorTransform )
{
	characterID = _characterID;
	depth = _depth;
	matrix = _matrix;
	colorTransform = _colorTransform;

	FLASHASSERT( _colorTransform );
}

FCTPlaceObject::~FCTPlaceObject(){
	delete matrix;
	delete colorTransform;

}
void FCTPlaceObject::WriteToSWFStream(FSWFStream* _SWFStream){
	
	FSWFStream body;;
	
	body.WriteWord((U32) characterID);
	
	body.WriteWord((U32) depth);
	
	matrix->WriteToSWFStream(&body);
	
	if (colorTransform){
		colorTransform->WriteToSWFStream(&body);
	}
	
	_SWFStream->AppendTag( stagPlaceObject, body.Size(), &body );	
}

//////////////////////////////////////////////////////////////////////////////////////
//  --------  FCTPlaceObject2 --------------------------------------------------------

FCTPlaceObject2::FCTPlaceObject2(	U16 _hasClipDepth,
									U16 _hasRatio, 
									U16 _hasChar, 
									U16 _hasMove, 
									U16 _depth, 
									U16 _characterID, 
									FMatrix* _matrix, 
									FCXForm* _colorTransform, 
									U16 _ratio, 
									FString* _name, 
									U16 _clipDepth )
{
	hasClipDepth	= _hasClipDepth;		
	hasRatio		= _hasRatio;
	hasCharID		= _hasChar;
	hasMove			= _hasMove;
	depth			= _depth;
	characterID		= _characterID;
	matrix			= _matrix;
	colorTransform	= _colorTransform;
	ratio			= _ratio;
	name			= _name;
	clipDepth		= _clipDepth;
}


FCTPlaceObject2::~FCTPlaceObject2(){
	
	delete name;
	delete matrix;
	delete colorTransform;
}

void FCTPlaceObject2::WriteToSWFStream(FSWFStream* _SWFStream){
	
	FSWFStream body;

	body.WriteBits(0, 1);                   /*DM*/
    body.WriteBits(hasClipDepth, 1);        /*DM*/
	body.WriteBits( ( name != 0 ), 1);
	body.WriteBits(hasRatio, 1);
	body.WriteBits( ( colorTransform != 0 ), 1);
	body.WriteBits( ( matrix != 0 ), 1);
	body.WriteBits(hasCharID, 1);
	body.WriteBits(hasMove, 1);
	
	body.WriteWord( depth );
	
	if (hasCharID)
		body.WriteWord((U32)characterID);
	if (matrix)
		matrix->WriteToSWFStream(&body);
	if (colorTransform)
		colorTransform->WriteToSWFStream(&body);
	if (hasRatio)
		body.WriteWord((U32)ratio);
	if (hasClipDepth)                                   /*DM*/  
        body.WriteWord((U32)clipDepth);                 /*DM*/
	if (name)
		name->WriteToSWFStream(&body, true);

	_SWFStream->AppendTag( stagPlaceObject2, body.Size(), &body );	
}

/////////////////////////////////////////////////////////////////////////////////
//  --------  FCTProtect --------------------------------------------------------

FCTProtect::FCTProtect()
{}

void FCTProtect::WriteToSWFStream(FSWFStream* _SWFStream){
	_SWFStream->AppendTag( stagProtect, 0, 0 );	
}


/////////////////////////////////////////////////////////////////////////////////
//  --------  FCTRemoveObject ---------------------------------------------------

FCTRemoveObject::FCTRemoveObject(U16 _characterID, U16 _depth){
	characterID = _characterID;
	depth = _depth;
}


void FCTRemoveObject::WriteToSWFStream(FSWFStream* _SWFStream){
	FSWFStream body;

	body.WriteWord((U32) characterID);
	body.WriteWord((U32) depth);

	_SWFStream->AppendTag( stagRemoveObject, body.Size(), &body );	
}

/////////////////////////////////////////////////////////////////////////////////
//  --------  FCTRemoveObject2 --------------------------------------------------

FCTRemoveObject2::FCTRemoveObject2(U16 _depth){
	depth = _depth;
}


void FCTRemoveObject2::WriteToSWFStream(FSWFStream* _SWFStream){
	FSWFStream body;
	body.WriteWord((U32)depth);

	_SWFStream->AppendTag( stagRemoveObject2, body.Size(), &body );	
}

/////////////////////////////////////////////////////////////////////////////////
//  --------  FCTSetBackgroundColor --------------------------------------------------

FCTSetBackgroundColor::FCTSetBackgroundColor( FColor* _color )
{
	color = _color;
	// here changed.
	// Background color is always opaque, i.e. no alpha channel.
	color->AlphaChannel(false);
}

FCTSetBackgroundColor::~FCTSetBackgroundColor()
{	
	delete( color );
}

void FCTSetBackgroundColor::WriteToSWFStream(FSWFStream* _SWFStream){
	
	FSWFStream body;
	// here changed.
	color->WriteToSWFStream(&body);

	_SWFStream->AppendTag( stagSetBackgroundColor, body.Size(), &body );	
}

/////////////////////////////////////////////////////////////////////////////
//  --------  FCTShowFrame --------------------------------------------------

FCTShowFrame::FCTShowFrame(){

}

U32 FCTShowFrame::IsShowFrame(){

	return 1;

}

void FCTShowFrame::WriteToSWFStream(FSWFStream* _SWFStream){
	
	_SWFStream->AppendTag( stagShowFrame, 0, 0 );	
}

/////////////////////////////////////////////////////////////////////////////
//  --------  FCTStartSound --------------------------------------------------

FCTStartSound::FCTStartSound(U16 _soundID, FSoundInfo* _soundInfo) {
	
	soundID = _soundID;
	soundInfo = _soundInfo;

}


FCTStartSound::~FCTStartSound(){
	
	delete soundInfo;

}



void FCTStartSound::WriteToSWFStream(FSWFStream* _SWFStream){
	
	FSWFStream body;
	
	body.WriteWord( (U32) soundID  );
	soundInfo->WriteToSWFStream(&body);
	
	_SWFStream->AppendTag( stagStartSound, body.Size(), &body );	
}
