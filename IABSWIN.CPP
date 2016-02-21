/***************************************************************/
/* Filename: iabswin.cpp                                       */
/*                                                             */
/* Purpose: Definition of classes IAbstractWindow and          */
/*          IAbsWinHandler.                                    */
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
   #define INCL_WINPOINTERS
   #define INCL_WINFRAMEMGR
   #include "os2.h"
   }

#ifndef _ITHREAD_
   #include <ithread.hpp>
#endif

#include "iabswin.hpp"

Boolean       IAbstractWindow::hasBeenRegistered = false;
unsigned long IAbstractWindow::minWindowData     = 4;

//----------------------------------------------------------------------------
// Method: IAbstractWindow::IAbstractWindow
//
// Description: Construct an IAbstractWindow from a class name 'winClassName',
//              class styles 'windowClassStyles', amount of extra memory
//              allocated per window 'extraDataBytes', window 'id', 'parent'
//              window, 'owner' window, 'initial' window rectangle, and
//              window 'style'.
//
// Notes: Register the PM class, throw an exception if registration fails.
//----------------------------------------------------------------------------
IAbstractWindow::IAbstractWindow(const IString& winClassName,
                                 unsigned long windowClassStyles,
                                 unsigned long extraDataBytes,
                                 unsigned long id,
                                 IWindow* parent,
                                 IWindow* owner,
                                 const IRectangle& initial,
                                 unsigned long style)
   : clsName(winClassName),
     clsStyle(windowClassStyles),
     exData(extraDataBytes + minWindowData)
   {
   if (!hasBeenRegistered)
      {
      // If class registration fails, throw an exception because
      // we can't survive
      if (WinRegisterClass(IThread::current().anchorBlock(),
                           clsName,
                           WinDefWindowProc,
                           clsStyle,
                           exData))
         {
         hasBeenRegistered = true;
         }
      else
         {
         // You can throw an exception here.
         }

      }

   // See if the class has already been registered or
   // was registered above.
   if (hasBeenRegistered)
      {
      // already registered, just create the window
      IWindowHandle handle(create(id,
                                  0,
                                  style,
                                  winClassName,
                                  parent->handle(),
                                  owner->handle(),
                                  initial,
                                  0,
                                  0));

      if (handle.isValid())
         {
         // successfully created the window, attach our handlers.
         IWindow::startHandlingEventsFor(handle);

         IResizeHandler::handleEventsFor(this);
         IPaintHandler::handleEventsFor(this);
         IMouseMoveHandler::handleEventsFor(this);

         IAbsWinHandler::handleEventsFor(this);
         }
      else
         {
         // You can throw an exception here.
         }
      }
   }

//----------------------------------------------------------------------------
// Method: IAbstractWindow::~IAbstractWindow
//
// Description: Destructor for IAbstractWindow.
//
// Notes: Empty destructor. May place trace information here to detect
//        destruction while debugging.
//----------------------------------------------------------------------------
IAbstractWindow::~IAbstractWindow()
   {
   }

//----------------------------------------------------------------------------
// Method: IAbstractWindow::windowClass
//
// Description: 'windowClass' returns the window class name specified
//              during contruction.
//----------------------------------------------------------------------------
IString IAbstractWindow::windowClass() const
   {
   return IString(clsName);
   }

//----------------------------------------------------------------------------
// Method: IAbstractWindow::windowClassStyle
//
// Description: 'windowClassStyle' returns the window class style bits
//              specified during construction.
//----------------------------------------------------------------------------
unsigned long IAbstractWindow::windowClassStyle() const
   {
   return clsStyle;
   }

//----------------------------------------------------------------------------
// Method: IAbstractWindow::windowDataBytes
//
// Description: 'windowDataBytes' returns the number of extra bytes each
//              window of this class has allocated.
//
// Notes: This number is a combination of the amount requested during
//        contruction plus the minimumWindowData().
//----------------------------------------------------------------------------
unsigned long IAbstractWindow::windowDataBytes() const
   {
   return exData;
   }

//----------------------------------------------------------------------------
// Method: IAbstractWindow::minimumWindowData
//
// Description: 'minimumWindowData' returns the constant amount of bytes
//              that are allocated for each window of this class. The
//              constant is 4 so that users of the class have access to
//              the offset at QWL_USER.
//----------------------------------------------------------------------------
unsigned long IAbstractWindow::minimumWindowData()
   {
   return minWindowData;
   }

//----------------------------------------------------------------------------
// Method: IAbstractWindow::paintWindow
//
// Description: 'paintWindow' is called in response to a paint event,
//              'evt', and simply clears the background.
//----------------------------------------------------------------------------
Boolean IAbstractWindow::paintWindow(IPaintEvent& evt)
   {
   evt.clearBackground();
   return true;
   }

//----------------------------------------------------------------------------
// Method: IAbstractWindow::mouseMove
//
// Description: 'mouseMove' is called in response to a mousemove event,
//              'evt'.
//----------------------------------------------------------------------------
Boolean IAbstractWindow::mouseMove(IMouseMoveEvent &evt)
   {
   IEventResult result(owner()->sendEvent(WM_CONTROLPOINTER,
                                          id(),
                                          WinQuerySysPointer(desktopWindow()->handle(),
                                                             SPTR_ARROW,
                                                             FALSE)));

   // If the event was received, change the pointer.
   if ((unsigned long)result)
      WinSetPointer(desktopWindow()->handle(), (unsigned long)result);

   return true;
   }

//----------------------------------------------------------------------------
// Method: IAbstractWindow::windowResize
//
// Description: 'windowResize' is called in response to a resize event,
//              'evt'.
//----------------------------------------------------------------------------
Boolean IAbstractWindow::windowResize(IResizeEvent& evt)
   {
   evt;
   return false;
   }

//----------------------------------------------------------------------------
// Method: IAbstractWindow::presParamChanged
//
// Description: 'presParamChanged' is called in response to a
//              WM_PRESPARAMCHANGED message or event, 'evt', and
//              invalidates the window.
//----------------------------------------------------------------------------
Boolean IAbstractWindow::presParamChanged(IEvent& evt)
   {
   evt;
   refresh();
   return true;
   }

Boolean IAbstractWindow::eraseBackground(IEvent& evt)
   {
   return false;
   }

Boolean IAbstractWindow::gainingFocus(IEvent& evt)
   {
   evt;
   return false;
   }

Boolean IAbstractWindow::losingFocus(IEvent& evt)
   {
   evt;
   return false;
   }

//------------------- IAbsWinHandler Definition Start ------------------------
IAbsWinHandler::IAbsWinHandler()
   : IHandler()
   {
   }

IAbsWinHandler::~IAbsWinHandler()
   {
   }

//----------------------------------------------------------------------------
// Method: IAbsWinHandler::dispatchHandlerEvent
//
// Description: 'dispatchHandlerEvent' receives an IEvent 'evt', examines
//              the contents and invokes a virtual function if the event
//              is recognized.
//----------------------------------------------------------------------------
Boolean IAbsWinHandler::dispatchHandlerEvent(IEvent& evt)
   {
   Boolean        fHandled = false;

   switch (evt.eventId())
      {
      case WM_PRESPARAMCHANGED:
         fHandled = presParamChanged(evt);
         break;

      case WM_ERASEBACKGROUND:
         fHandled = eraseBackground(evt);
         break;

      case WM_SETFOCUS:
         if ((unsigned long)evt.parameter2())
            fHandled = gainingFocus(evt);
         else
            fHandled = losingFocus(evt);
         break;
      }

   return fHandled;
   }

//-------------------- IAbsWinHandler Definition End -------------------------
