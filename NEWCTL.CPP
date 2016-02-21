/***************************************************************/
/* Filename: newctl.cpp                                        */
/*                                                             */
/* Purpose: Main source file for C++ control NewControl.       */
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
   #define INCL_WINSYS
   #define INCL_WINWINDOWMGR
   #define INCL_GPICONTROL
   #define INCL_GPILOGCOLORTABLE
   #define INCL_GPIPRIMITIVES
   #include <os2.h>
   }

#ifndef _IEXCEPT_
   #include <iexcept.hpp>
#endif

#define MIN(a, b) ( ( (a) <= (b) ) ? (a) : (b) )
#define MAX(a, b) ( ( (a) >= (b) ) ? (a) : (b) )

#include "newctl.hpp"

// Class variables and constants
const NewControl::Style NewControl::notifyMB1 = 1;
const NewControl::Style NewControl::notifyMB2 = (1 << 1);

const NewControl::Style NewControl::classDefaultStyle =
   IWindow::visible | notifyMB1 | notifyMB2;

NewControl::Style NewControl::currentDefaultStyle =
   NewControl::classDefaultStyle;

// Define the NewControl class name for use in constructing IAbstractWindow
const char* NewControl::newControlClass = "NewControlClass";

// Define the the class style to be CS_SIZEREDRAW so that the text in
// the control will be scaled to the window size.
const unsigned long NewControl::newControlClassStyle = CS_SIZEREDRAW;

// Define the text to be displayed in the control.
const char* NewControl::dummyText = "Mouse clicks: ";

// Define the default colors for background, foreground, and hilite.
const IColor NewControl::defclrBackground(IColor::paleGray);
const IColor NewControl::defclrForeground(IColor::blue);
const IColor NewControl::defclrHilite(IColor::red);

//----------------------------------------------------------------------------
// Method: NewControl::establishColor
//
// Description: 'establishColor' sets the the logical color table
//              for the hps into RGB mode and sets 'clr' to the
//              color value for 'clrArea' or 'defClr' if there
//              is an exception.
//----------------------------------------------------------------------------
inline NewControl& NewControl::establishColor(IColor& clr,
                                              NewControl::ColorArea clrArea,
                                              const IColor& defClr)
   {
   // Need to bracket the call with try/catch since an exception will
   // be thrown if someone removed the presparam.
   try
      {
      clr = color(clrArea);
      }
   catch (IException& exc)
      {
      // Reassign default to make sure it wasn't hosed up somehow.
      clr = defClr;
      }

   return *this;
   }

//----------------------------------------------------------------------------
// Method: NewControl::NewControl
//
// Description: 'NewControl' is the constructor for the NewControl class.
//              It takes all the standard window creation parameters
//              plus the class name, class style, and extra window words.
//----------------------------------------------------------------------------
NewControl::NewControl(unsigned long id,
                       IWindow* parent,
                       IWindow* owner,
                       const IRectangle& initial,
                       const Style& style)
   : IAbstractWindow(newControlClass,
                     newControlClassStyle,
                     0,
                     id,
                     parent,
                     owner,
                     initial,
                     style.asUnsignedLong()),
     clicks(0),
     cx(initial.width()),
     cy(initial.height())
   {
   // Set color presparams to try to avoid exceptions being
   // thrown.
   setColor(background, defclrBackground);
   setColor(foreground, defclrForeground);
   setColor(hilite, defclrHilite);

   // Attach the mouse click handler because we want to be
   // notified of any click.
   IMouseClickHandler::handleEventsFor(this);
   }

//----------------------------------------------------------------------------
// Method: NewControl::~NewControl
//
// Description: '~NewControl' is the destructor for the NewControl class.
//----------------------------------------------------------------------------
NewControl::~NewControl()
   {
   }

NewControl::Style NewControl::defaultStyle()
   {
   return currentDefaultStyle;
   }

void NewControl::setDefaultStyle(const Style& style)
   {
   currentDefaultStyle = style;
   }

NewControl& NewControl::setColor(ColorArea area, const IColor& color)
   {
   IWindow::setColor(area, color);
   return *this;
   }

IColor NewControl::color(ColorArea area) const
   {
   return IWindow::color(area);
   }

