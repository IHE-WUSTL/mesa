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

#include "MESA.hpp"
#include "MDBPostProcMgrClient.hpp"
#include "MGPWorkitem.hpp"


static char rcsid[] = "$Id: MDBPostProcMgrClient.cpp,v 1.1 2002/04/16 19:21:10 drm Exp $";

MDBPostProcMgrClient::MDBPostProcMgrClient()
{
}

MDBPostProcMgrClient::MDBPostProcMgrClient(const MDBPostProcMgrClient& cpy)
{
}

MDBPostProcMgrClient::~MDBPostProcMgrClient()
{
}

void
MDBPostProcMgrClient::printOn(ostream& s) const
{
  s << "MDBPostProcMgrClient";
}

void
MDBPostProcMgrClient::streamIn(istream& s)
{
  //s >> this->member;
}

// Non boiler-plate methods follow below

//virtual
//int
//MDBOFClient::selectCallback(const MMWL& mwl, const MActionItemVector& actionitem)
//{
//  cout << mwl << endl;
//}
