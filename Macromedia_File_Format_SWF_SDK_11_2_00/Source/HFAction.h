// Copyright © 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu.
// First Created On 11/08/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: HFAction.h

	This header-file contains the declarations of high-level action-related classes.
	Parent classes are in the parentheses:

		class HFAction;
		class HFActionGetURL; (public HFAction)
		class HFActionPlay; (public HFAction)
		class HFActionStop; (public HFAction)
		class HFActionGoToFrame; (public HFAction)

****************************************************************************************/

#ifndef HFACTION_H_
#define HFACTION_H_

#include "FAction.h"
#include "FCT.h"

//! Abstract class of all high-level action classes.
/*!	
	\sa HFActionGetURL, HFActionPlay, HFActionStop, HFActionGoToFrame
*/
class HFAction
{
public:
	// Method for internal use.
	virtual void AddToActionCondition(FActionCondition* ac) = 0;

	// Method for internal use.
	virtual	void AddToAction(FCTDoAction* doAction) = 0;
};


//! Define a high-level GetURL action.
/*!	
	\sa HFAction
*/
class HFActionGetURL : public HFAction
{
public:
	//! Construct a GetURL action, open the URL in the same window.
	/*!	
		\param _url		A pointer to the string specifying URL.
	*/
	HFActionGetURL(char* _url);

	//! Construct a GetURL action, open the URL in the window specified by _target.
	/*!	
		\param _url		A pointer to the string specifying URL.
		\param _target	A pointer to the string specifying the target window.
	*/
	HFActionGetURL(char* _url, char* _target);

	// Method for internal use.
	void AddToActionCondition(FActionCondition* ac);

	// Method for internal use.
	void AddToAction(FCTDoAction* doAction);
private:
	char* url;
	char* target;
};


//! Define a high-level Play action.
/*!	
	\sa HFAction
*/
class HFActionPlay : public HFAction
{
public:
	// Method for internal use.
	void AddToActionCondition(FActionCondition* ac);

	// Method for internal use.
	void AddToAction(FCTDoAction* doAction);
};



//! Define a high-level Stop action.
/*!	
	\sa HFAction
*/
class HFActionStop : public HFAction
{
public:
	// Method for internal use.
	void AddToActionCondition(FActionCondition* ac);

	// Method for internal use.
	void AddToAction(FCTDoAction* doAction);
};



//! Define a high-level GoToFrame action.
/*!	
	\sa HFAction
*/
class HFActionGoToFrame : public HFAction
{
public:
	//! Construct a GoToFrame action.
	/*!	
		\param frame	The index of the frame to goto.
	*/
	HFActionGoToFrame( int frame );

	// Method for internal use.
	void AddToActionCondition(FActionCondition* ac);

	// Method for internal use.
	void AddToAction(FCTDoAction* doAction);
private:
	int frame;
};

#endif