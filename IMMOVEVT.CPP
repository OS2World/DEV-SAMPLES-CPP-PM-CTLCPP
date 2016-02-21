/***************************************************************/
/* Filename: immovevt.cpp                                      */
/*                                                             */
/* Purpose: Definition of the IMouseMoveEvent class. These     */
/*          classes encapsulates several different types of    */
/*          mouse movement events, including WM_MOUSEMOVE,     */
/*          WM_CONTROLPOINTER, WM_BEGIN/ENDDRAG, and           */
/*          WM_BEGIN/ENDSELECT. An associated class is         */
/*          IMouseMoveHandler.                                 */
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
   #define INCL_WININPUT
   #define INCL_WINMESSAGEMGR
   #define INCL_WINPOINTERS
   #include <os2.h>
   }

#include "immovevt.hpp"

IMouseMoveEvent::IMouseMoveEvent(IEvent &evt)
   : IEvent(evt)
   {
   }

IMouseMoveEvent::~IMouseMoveEvent()
   {
   }

//----------------------------------------------------------------------------
// Method: IMouseMoveEvent::pointerPosition
//
// Description: 'pointerPosition' returns the x/y coordinate of the pointer
//               at the time the mouse move event occurred.
//----------------------------------------------------------------------------
IPoint IMouseMoveEvent::pointerPosition() const
   {
   return IPoint(parameter1().lowNumber(), parameter1().highNumber());
   }

//----------------------------------------------------------------------------
// Method: IMouseMoveEvent::hitTest
//
// Description: 'hitTest' returns 0 if a pointing device capture is
//              currently in progress, otherewise returns the result
//              of the WM_HITTEST message.
//----------------------------------------------------------------------------
IMouseMoveEvent::HitTest IMouseMoveEvent::hitTest() const
   {
   return IMouseMoveEvent::HitTest(parameter2().lowNumber());
   }

//----------------------------------------------------------------------------
// Method: IMouseMoveEvent::keyCodes
//
// Description: 'keyCodes' returns the keyboard control code, which reflects
//              the keyboard state at the time the mouse move was initiated.
//----------------------------------------------------------------------------
unsigned short IMouseMoveEvent::keyCodes() const
   {
   return parameter2().highNumber();
   }

//----------------------------------------------------------------------------
// Method: IMouseMoveEvent::currentPointerPosition
//
// Description: 'currentPointerPosition' returns the x/y coordinate of the
//               pointer at the time the method is invoked.
//
// Notes: The value returned by this method can be different (more current)
//        than the value returned by the pointerPosition method.
//        This method is static so can be called anytime.
//----------------------------------------------------------------------------
IPoint IMouseMoveEvent::currentPointerPosition()
   {
   POINTL ptl = {0, 0};
   WinQueryPointerPos(HWND_DESKTOP, &ptl);
   return IPoint(ptl);
   }

IControlPointerEvent::IControlPointerEvent(IEvent &evt)
   : IEvent(evt)
   {
   }

IControlPointerEvent::~IControlPointerEvent()
   {
   }

//----------------------------------------------------------------------------
// Method: IControlPointerEvent::pointerOverId
//
// Description: 'pointerOverId' returns the id of the control the pointer
//              is over.
//----------------------------------------------------------------------------
unsigned long IControlPointerEvent::pointerOverId() const
   {
   return parameter1();
   }

//----------------------------------------------------------------------------
// Method: IControlPointerEvent::currentPointer
//
// Description: 'currentPointer' returns the current pointer handle.
//----------------------------------------------------------------------------
IPointerHandle IControlPointerEvent::currentPointer() const
   {
   return IPointerHandle(parameter2());
   }

//----------------------------------------------------------------------------
// Method: IControlPointerEvent::setNewPointer
//
// Description: 'setNewPointer' sets the pointer to 'ptrHandle'.
//----------------------------------------------------------------------------
Boolean IControlPointerEvent::setNewPointer(const IPointerHandle &ptrHandle)
   {
   setResult(IEventResult((unsigned long)ptrHandle));
   return true;
   }

IMouseDragSelectEvent::IMouseDragSelectEvent(IEvent &evt)
   : IEvent(evt)
   {
   }

IMouseDragSelectEvent::~IMouseDragSelectEvent()
   {
   }

//----------------------------------------------------------------------------
// Method: IMouseDragSelectEvent::pointerInitiated
//
// Description: 'pointerInitiated' returns true if the pointer is being
//              dragged into the window, false otherwise.
//----------------------------------------------------------------------------
Boolean IMouseDragSelectEvent::pointerInitiated() const
   {
   return !parameter2().asUnsignedLong();
   }

//----------------------------------------------------------------------------
// Method: IMouseDragSelectEvent::pointerPosition
//
// Description: 'pointerPosition' returns the x/y coordinate of the pointer
//               at the time the mouse drag event occurred.
//----------------------------------------------------------------------------
IPoint IMouseDragSelectEvent::pointerPosition() const
   {
   // If pointer is being dragged into the window, return those
   // coordinates, otherwise return (0,0).
   if (pointerInitiated())
      {
      return IPoint(parameter1().lowNumber(), parameter1().highNumber());
      }
   else
      return IPoint();
   }


