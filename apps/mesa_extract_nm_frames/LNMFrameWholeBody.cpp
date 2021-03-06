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
#include "ctn_os.h"
#include "MString.hpp"
#include "MDICOMWrapper.hpp"

#include "LNMFrameWholeBody.hpp"


static char rcsid[] = "$Id: LNMFrameWholeBody.cpp,v 1.1 2004/09/30 13:39:36 ssurul01 Exp $";

LNMFrameWholeBody::LNMFrameWholeBody ()
{
}

LNMFrameWholeBody::~LNMFrameWholeBody (void)
{
}

LNMFrameWholeBody::LNMFrameWholeBody (const LNMFrameWholeBody& cpy)
{
}

void
LNMFrameWholeBody::printOn(ostream& s) const
{
  s << "LNMFrameWholeBody";
}

void
LNMFrameWholeBody::streamIn(istream& s)
{
}

// Non boiler-plate methods start here

int
LNMFrameWholeBody::extract(ofstream& f, MDICOMWrapper& w, MStringMap& m, ofstream& o)
{
  U32 frameSize = 0;
  U16 frameCount = 0;
  if (this->getFrameInformation(w, frameSize, frameCount, o) != 0) {
    return 1;
  }
  unsigned char* pixels = new unsigned char[frameSize];
  DCM_OBJECT* obj = w.getNativeObject();

  int energyWindowVectorLength;
  unsigned short* energyWindowVector = 0;
  if (w.getVector(energyWindowVectorLength, energyWindowVector, 0x00540010) != 0) {
    return 1;
  }
  int detectorVectorLength;
  unsigned short* detectorVector = 0;
  if (w.getVector(detectorVectorLength, detectorVector, 0x00540020) != 0) {
    return 1;
  }
  int matchingFrameCount = 0;
  int i;
  unsigned short fixedEnergyWindow = 0;
  unsigned short fixedDetector = 0;
  MString x;
  x = m["ENERGY"];
  if (x != "") fixedEnergyWindow = x.intData();
  x = m["DETECTOR"];
  if (x != "") fixedDetector = x.intData();

  void* ctx = 0;
  U32 rtnLength = 0;
  CONDITION cond = 0;
  DCM_ELEMENT pixelElement;
  ::memset(&pixelElement, 0, sizeof(pixelElement));
  pixelElement.tag = 0x7fe00010;
  ::DCM_LookupElement(&pixelElement);
  pixelElement.length = frameSize;

  for (i = 0; i < energyWindowVectorLength; i++) {
    bool matchingFrame = true;
    cout << energyWindowVector[i] << ' ' << detectorVector[i] << endl;
    if (fixedEnergyWindow != 0 && fixedEnergyWindow != energyWindowVector[i]) {
      matchingFrame = false;
    }
    if (fixedDetector != 0 && fixedDetector != detectorVector[i]) {
      matchingFrame = false;
    }
    cout << fixedEnergyWindow << ' ' << fixedDetector << ' ' << 'x' << matchingFrame << endl;
    pixelElement.d.ob = pixels;
    cond = ::DCM_GetElementValue(&obj, &pixelElement, &rtnLength, &ctx);
    if (matchingFrame) {
      matchingFrameCount++;
      f.write((const char*)pixels, frameSize);
      //o << frameSize << " " << frameCount;
    }
  }
  o << " " << matchingFrameCount << endl;
  cout << "matchingFrameCount: " << matchingFrameCount << endl;

  delete []energyWindowVector;
  delete []detectorVector;
  delete []pixels;
  return 0;
}
