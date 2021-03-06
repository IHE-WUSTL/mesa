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

static char rcsid[] = "$Revision: 1.2 $ $RCSfile: weld.cpp,v $";


#include "MESA.hpp"
#include "ctn_api.h"

#include "MString.hpp"
#include "MDICOMWrapper.hpp"

void weldTopLevel(DCM_TAG* tag, MDICOMWrapper& mwl,
			 MDICOMWrapper& image)
{
  DCM_TAG t;
  MString s;

  while ((t = *tag++) != 0) {
    s = mwl.getString(t);
    image.setString(t, s);
  }
}

void addPerformedStudySequence(MDICOMWrapper& mwl,
				       MDICOMWrapper& image)
{
  LST_HEAD* l1 = 0;

  l1 = ::LST_Create();

  DCM_ELEMENT e = {DCM_PRCPERFORMEDAISEQUENCE, DCM_SQ, "", 1, 0, 0};

  e.d.sq = l1;

  DCM_OBJECT* obj = image.getNativeObject();
  ::DCM_AddSequenceElement(&obj, &e);
}

void addReferencedStudySequence(MDICOMWrapper& mwl,
				       MDICOMWrapper& image)
{
  LST_HEAD* l1 = 0;

  l1 = ::LST_Create();

  DCM_ELEMENT e = {DCM_IDREFERENCEDSTUDYSEQ, DCM_SQ, "", 1, 0, 0};

  e.d.sq = l1;

  DCM_OBJECT* obj = image.getNativeObject();
  ::DCM_AddSequenceElement(&obj, &e);
}

void addScheduledAICodeSequence(MDICOMWrapper& mwl,
				       MDICOMWrapper& image)
{
  DCM_OBJECT* mwlObj = mwl.getNativeObject();
  DCM_OBJECT* imageObj = image.getNativeObject();
  CONDITION cond;

  LST_HEAD* l1 = 0;

  cond = ::DCM_GetSequenceList(&mwlObj,
			       DCM_PRCSCHEDULEDPROCSTEPSEQ,
			       &l1);
  if (cond != DCM_NORMAL)
    return;

  LST_HEAD* l2 = ::LST_Create();
  DCM_SEQUENCE_ITEM* item = (DCM_SEQUENCE_ITEM*)::LST_Head(&l1);
  while (item != 0) {
    DCM_OBJECT* obj;

    ::DCM_CopyObject(&item->object, &obj);
    DCM_SEQUENCE_ITEM* item2 = (DCM_SEQUENCE_ITEM*)::malloc(sizeof(*item2));
    item2->object = obj;
    ::LST_Enqueue(&l2, item2);

    item = (DCM_SEQUENCE_ITEM*)::LST_Next(&l1);
  }

  DCM_ELEMENT e = { DCM_PRCSCHEDULEDACTIONITEMCODESEQ, DCM_SQ, "", 1, 0, 0};
  e.d.sq = l2;
//  DCM_ELEMENT e = { DCM_PRCPERFORMEDAISEQUENCE, DCM_SQ, "", 1, 0, 0};
//  e.d.sq = l2;

  ::DCM_RemoveElement(&imageObj, DCM_PRCSCHEDULEDACTIONITEMCODESEQ);
  ::DCM_AddSequenceElement(&imageObj, &e);
}

void addRequestAttributesSequence(MDICOMWrapper& mwl,
					  MDICOMWrapper& image)
{
  DCM_OBJECT* obj = 0;
  CONDITION cond = 0;

  ::DCM_CreateObject(&obj, 0);
  MDICOMWrapper w(obj);
  MString s;

  s = mwl.getString(DCM_PRCREQUESTEDPROCEDUREID);
  w.setString(DCM_PRCREQUESTEDPROCEDUREID, s);

  s = mwl.getString(DCM_PRCSCHEDULEDPROCSTEPSEQ,
		    DCM_PRCSCHEDULEDPROCSTEPID);
  w.setString(DCM_PRCSCHEDULEDPROCSTEPID, s);

  s = mwl.getString(DCM_PRCSCHEDULEDPROCSTEPSEQ,
		    DCM_PRCSCHEDULEDPROCSTEPID);
  w.setString(DCM_PRCSCHEDULEDPROCSTEPID, s);

  s = mwl.getString(DCM_PRCSCHEDULEDPROCSTEPSEQ,
		    DCM_PRCSCHEDULEDPROCSTEPDESCRIPTION);
  w.setString(DCM_PRCSCHEDULEDPROCSTEPDESCRIPTION, s);

  addScheduledAICodeSequence(mwl, w);

  LST_HEAD* l1;
  l1 = ::LST_Create();
  DCM_SEQUENCE_ITEM* item = (DCM_SEQUENCE_ITEM*)::malloc(sizeof(*item));
  item->object = obj;
  ::LST_Enqueue(&l1, item);

  DCM_ELEMENT e = { DCM_PRCREQUESTATTRIBUTESSEQ, DCM_SQ, "", 1, 0, 0};
  e.d.sq = l1;

  DCM_OBJECT* imageObj = image.getNativeObject();
  ::DCM_AddSequenceElement(&imageObj, &e);

}
