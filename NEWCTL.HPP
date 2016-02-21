#ifndef _NEWCTL_
   #define _NEWCTL_

/***************************************************************/
/* Filename: newctl.hpp                                        */
/*                                                             */
/* Purpose: Contains declaration of NewControl class which is  */
/*          the client area of the main window.                */
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

#ifndef _IABSWIN_
   #include "iabswin.hpp"
#endif

#ifndef _ICOLOR_
   #include "icolor.hpp"
#endif

#ifndef _IMCHDR_
   #include <imchdr.hpp>
#endif

// Align classes on 4 byte boundary
#pragma pack(4)

class NewControl : public IAbstractWindow,
                   public IMouseClickHandler
   {
   friend class NewControlHandler;

   public:
      class Style;   // forward declaration for nested class

      NewControl(unsigned long id,
                 IWindow* parent,
                 IWindow* owner,
                 const IRectangle& initial = IRectangle(),
                 const Style& style = defaultStyle());

      virtual ~NewControl();

/*---------------------------------- Style -------------------------------------
| The following functions provide a means to set and query NewControl styles:  |
|                                                                              |
|   Style - Nested class that provides static members that define the set      |
|           of valid control styles.  These styles can be used in conjunction  |
|           with the styles defined by the IControl::Style nested class. For   |
|           example, you could define an instance of the NewControl::Style     |
|           class and initialize it like:                                      |
|             NewControl::Style                                                |
|               style = NewControl::classDefaultStyle |                        |
|                       IWindow::saveBits;                                     |
|           An object of this type is provided when NewControl is created.  A  |
|           customizable default is used if no styles are specified.  Once     |
|           the object is constructed, NewControl and IWindow member functions |
|           can be used to set or query the object's style.                    |
|                                                                              |
|           The declaration of the Style nested class is generated             |
|           by the INESTEDBITFLAGCLASSDEF2 macro.                              |
|                                                                              |
| The valid NewControl style is:                                               |
|   classDefaultStyle - The original default style for this class, which is    |
|                       IWindow::visible                                       |
|                                                                              |
| The following functions provide a means of getting and setting the default   |
| style for new objects of this class:                                         |
|   defaultStyle    - Returns the current default style, which is the same as  |
|                     classDefaultStyle unless setDefaultStyle has been        |
|                     called.                                                  |
|   setDefaultStyle - Sets the default style for all subsequent NewControls.   |
------------------------------------------------------------------------------*/
      // Name the nested class "Style" and combine IControl and IWindow
      // styles with NewControl.
      INESTEDBITFLAGCLASSDEF2(Style, NewControl, IControl, IWindow);

      static const Style notifyMB1;
      static const Style notifyMB2;

      static const Style classDefaultStyle;

      static Style defaultStyle();

      static void setDefaultStyle(const Style& style);


/*------------------------------- Enumerations ---------------------------------
| The following enumerations are defined:                                      |
|   ColorArea - Used to specify an area of the control that can be affected    |
|               with color:                                                    |
|                 background - The background color.                           |
|                 foreground - The text color.                                 |
|                 hilite     - The color of the hilited portion of the text    |
------------------------------------------------------------------------------*/
      enum ColorArea
         {
         background     = 3,   // PP_BACKGROUNDCOLOR
         foreground     = 1,   // PP_FOREGROUNDCOLOR
         hilite         = 5    // PP_HILITEFOREGROUNDCOLOR
         };

/*---------------------------------- Color -------------------------------------
| These functions set and query the color of the control:                      |
|   setColor  - Sets the specified color of the control.                       |
|   color     - Returns the specified color of the control.                    |
------------------------------------------------------------------------------*/
      NewControl &setColor(ColorArea area, const IColor& color);

      IColor color(ColorArea area) const;

   protected:
      virtual Boolean paintWindow(IPaintEvent& evt);
      virtual Boolean windowResize(IResizeEvent& evt);
      virtual Boolean gainingFocus(IEvent& evt);
      virtual Boolean losingFocus(IEvent& evt);
      virtual Boolean mouseClicked(IMouseClickEvent& evt);

   private:
      NewControl& establishColor(IColor& clr,
                                 NewControl::ColorArea clrArea,
                                 const IColor& defClr);

      static Style currentDefaultStyle;

      static const char* newControlClass;
      static const unsigned long newControlClassStyle;

      static const char* dummyText;

      static const IColor defclrBackground;
      static const IColor defclrForeground;
      static const IColor defclrHilite;

      long clicks;            // number of MB1 clicks in control
      long cx;                // control width in pels
      long cy;                // control height in pels
   };

INESTEDBITFLAGCLASSFUNCS(Style, NewControl);

// Resume compiler default packing
#pragma pack()

#endif //#ifndef _NEWCTL_
