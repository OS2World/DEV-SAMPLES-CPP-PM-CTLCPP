#ifndef _NEWCTEVT_
   #define _NEWCTEVT_
/***************************************************************/
/* Filename: newctevt.hpp                                      */
/*                                                             */
/* Purpose: Declaration of NewControlEvent class.              */
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

#ifndef _IMCEVT_
   #include "imcevt.hpp"
#endif

#ifndef _MCTLEVT_
   #include "mctlevt.hpp"
#endif

// Align classes on 4 byte boundary
#pragma pack(4)

class NewControlEvent : public MControlEvent
   {
   public:
      NewControlEvent(IEvent &evt);
      virtual ~NewControlEvent();

      IMouseClickEvent::MouseNumber mouseNumber() const;

   };

// Resume compiler default packing
#pragma pack()

#endif //#ifndef _NEWCTEVT_
