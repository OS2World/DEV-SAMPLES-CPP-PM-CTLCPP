#ifndef _MCTLEVT_
   #define _MCTLEVT_

/***************************************************************/
/* Filename: mctlevt.hpp                                       */
/*                                                             */
/* Purpose: The declaration of MControlEvent class. This class */
/*          is an extension of the IControlEvent class. Event  */
/*          classes which wrap WM_CONTROL messages should      */
/*          inherit from this class as opposed to IControlEvent*/
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

#ifndef _ICTLEVT_
   #include <ictlevt.hpp>
#endif

#ifndef _IHANDLE_
   #include <ihandle.hpp>
#endif

#ifndef _ISTRING_
   #include <istring.hpp>
#endif

// Align classes on 4 byte boundary
#pragma pack(4)

//-------------------------------------------------------------------
// We've extended IControlEvent to return the control window's
// handle and class name. When we get a WM_CONTROL msg (wrapped
// by MControlEvent) we need to distinguish what class sent the
// event in the handler code. This way we won't mistakenly intercept
// control messages in the wrong handler.
//-------------------------------------------------------------------
class MControlEvent : public IControlEvent
   {
   public:
      MControlEvent(IEvent& evt);
      virtual ~MControlEvent();

      virtual IWindowHandle controlHandle() const;
      virtual IString controlClassName() const;
   };

// Resume compiler default packing
#pragma pack()


#endif //#ifndef _MCTLEVT_


