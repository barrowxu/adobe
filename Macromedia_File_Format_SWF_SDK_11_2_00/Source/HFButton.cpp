// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 11/05/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFButton.cpp

  This source file contains the definition for high-level button functions,

		Class						Member Function

	HFButton					HFButton(HFShape*, HFShape*, HFShape*, HFShape*);
								~HFButton();
								void QueueEvent(HFAction*, int);
								void AddToObjectList(std::list<FObj*>*);
								void AddEvent(int);

****************************************************************************************/

#include "HFButton.h"
#include "HFColors.h"
#include "FPrimitive.h"
#include "FDTButtons.h"
#include "FAction.h"
#include "HF3SDK.h"


//////////////////////////////////////////////////////////////////////////////////////
//  --------  HFButton  --------------------------------------------------------------

HFButton::HFButton(	HFShape* shape1, 
					HFShape* shape2, 
					HFShape* shape3, 
					HFShape* shape4
				  )
{
	shape[0] = shape1;
	shape[1] = shape2;
	shape[2] = shape3;
	shape[3] = shape4;
	ac = new FActionCondition();;
}



HFButton::~HFButton()
{
	delete ac;
}


void HFButton::QueueEvent(HFAction* action, int event)
{
	AddEvent( event );
	action->AddToActionCondition(ac);
}


void HFButton::AddToObjectList( std::list<FObj*> *objList, HFMovie* movie )
{
	int i;
	FMatrix *mx;
	FCXFormWAlpha *cxf;
	FButtonRecord2 *bRec;

	if ( !defineWritten )	// only write the define tag once!
	{
		// Add the four shapes button refering to.
		for (i = 0; i < 4; i++) 
		{
			shape[i]->ObjectIsEmbedded( true );
			shape[i]->AddToObjectList( objList, movie );
		}
		
		// Add the button itself.
		FDTDefineButton2 *buttonTag = new FDTDefineButton2(0); //0 flags a push button

	// 	objectID = buttonTag->ID();
		SetDefineTagId( buttonTag->ID() );

		for (i = 0; i < 4; i++) {
			mx = new FMatrix();
			cxf = new FCXFormWAlpha(false,false,0,0,0,0,0,0,0,0);
			bRec = new FButtonRecord2(	(i==HIT),(i==DOWN),(i==OVER),(i==UP),	// 
										shape[i]->DefineTagId(), 1,	// layer
										mx,				// geometry transformation matrix: empty
										cxf);			//    color transformation matrix: empty
			buttonTag->AddButtonRecord(bRec);
		}

		// Add action-condition record(s).
		buttonTag->AddActionCondition(ac);
		ac = 0;

		objList->push_back ( buttonTag );
	}
	AddPlaceObject2( objList, movie );
}

void HFButton::AddEvent(int event)
{
	switch (event){
	case MENU_DRAG_OUT:
		ac->AddCondition(OverDownToIdle);
		break;
	case MENU_DRAG_OVER:
		ac->AddCondition(IdleToOverDown);
		break;
	case PUSH_RELEASE_OUTSIDE:
		ac->AddCondition(OutDownToIdle);
		break;
	case PUSH_DRAG_OVER:
		ac->AddCondition(OutDownToOverDown);
		break;
	case PUSH_DRAG_OUT:
		ac->AddCondition(OverDownToOutDown);
		break;
	case RELEASE:
		ac->AddCondition(OverDownToOverUp);
		break;
	case PRESS:
		ac->AddCondition(OverUpToOverDown);
		break;
	case ROLL_OUT:
		ac->AddCondition(OverUpToIdle);
		break;
	case ROLL_OVER:
		ac->AddCondition(IdleToOverUp);
		break;
	default:
		break;
	}
}
