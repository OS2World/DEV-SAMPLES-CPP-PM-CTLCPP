#ifndef _CPPCTL_
   #define _CPPCTL_

/***************************************************************/
/* Filename: cppctl.hpp                                        */
/*                                                             */
/* Purpose: Contains declaration of MainFrame class which is   */
/*          the application's main window.                     */
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

#ifndef _IFRAME_
   #include <iframe.hpp>
#endif

#ifndef _NEWCTL_
   #include "newctl.hpp"
#endif

#ifndef _NEWCTHDR_
   #include "newcthdr.hpp"
#endif

#ifndef _IMMOVHDR_
   #include "immovhdr.hpp"
#endif

#ifndef _IMMOVEVT_
   #include "immovevt.hpp"
#endif

// Align classes on 4 byte boundary
#pragma pack(4)

class MainFrame : public IFrameWindow,
                  public IMouseMoveHandler,
                  public NewControlHandler
   {
   public:
      MainFrame();

      virtual ~MainFrame();

   protected:
      virtual Boolean controlPointer(IControlPointerEvent &evt);
      virtual Boolean button1Click(NewControlEvent& evt);
      virtual Boolean button2Click(NewControlEvent& evt);

   private:
      NewControl clientWin;

   };


// Resume compiler default packing
#pragma pack()

#endif //#ifndef _CPPCTL_
