/***************************************************************/
/* Filename: immovhdr.cpp                                      */
/*                                                             */
/* Purpose: Definition of IMouseMoveHandler class.             */
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
extern "C"
   {
   #define INCL_WININPUT
   #define INCL_WINMESSAGEMGR
   #include <os2.h>
   }

#ifndef _IMMOVEVT_
   #include "immovevt.hpp"
#endif

#include "immovhdr.hpp"

IMouseMoveHandler::IMouseMoveHandler()
   : IHandler()
   {
   }

IMouseMoveHandler::~IMouseMoveHandler()
   {
   }

//----------------------------------------------------------------------------
// Method: IMouseMoveHandler::dispatchHandlerEvent
//
// Description: 'dispatchHandlerEvent' receives an IEvent 'evt', examines
//              the contents and invokes a virtual function if the event
//              is recognized.
//----------------------------------------------------------------------------
Boolean IMouseMoveHandler::dispatchHandlerEvent(IEvent &evt)
   {
   Boolean        fHandled = false;

   switch (evt.eventId())
      {
      case WM_MOUSEMOVE:
         {
         IMouseMoveEvent mouEvt(evt);
         fHandled = mouseMove(mouEvt);
         evt.setResult(mouEvt.result());
         break;
         }

      case WM_CONTROLPOINTER:
         {
         IControlPointerEvent ctlEvt(evt);
         fHandled = controlPointer(ctlEvt);
         evt.setResult(ctlEvt.result());
         break;
         }

      case WM_BEGINDRAG:
      case WM_ENDDRAG:
      case WM_BEGINSELECT:
      case WM_ENDSELECT:
         {
         IMouseDragSelectEvent drgEvt(evt);
         switch (evt.eventId())
            {
            case WM_BEGINDRAG:
               fHandled = beginDrag(drgEvt);
               break;

            case WM_ENDDRAG:
               fHandled = endDrag(drgEvt);
               break;

            case WM_BEGINSELECT:
               fHandled = beginSelect(drgEvt);
               break;

            case WM_ENDSELECT:
               fHandled = endSelect(drgEvt);
               break;
            }
         evt.setResult(drgEvt.result());
         break;
         }

      }

   return fHandled;
   }

Boolean IMouseMoveHandler::mouseMove(IMouseMoveEvent &evt)
   {
   evt;
   return false;
   }

Boolean IMouseMoveHandler::controlPointer(IControlPointerEvent &evt)
   {
   evt;
   return false;
   }

Boolean IMouseMoveHandler::beginDrag(const IMouseDragSelectEvent& evt)
   {
   evt;
   return false;
   }

Boolean IMouseMoveHandler::endDrag(const IMouseDragSelectEvent& evt)
   {
   evt;
   return false;
   }

Boolean IMouseMoveHandler::beginSelect(const IMouseDragSelectEvent& evt)
   {
   evt;
   return false;
   }

Boolean IMouseMoveHandler::endSelect(const IMouseDragSelectEvent& evt)
   {
   evt;
   return false;
   }
