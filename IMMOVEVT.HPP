#ifndef _IMMOVEVT_
   #define _IMMOVEVT_
/***************************************************************/
/* Filename: immovevt.hpp                                      */
/*                                                             */
/* Purpose: Declaration of IMouseMoveEvent,                    */
/*          IControlPointerEvent, and IMouseDragSelectEvent.   */
/*          These classes encapsulate several different types  */
/*          of mouse movement events, including WM_MOUSEMOVE,  */
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

#ifndef _IEVENT_
   #include <ievent.hpp>
#endif

#ifndef _IHANDLE_
   #include <ihandle.hpp>
#endif

#ifndef _IPOINT_
   #include <ipoint.hpp>
#endif

// Align classes on 4 byte boundary
#pragma pack(4)


//----------------------------------------------------------------------------
// IMouseMoveEvent
//
// This class encapsulates the WM_MOUSEMOVE message. A static method which
// returns the current pointer position is also included.
//----------------------------------------------------------------------------
class IMouseMoveEvent : public IEvent
   {
   public:
      IMouseMoveEvent(IEvent &evt);
      virtual ~IMouseMoveEvent();


      IPoint pointerPosition() const;

      enum HitTest
         {
         normal      =  0,
         transparent = -1,
         discard     = -2,
         error       = -3
         };

      HitTest hitTest() const;

      unsigned short keyCodes() const;

      static IPoint currentPointerPosition();
   };

//----------------------------------------------------------------------------
// IControlPointerEvent
//
// This class encapsulates the WM_CONTROLPOINTER message. There are methods
// to query/set the pointer and to query the window id of the control under
// the pointer.
//----------------------------------------------------------------------------
class IControlPointerEvent : public IEvent
   {
   typedef IEvent Inherited;

   public:
      IControlPointerEvent(IEvent &evt);
      virtual ~IControlPointerEvent();

      unsigned long pointerOverId() const;
      IPointerHandle currentPointer() const;
      Boolean setNewPointer(const IPointerHandle &ptrHandle);
   };

//----------------------------------------------------------------------------
// IMouseDragSelectEvent
//
// This class encapsulates the WM_BEGINDRAG and WM_ENDDRAG messages. There
// are methods to get the pointer position and see if the pointer is being
// dragged into the window.
//----------------------------------------------------------------------------
class IMouseDragSelectEvent : public IEvent
   {
   typedef IEvent Inherited;

   public:
      IMouseDragSelectEvent(IEvent& evt);
      virtual ~IMouseDragSelectEvent();

      Boolean pointerInitiated() const;
      IPoint pointerPosition() const;

   };

// Resume compiler default packing
#pragma pack()

#endif //#ifndef _IMMOVEVT_
