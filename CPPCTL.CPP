/***************************************************************/
/* Filename: cppctl.cpp                                        */
/*                                                             */
/* Purpose: Main source file for C++ control test app. Contains*/
/*          definition of MainFrame class.                     */
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
   #define INCL_WINFRAMEMGR
   #define INCL_WINPOINTERS
   #define INCL_DOSPROCESS
   #include "os2.h"
   }

#include "cppctl.hpp"

#ifndef _IAPP_
   #include <iapp.hpp>
#endif

int main(int argc, char *argv[])
   {
   MainFrame mainFrame;

   IApplication::current().run();

   return 0;
   }

//----------------------------------------------------------------------------
// Method: MainFrame::MainFrame
//
// Description: Construct our frame window, hard coding window IDs.
//----------------------------------------------------------------------------
MainFrame::MainFrame()
   : IFrameWindow(100),
     clientWin(101, this, this)
   {
   // clientWin's ID will be changed to FID_CLIENT when
   // it is set as the client
   setClient(&clientWin);

   // Attach the mouse move handler so we will be notified of the
   // controlPointer messages.
   IMouseMoveHandler::handleEventsFor(this);

   // Attach the NewControl handler so we will be notified of the
   // button1Click and button2Click messages.
   NewControlHandler::handleEventsFor(this);

   setFocus();
   show();
   }

//----------------------------------------------------------------------------
// Method: MainFrame::~MainFrame
//
// Description: Destructor for our frame window.
//----------------------------------------------------------------------------
MainFrame::~MainFrame()
   {
   }

//----------------------------------------------------------------------------
// Method: MainFrame::controlPointer
//
// Description: 'controlPointer' is called in response to a
//              WM_CONTROLPOINTER message/event, 'evt', being sent
//              from a control.
//----------------------------------------------------------------------------
Boolean MainFrame::controlPointer(IControlPointerEvent &evt)
   {
   Boolean rc = false;

   // See if the pointer is over the client window and if so, change the
   // pointer to an I-beam. Return true to say we handled the event.
   if (FID_CLIENT == evt.pointerOverId())
      {
      evt.setNewPointer(WinQuerySysPointer(desktopWindow()->handle(),
                                           SPTR_TEXT,
                                           FALSE));
      rc = true;
      }

   return rc;
   }

//----------------------------------------------------------------------------
// Method: MainFrame::button1Click
//
// Description: 'button1Click' is called in response to a NewControl
//              sending a button1 click event, 'evt'.
//----------------------------------------------------------------------------
Boolean MainFrame::button1Click(NewControlEvent& evt)
   {
   evt;

   //Just beep to recognize the message.
   DosBeep(1000, 500);

   return true;
   }

//----------------------------------------------------------------------------
// Method: MainFrame::button2Click
//
// Description: 'button2Click' is called in response to a NewControl
//              sending a button2 click event, 'evt'.
//----------------------------------------------------------------------------
Boolean MainFrame::button2Click(NewControlEvent& evt)
   {
   evt;

   //Just beep to recognize the message.
   DosBeep(500, 500);

   return true;
   }



