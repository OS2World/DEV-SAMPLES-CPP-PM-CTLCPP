/***************************************************************/
/* Filename: mctlevt.cpp                                       */
/*                                                             */
/* Purpose: Definition of the MControlEvent class.             */
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
   #define INCL_WINWINDOWMGR
   #include <os2.h>
   }

#ifndef _IWINDOW_
   #include <iwindow.hpp>
#endif

#include "mctlevt.hpp"

MControlEvent::MControlEvent(IEvent& evt)
   : IControlEvent(evt)
   {
   }

MControlEvent::~MControlEvent()
   {
   }

//----------------------------------------------------------------------------
// Method: MControlEvent::controlHandle
//
// Description: 'controlHandle' returns the window handle of the control
//----------------------------------------------------------------------------
IWindowHandle MControlEvent::controlHandle() const
   {
   IWindow* pwndControl = controlWindow();

   // The handler is either attached to the control generating
   // the WM_CONTROL message or to its owner.  If
   // IControlEvent::controlWindow returns 0, this must mean we
   // have a non-wrappered control with a wrappered owner
   // window and that the handler is attached to the owner
   // window.  This case is supported only if the owner of the
   // control is also the control's parent (this is in order
   // for handleWithId to work).

   if (pwndControl)
      {                           // in IWindowInfo list
      return pwndControl->handle();
      }
   else
      {
      return IWindow::handleWithId(controlId(), handle());
      }
   }

//----------------------------------------------------------------------------
// Method: MControlEvent::controlClassName
//
// Description: 'controlClassName' returns the class name of the control
//              based on the handle.
//----------------------------------------------------------------------------
IString MControlEvent::controlClassName() const
   {
   IWindowHandle hwnd(controlHandle());
   IString rc;

   if (hwnd.isValid())
      {
      // a little ugly magic stolen from ICLUI
      IString temp;
      unsigned len = 0;
      do
         {
         temp = IString( 0, len + 16 );
         len = WinQueryClassName(hwnd, temp.length()+1, temp);
         }
      while (len == temp.length());
      rc = temp;
      }

   return rc;
   }

