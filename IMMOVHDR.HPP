#ifndef _IMMOVHDR_
   #define _IMMOVHDR_
/***************************************************************/
/* Filename: immovhdr.hpp                                      */
/*                                                             */
/* Purpose: Declaration of IMouseMoveHandler class.            */
/*          This class handles several different types         */
/*          of mouse movement events, including WM_MOUSEMOVE,  */
/*          WM_CONTROLPOINTER, WM_BEGIN/ENDDRAG, and           */
/*          WM_BEGIN/ENDSELECT. Associated classes are         */
/*          IMouseMoveEvent, IControlPointerEvent, and         */
/*          IMouseDragSelectEvent.                             */
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

#ifndef _IHANDLER_
   #include <ihandler.hpp>
#endif

class IMouseMoveEvent;
class IControlPointerEvent;
class IMouseDragSelectEvent;

// Align classes on 4 byte boundary
#pragma pack(4)

class IMouseMoveHandler : public IHandler
   {
   typedef IHandler Inherited;

   public:
      IMouseMoveHandler();
      virtual ~IMouseMoveHandler();

   protected:
      virtual Boolean dispatchHandlerEvent(IEvent& evt);
      virtual Boolean mouseMove(IMouseMoveEvent &evt);
      virtual Boolean controlPointer(IControlPointerEvent &evt);

      virtual Boolean beginDrag(const IMouseDragSelectEvent& evt);
      virtual Boolean endDrag(const IMouseDragSelectEvent& evt);
      virtual Boolean beginSelect(const IMouseDragSelectEvent& evt);
      virtual Boolean endSelect(const IMouseDragSelectEvent& evt);

   };

// Resume compiler default packing
#pragma pack()

#endif //#ifndef _IMMOVHDR_
