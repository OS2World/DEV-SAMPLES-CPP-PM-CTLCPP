#ifndef _NEWCTHDR_
   #define _NEWCTHDR_
/***************************************************************/
/* Filename: newcthdr.hpp                                      */
/*                                                             */
/* Purpose: Decalaration of teh NewControlHandler class.       */
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

#ifndef _NEWCTEVT_
   #include "newctevt.hpp"
#endif

// Align classes on 4 byte boundary
#pragma pack(4)

class NewControlHandler : public IHandler
   {
   public:
      NewControlHandler();
      virtual ~NewControlHandler();

   protected:
      virtual Boolean dispatchHandlerEvent(IEvent& evt);
      virtual Boolean button1Click(NewControlEvent& evt);
      virtual Boolean button2Click(NewControlEvent& evt);
   };

// Resume compiler default packing
#pragma pack()

#endif //#ifndef _NEWCTHDR_

