#ifndef _IABSWIN_
   #define _IABSWIN_
/***************************************************************/
/* Filename: iabswin.hpp                                       */
/*                                                             */
/* Purpose: Declaration of classes IAbstractWindow and         */
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

#ifndef _ICONTROL_
   #include <icontrol.hpp>
#endif

#ifndef _ISTRING_
   #include <istring.hpp>
#endif

#ifndef _IPAINHDR_
   #include <ipainhdr.hpp>
#endif

#ifndef _ISIZEHDR_
   #include <isizehdr.hpp>
#endif

#ifndef _IMMOVHDR_
   #include "immovhdr.hpp"
#endif

// Align classes on 4 byte boundary
#pragma pack(4)

// We need a handler for various messages we want to handle. To
// split the msgs out into various handlers is really more work
// than we want to do and we don't see much reuse outside of
// IAbstractWindow.
class IAbsWinHandler : public IHandler
   {
   public:
      IAbsWinHandler();
      virtual ~IAbsWinHandler();

   protected:
      virtual Boolean dispatchHandlerEvent(IEvent& evt);
      virtual Boolean presParamChanged(IEvent& evt) = 0;
      virtual Boolean eraseBackground(IEvent& evt) = 0;
      virtual Boolean gainingFocus(IEvent &evt) = 0;
      virtual Boolean losingFocus(IEvent &evt) = 0;
   };


//---------------------------------------------------------------------------
// IAbstractWindow
//
// This class is an abstract class which should be used as the base of
// new PM controls. This class handles the registration of the PM class
// and alleviates some of the problems associated with inheriting from
// a preexisting control such as ICanvas.
//
// The constructor of this class is protected since users should not create
// an instance of the class, but subclasses do need to invoke the
// constructor.
//---------------------------------------------------------------------------
class IAbstractWindow : public IControl,
                        protected IPaintHandler,
                        protected IResizeHandler,
                        protected IMouseMoveHandler,
                        protected IAbsWinHandler
   {
   public:
//------------------------------- Contructor --------------------------------
// The constructor for this class accepts a class name, class styles, and
// the amount of extra bytes that should be allocated for each window
// of this class (please see WinRegisterClass in the OS/2 toolkit for more
// information). The constructor also accepts the parameters usually
// associated with window construction in ICLUI (see IWindow::create and
// WinCreateWindow for more info).
//
// This constructor will register the window class with PM if the class
// has not already been registered. A ??? exception is thrown if window
// class registration fails.
//---------------------------------------------------------------------------
      IAbstractWindow(const IString& windowClassName,
                      unsigned long windowClassStyles,
                      unsigned long extraDataBytes,
                      unsigned long id,
                      IWindow* parent,
                      IWindow* owner,
                      const IRectangle& initial = IRectangle(),
                      unsigned long style = 0);

      virtual ~IAbstractWindow();

//--------------------------- Class Information -----------------------------
// windowClass       - Returns the window class name passed on construction.
// windowClassStyle  - Returns the window class style passed on contruction.
// windowDataBytes   - Returns the number of data bytes requested during
//                     construction, plus the minimumWindowData(). The
//                     data bytes are commonly referred to as "window words".
// minimumWindowData - Returns the minimum amount of "window words"
//                     (in bytes) that are allocated for windows of this
//                     class. These window words are meant for user use
//                     and should not be used by subclasses of this class.
//
// Notes:
//   Window words can be set/retrieved using the IWindow methods
//   windowUShort, windowULong, and setWindowData.
//---------------------------------------------------------------------------
      virtual IString windowClass() const;
      virtual unsigned long windowClassStyle() const;
      virtual unsigned long windowDataBytes() const;
      static unsigned long minimumWindowData();

   protected:
      virtual Boolean paintWindow(IPaintEvent& evt);
      virtual Boolean mouseMove(IMouseMoveEvent &evt);
      virtual Boolean windowResize(IResizeEvent& evt);
      virtual Boolean presParamChanged(IEvent& evt);
      virtual Boolean eraseBackground(IEvent& evt);
      virtual Boolean gainingFocus(IEvent &evt);
      virtual Boolean losingFocus(IEvent &evt);

   private:
      IAbstractWindow(const IAbstractWindow&);
      IAbstractWindow& operator = (const IAbstractWindow&);

      static Boolean       hasBeenRegistered;
      static unsigned long minWindowData;

      IString       clsName;
      unsigned long clsStyle;
      unsigned long exData;
   };

// Resume compiler default packing
#pragma pack()

#endif //#ifndef _IABSWIN_