//----------------------------------------------------------------------------
// Method: NewControl::paintWindow
//
// Description: 'paintWindow' is called in response to a paint event, 'evt'.
//              It establishes the colors to paint as well as determines
//              how large and where to draw the text.
//----------------------------------------------------------------------------
Boolean NewControl::paintWindow(IPaintEvent& evt)
   {
   IColor clrBackground(defclrBackground);
   IColor clrForeground(defclrForeground);
   IColor clrHilite(defclrHilite);

   IPresSpaceHandle hps = evt.presSpaceHandle();

   // Should make a separate method which sets the logical
   // color table for the HPS into RGB mode and sets all our
   // colors. Also, colors could be cached in private data
   // and only updated when presparams change.
   establishColor(clrBackground, background, defclrBackground);
   establishColor(clrForeground, foreground, defclrForeground);
   establishColor(clrHilite, hilite, defclrHilite);

   evt.clearBackground(clrBackground);

   // Create the text to draw
   IString theText(dummyText);
   IString theNumber(clicks);
   theNumber.rightJustify(4);
   IString both(theText + theNumber);

   POINTL aptl[TXTBOX_COUNT];
   POINTL ptl = {0,0};

   // Find where we're going to draw our text and how big it will be.
   GpiQueryTextBox(hps,
                   strlen((char*)both),
                   (char*)both,
                   TXTBOX_COUNT,
                   aptl);

   long textWidth = MAX(aptl[TXTBOX_TOPRIGHT].x,
                        aptl[TXTBOX_BOTTOMRIGHT].x);
   long textHeight = MAX(aptl[TXTBOX_TOPLEFT].y,
                         aptl[TXTBOX_TOPRIGHT].y);

   // Center the text before drawing it.
   long x = (cx - textWidth) / 2;
   long y = (cy - textHeight) / 2;

   evt.drawText(theText, IPoint(x, y), clrForeground);

   GpiQueryTextBox(hps,
                   strlen((char*)theText),
                   (char*)theText,
                   TXTBOX_COUNT,
                   aptl);

   // Draw the number to the side of the text
   x += aptl[TXTBOX_CONCAT].x;
   evt.drawText(theNumber, IPoint(x, y), clrHilite);

   return true;
   }

//----------------------------------------------------------------------------
// Method: NewControl::windowResize
//
// Description: 'windowResize' is called in response to a resize event, 'evt'.
//              It stores the current width and height of the control.
//----------------------------------------------------------------------------
Boolean NewControl::windowResize(IResizeEvent& evt)
   {
   // Keep track of control's width and height.
   cx = evt.newSize().width();
   cy = evt.newSize().height();
   return false;
   }

//----------------------------------------------------------------------------
// Method: NewControl::gainingFocus
//
// Description: 'gainingFocus' is called in response to a focus gain event,
//              'evt'. It doesn't do anything, but you can fill in any code
//              you feel appropriate for when the control gains focus.
//----------------------------------------------------------------------------
Boolean NewControl::gainingFocus(IEvent &evt)
   {
   evt;

   // You could create a cursor here if you like.

   return true;
   }

//----------------------------------------------------------------------------
// Method: NewControl::losingFocus
//
// Description: 'losingFocus' is called in response to a focus loss event,
//              'evt'. It doesn't do anything, but you can fill in any code
//              you feel appropriate for when the control loses focus.
//----------------------------------------------------------------------------
Boolean NewControl::losingFocus(IEvent &evt)
   {
   evt;

   // You could destroy a cursor here if you like.

   return true;
   }

//----------------------------------------------------------------------------
// Method: NewControl::mouseClicked
//
// Description: 'mouseClicked' is called in response to a mouse click event,
//              'evt'. It sends notifications to the owner describing which
//              mouse button was clicked and refreshes the window when
//              appropriate.
//----------------------------------------------------------------------------
Boolean NewControl::mouseClicked(IMouseClickEvent& evt)
   {
   // If the mouse is clicked down and NewControl doesn't already
   // have the focus, set the focus to it.
   if (IMouseClickEvent::down == evt.mouseAction() &&
       !hasFocus())
      setFocus();

   // If the mouse is clicked and released...
   if (IMouseClickEvent::click == evt.mouseAction())
      {

      // If it was button 1, update the click count, paint, and notify owner.
      if (IMouseClickEvent::button1 == evt.mouseNumber())
         {
         ++clicks;
         refresh();
         owner()->sendEvent(WM_CONTROL,
                            IEventParameter1(id(), IMouseClickEvent::button1));
         }

      // If it was button 2, just notify owner.
      else if (IMouseClickEvent::button2 == evt.mouseNumber())
         {
         owner()->sendEvent(WM_CONTROL,
                            IEventParameter1(id(), IMouseClickEvent::button2));
         }
      }

   return true;
   }

