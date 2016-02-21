/***************************************************************/
/* Filename: newctevt.cpp                                      */
/*                                                             */
/* Purpose: Definition od NewControlEvent class.               */
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

#include "newctevt.hpp"

NewControlEvent::NewControlEvent(IEvent &evt)
   : MControlEvent(evt)
   {
   }

NewControlEvent::~NewControlEvent()
   {
   }

//----------------------------------------------------------------------------
// Method: NewControlEvent::mouseNumber
//
// Description: 'mouseNumber' returns the number of the mouse button that
//              was clicked.
//----------------------------------------------------------------------------
IMouseClickEvent::MouseNumber NewControlEvent::mouseNumber() const
   {
   return IMouseClickEvent::MouseNumber(parameter1().number2());
   }

