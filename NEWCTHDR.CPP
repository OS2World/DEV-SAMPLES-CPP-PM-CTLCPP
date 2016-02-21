/***************************************************************/
/* Filename: newcthdr.cpp                                      */
/*                                                             */
/* Purpose: Definition of the NewControlHandler class.         */
/*                                                             */
/* Program name: cppctl.exe     Title: C++ PM Control Test App */
/* OS/2 Developer Magazine, Issue: Sept. '94, page             */
/* Article title: Writing OS/2 PM Controls in C++              */
/* Authors: Eric Snell and Lori Ruffing                        */
/*                                                             */
/* Description: This example shows how to implement an OS/2 PM */
/*              control window in C++.                         */
/*                                                             */
/* Program Requirements: This example requires the IBM C Set++ */
/*                       compiler and libraries.               */
/***************************************************************/

extern "C"
   {
   #include <string.h>
   #define INCL_WINWINDOWMGR
   #include <os2.h>
   }

#include "newcthdr.hpp"

#ifndef _NEWCTL_
   #include "newctl.hpp"
#endif

NewControlHandler::NewControlHandler()
   : IHandler()
   {
   }

NewControlHandler::~NewControlHandler()
   {
   }

//----------------------------------------------------------------------------
// Method: NewControlHandler::dispatchHandlerEvent
//
// Description: 'dispatchHandlerEvent' receives an IEvent 'evt', examines
//              the contents and invokes a virtual function if the event
//              is recognized.
//----------------------------------------------------------------------------
Boolean NewControlHandler::dispatchHandlerEvent(IEvent& evt)
   {
   Boolean fHandled = false;
   NewControlEvent nEvt(evt);

   if (nEvt.eventId() == WM_CONTROL)
      {
      // Ensure that a NewControl window sent us this msg by comparing
      // the class name from the event with the NewControl class name.
      if (!strcmp(nEvt.controlClassName(), NewControl::newControlClass))
         {
         if (IMouseClickEvent::button1 == nEvt.mouseNumber())
            fHandled = button1Click(nEvt);
         else if (IMouseClickEvent::button2 == nEvt.mouseNumber())
            fHandled = button2Click(nEvt);

         if (fHandled)
            evt.setResult(nEvt.result());
         }
      }

   return fHandled;
   }

//--------------------------------------------------------------------
// Provide default "do nothing" implementations of the handler's
// virtual functions. Another method would be to make them
// pure virtual to force the user to override them.
//--------------------------------------------------------------------

Boolean NewControlHandler::button1Click(NewControlEvent& evt)
   {
   evt;
   return false;
   }

Boolean NewControlHandler::button2Click(NewControlEvent& evt)
   {
   evt;
   return false;
   }
