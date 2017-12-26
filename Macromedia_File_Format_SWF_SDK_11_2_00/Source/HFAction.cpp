// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 11/08/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFAction.cpp

  This source file contains the definition for all high-level action-related functions,
  grouped by classes:

		Class						Member Function
  
	HFActionGetURL				HFActionGetURL(char*);
								HFActionGetURL(char*, char*);
								void AddToActionCondition(FActionCondition*);
								void AddToAction(FCTDoAction*);

	HFActionPlay				void AddToActionCondition(FActionCondition*);
								void AddToAction(FCTDoAction*);

	HFActionStop				void AddToActionCondition(FActionCondition*);
								void AddToAction(FCTDoAction*);

	HFActionGoToFrame			HFActionGoToFrame(int);
								void AddToActionCondition(FActionCondition*);
								void AddToAction(FCTDoAction*);

****************************************************************************************/

#include "HFAction.h"

//////////////////////////////////////////////////////////////////////////////////////
//  --------  HFActionGetURL  --------------------------------------------------------


HFActionGetURL::HFActionGetURL(char* _url)
{	
	url		= _url;
	target	= "";
}

HFActionGetURL::HFActionGetURL(char* _url, char* _target)
{	
	url		= _url;
	target	= _target;
}

void HFActionGetURL::AddToActionCondition(FActionCondition* ac)
{	
	ac->AddActionRecord(	new FActionGetURL(	new FString((U8*)url), 
												new FString((U8*)target)));		
}

void HFActionGetURL::AddToAction(FCTDoAction* doAction)
{	doAction->AddAction(	new FActionGetURL(	new FString((U8*)url), 
												new FString((U8*)target)));		
}

//////////////////////////////////////////////////////////////////////////////////////
//  --------  HFActionPlay  -----------------------------------------------------------

void HFActionPlay::AddToActionCondition(FActionCondition* ac)
{	
	ac->AddActionRecord(	new FActionPlay());		
}

void HFActionPlay::AddToAction(FCTDoAction* doAction)
{	
	doAction->AddAction(new FActionPlay());		
}		



//////////////////////////////////////////////////////////////////////////////////////
//  --------  HFActionStop  ----------------------------------------------------------

void HFActionStop::AddToActionCondition(FActionCondition* ac)
{	
	ac->AddActionRecord(new FActionStop());		
}

void HFActionStop::AddToAction(FCTDoAction* doAction)
{		
	doAction->AddAction(new FActionStop());		
}		



//////////////////////////////////////////////////////////////////////////////////////
//  --------  HFActionGoToFrame  -----------------------------------------------------

HFActionGoToFrame::HFActionGoToFrame( int f )
{
	frame = f;
}

void HFActionGoToFrame::AddToActionCondition(FActionCondition* ac)
{	
	ac->AddActionRecord(new FActionGotoFrame( frame ));		
}

void HFActionGoToFrame::AddToAction(FCTDoAction* doAction)
{		
	doAction->AddAction(new FActionGotoFrame( frame ));		
}		

