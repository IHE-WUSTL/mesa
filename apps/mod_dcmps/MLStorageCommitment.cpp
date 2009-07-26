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
#include "MLStorageCommitment.hpp"
#include "MDBImageManager.hpp"
#include "MDICOMWrapper.hpp"
#include "MDICOMDomainXlate.hpp"
#include "MPatient.hpp"
#include "MStudy.hpp"
#include "MSeries.hpp"
#include "MSOPInstance.hpp"
#include "MFileOperations.hpp"
#include "MLogClient.hpp"

#if 0
MLStorageCommitment::MLStorageCommitment()
{
}
#endif

MLStorageCommitment::MLStorageCommitment(const MLStorageCommitment& cpy) :
  mImageManager(cpy.mImageManager),
  mStorageDir(cpy.mStorageDir)
{
}

MLStorageCommitment::~MLStorageCommitment()
{
}

void
MLStorageCommitment::printOn(ostream& s) const
{
  s << "MLStorageCommitment";
}

void
MLStorageCommitment::streamIn(istream& s)
{
  //s >> this->member;
}

// Non-boiler plate methods to follow

MLStorageCommitment::MLStorageCommitment(MDBImageManager& manager,
				const MString& storageDir) :
  mImageManager(manager),
  mStorageDir(storageDir)
{
}

CONDITION
MLStorageCommitment::handleNEventCommand(DUL_PRESENTATIONCONTEXT* ctx,
					 MSG_N_EVENT_REPORT_REQ** message,
					 MSG_N_EVENT_REPORT_RESP* response,
					 DUL_ASSOCIATESERVICEPARAMETERS* params,
					 MString& directoryName)
{
  directoryName = ".";
  //::MSG_DumpMessage(*message, stdout);

  return 0;
}

CONDITION
MLStorageCommitment::handleNEventDataSet(DUL_PRESENTATIONCONTEXT* ctx,
					 MSG_N_EVENT_REPORT_REQ** message,
					 MSG_N_EVENT_REPORT_RESP* response,
					 DUL_ASSOCIATESERVICEPARAMETERS* params,
					 MString& directoryName)
{
  MLogClient logClient;
  logClient.log(MLogClient::MLOG_VERBOSE,
		params->callingAPTitle,
		"MLStorageCommitment::handleNEventDataSet",
		__LINE__,
		"Storage Commit N-Event dataset received");

  MFileOperations f;

  MString apTitle(params->callingAPTitle);
  MString fullPath = mStorageDir + "/st_comm/" + apTitle;

  f.createDirectory(fullPath);

  MString s = f.uniqueFile(fullPath, "cls");
  char* s1 = s.strData();

  CONDITION cond;
  cond = ::DCM_WriteFile(&(*message)->dataSet,
		  DCM_ORDERLITTLEENDIAN,
		  s1);

  logClient.log(MLogClient::MLOG_VERBOSE,
		params->callingAPTitle,
		"MLStorageCommitment::handleNEventDataSet",
		__LINE__,
		"Storage Commit N-Event dataset written to " + s);

  if (cond != DCM_NORMAL) {
    logClient.logCTNErrorStack(MLogClient::MLOG_ERROR, "");
  }

  delete []s1;

  ::strcpy(response->classUID, (*message)->classUID);
  response->dataSetType = DCM_CMDDATANULL;
  response->conditionalFields = 0;
  response->status = MSG_K_SUCCESS;
  return SRV_NORMAL;
}
