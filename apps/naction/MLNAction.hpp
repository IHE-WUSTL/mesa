//
//        Copyright (C) 1999, 2000, HIMSS, RSNA and Washington University
//
//        The MESA test tools software and supporting documentation were
//        developed for the Integrating the Healthcare Enterprise (IHE)
//        initiative Year 1 (1999-2000), under the sponsorship of the
//        Healthcare Information and Management Systems Society (HIMSS)
//        and the Radiological Society of North America (RSNA) by:
//                Electronic Radiology Laboratory
//                Mallinckrodt Institute of Radiology
//                Washington University School of Medicine
//                510 S. Kingshighway Blvd.
//                St. Louis, MO 63110
//        
//        THIS SOFTWARE IS MADE AVAILABLE, AS IS, AND NEITHER HIMSS, RSNA NOR
//        WASHINGTON UNIVERSITY MAKE ANY WARRANTY ABOUT THE SOFTWARE, ITS
//        PERFORMANCE, ITS MERCHANTABILITY OR FITNESS FOR ANY PARTICULAR
//        USE, FREEDOM FROM ANY DEFECTS OR COMPUTER DISEASES OR ITS CONFORMITY 
//        TO ANY SPECIFICATION. THE ENTIRE RISK AS TO QUALITY AND PERFORMANCE OF
//        THE SOFTWARE IS WITH THE USER.
//
//        Copyright of the software and supporting documentation is
//        jointly owned by HIMSS, RSNA and Washington University, and free
//        access is hereby granted as a license to use this software, copy
//        this software and prepare derivative works based upon this software.
//        However, any distribution of this software source code or supporting
//        documentation or derivative works (source code and supporting
//        documentation) must include the three paragraphs of this copyright
//        notice.

// $Id: MLNAction.hpp,v 1.3 2000/05/09 03:43:32 smm Exp $ $Author: smm $ $Revision: 1.3 $ $Date: 2000/05/09 03:43:32 $ $State: Exp $
//
// ====================
//  = LIBRARY
//	xxx
//
//  = FILENAME
//	MLNAction.hpp
//
//  = AUTHOR
//	Author Name
//
//  = COPYRIGHT
//	Copyright Washington University, 1999
//
// ====================
//
//  = VERSION
//	$Revision: 1.3 $
//
//  = DATE RELEASED
//	$Date: 2000/05/09 03:43:32 $
//
//  = COMMENTTEXT
//	Comments

#ifndef MLNActionISIN
#define MLNActionISIN

#include <iostream>
#include <string>

#include "MSOPHandler.hpp"

using namespace std;

class MLNAction : public MSOPHandler
// = TITLE
//	Short title/description
//
// = DESCRIPTION
//	Describe the class and how to use it
{
public:
  // = The standard methods in this framework.
  MLNAction();
  // Default constructor
  MLNAction(const MLNAction& cpy);
  virtual ~MLNAction();
  virtual void printOn(ostream& s) const;
  // This method is used in conjunction with the streaming operator <<
  // to print the current state of MLNAction

  virtual void streamIn(istream& s);
  
  // = Class specific methods.

  CONDITION handleNActionResponse(DUL_PRESENTATIONCONTEXT* ctx,
				  MSG_N_ACTION_RESP** message,
				  DUL_ASSOCIATESERVICEPARAMETERS* params);

private:
};

inline ostream& operator<< (ostream& s, const MLNAction& c) {
	  c.printOn(s);
	  return s;
};

inline istream& operator >> (istream& s, MLNAction& c) {
  c.streamIn(s);
  return s;
}

#endif
