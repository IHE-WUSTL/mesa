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
#include "MDBOrderFiller.hpp"
#include "MPatient.hpp"
#include "MMWLObjects.hpp"
#include "MDBOFClient.hpp"
#include "MVisit.hpp"
#include "MFillerOrder.hpp"
#include "MPlacerOrder.hpp"
#include "MLogClient.hpp"

static void
placerOrderCallback(MDomainObject& o, void* ctx)
{
  MOrder ord;

  ord.import(o);

  MPlacerOrder* po = (MPlacerOrder*)ctx;
  if (po)
    po->add(ord);
}

static void
fillerOrderCallback(MDomainObject& o, void* ctx)
{
  MOrder ord;

  ord.import(o);
  MFillerOrder* fo = (MFillerOrder*)ctx;
  if (fo)
    fo->add(ord);
}

MDBOrderFiller::MDBOrderFiller() : mDBInterface(NULL)
{
}

MDBOrderFiller::MDBOrderFiller(const MDBOrderFiller& cpy) : mDBInterface(cpy.mDBInterface)
{
}

MDBOrderFiller::~MDBOrderFiller()
{
  if (mDBInterface)
    delete mDBInterface;
}

void
MDBOrderFiller::printOn(ostream& s) const
{
  s << "MDBOrderFiller";
}

void
MDBOrderFiller::streamIn(istream& s)
{
  //s >> this->member;
}

MDBOrderFiller::MDBOrderFiller(const MString& databaseName)
{
  if (databaseName == "")
    mDBInterface = 0;
  else
    mDBInterface = new MDBInterface(databaseName);
}

int
MDBOrderFiller::openDatabase(const MString& databaseName)
{
  if (mDBInterface)
    delete mDBInterface;

  if (databaseName == "")
    mDBInterface = 0;
  else
    mDBInterface = new MDBInterface(databaseName);

  return 0;
}

int
MDBOrderFiller::admitRegisterPatient(const MPatient& patient,
				     const MVisit& visit)
{
  MLogClient logClient;
  logClient.logTimeStamp(MLogClient::MLOG_VERBOSE,
		  "MDBOrderFiller::admitRegisterPatient enter method");

  // first do sanity check
  if (!mDBInterface) {
    logClient.logTimeStamp(MLogClient::MLOG_ERROR,
		    "MDBOrderFiller::admitRegisterPatient no DBInterface defined; programming or runtime error");
    return 1;
  }

  if (patient.mapEmpty()) {
    logClient.logTimeStamp(MLogClient::MLOG_VERBOSE,
		    "MDBOrderFiller::admitRegisterPatient exit method; no patient to register");
    return 0;
  }

  int status = 0;
  status = recordExists(patient);
  if (status < 0) {
    logClient.logTimeStamp(MLogClient::MLOG_ERROR,
		    "MDBOrderFiller::admitRegisterPatient; unable to determine if patient record exists");
  } else if (status != 0) {
    status = updateRecord(patient);
  } else {
    status = addRecord(patient);
  }

  if (status != 0) {
    logClient.logTimeStamp(MLogClient::MLOG_ERROR,
		    "MDBOrderFiller::admitRegisterPatient exit method; unable to update or add patient record");
    return status;
  }

  if (visit.mapEmpty())
    return 0;

  if (recordExists(visit))
    updateRecord(visit);
  else
    addRecord(visit);

  logClient.logTimeStamp(MLogClient::MLOG_VERBOSE,
		  "MDBOrderFiller::admitRegisterPatient exit method");
  return 0;
}

int
MDBOrderFiller::preRegisterPatient(const MPatient& patient,
				     const MVisit& visit)
{
  if (!mDBInterface)
    return 1;

  return this->admitRegisterPatient(patient, visit);
}
int
MDBOrderFiller::updateADTInfo(const MPatient& patient)
{
  // first do sanity check
  if (!mDBInterface)
    return 1;

  if (patient.mapEmpty())
    return 0;

  updateRecord(patient);
  MMWL mwl;
  mwl.patientID(patient.patientID());
  mwl.patientName(patient.patientName());
  updateRecord(mwl);

  return 0;
}

int
MDBOrderFiller::updateADTInfo(const MPatient& patient, const MVisit& visit)
{
  // first do sanity check
  if (!mDBInterface)
    return 1;

  if (patient.mapEmpty())
    return 0;

  updateRecord(patient);

  if (visit.mapEmpty())
    return 0;

  updateRecord(visit);
  return 0;
}

int
MDBOrderFiller::transferPatient(const MVisit& visit)
{
  // first do sanity check
  if (!mDBInterface)
    return 1;

  if (visit.mapEmpty())
    return 0;

  MPatient patient;

  patient.patientID(visit.patientID());
  patient.issuerOfPatientID(visit.issuerOfPatientID());

  if (!recordExists(patient))
    return 0;

  updateRecord(visit);
  return 0;
}


int
MDBOrderFiller::mergePatient(const MPatient& patient, const MString& issuer)
{
  if (!mDBInterface)
    return 1;

  MCriteriaVector criteria;

  MString priorID = patient.priorID(issuer);

  MCriteria c;
  c.attribute = "patid";
  c.oper      = TBL_EQUAL;
  c.value     = priorID;

  MCriteriaVector cv;
  cv.push_back(c);

  MUpdateVector updateVector;
  MUpdate u;

  u.attribute = "patid";
  u.func      = TBL_SET;
  u.value     = patient.patientID();
  updateVector.push_back(u);

  MPlacerOrder placerOrder;
  placerOrder.patientID(patient.patientID());
  mDBInterface->update(placerOrder, cv, updateVector);

  MFillerOrder fillerOrder;
  fillerOrder.patientID(patient.patientID());
  mDBInterface->update(fillerOrder, cv, updateVector);

  MMWL mwl;
  mwl.patientID(patient.patientID());

  // In the MWL table, we have copies of demographics that
  // we need to update.
  // Repair job in the future is to replace demographics with a view
  // into a patient table.
  u.attribute = "nam";
  u.func      = TBL_SET;
  u.value     = patient.patientName();
  updateVector.push_back(u);

  u.attribute = "datbir";
  u.func      = TBL_SET;
  u.value     = patient.dateOfBirth();
  updateVector.push_back(u);

  u.attribute = "sex";
  u.func      = TBL_SET;
  u.value     = patient.patientSex();
  updateVector.push_back(u);

  mDBInterface->update(mwl, cv, updateVector);

  // Then delete from patient table.
  mDBInterface->remove(patient, cv);

  // Add the patient if it does not already exist
  if (!recordExists(patient)) {
    addRecord(patient);
  }

  return 0;
}

int
MDBOrderFiller::enterOrder(const MFillerOrder& order)
{
  // first do sanity check
  if (!mDBInterface)
    return 1;

  if (order.mapEmpty())
    return 0;

  MPatient p;

  p.patientID(order.patientID());
  p.issuerOfPatientID(order.issuerOfPatientID());

  if (recordExists(p))
  {
    if (recordExists(order))
      updateRecord(order);
    else {
      addOrder(order);
    }
  }
  else
    return 0;

  return 1;
}

int
MDBOrderFiller::enterOrder(const MPlacerOrder& order)
{
  // first do sanity check
  if (!mDBInterface)
    return 1;

  if (order.mapEmpty())
    return 0;

  MPatient p;

  p.patientID(order.patientID());
  p.issuerOfPatientID(order.issuerOfPatientID());

  if (recordExists(p)) {
    if (recordExists(order)) {
      MPlacerOrder copyOfOrder(order);
      copyOfOrder.remove("messta");
      updateRecord(copyOfOrder);
    } else {
      MPlacerOrder copyOfOrder(order);
      copyOfOrder.mesaStatus("REQUESTED");
      addOrder(copyOfOrder);
    }
  } else {
    return 0;
  }

  return 1;
}

int
MDBOrderFiller::updatePlacerOrderNumber(const MFillerOrder& order)
{
  if (!mDBInterface)
    return 1;
//  if (order.mapEmpty())
//    return 0;
//  MPatient p;
//  p.patientID(order.patientID());
//  p.issuerOfPatientID(order.issuerOfPatientID());
// if (recordExists(p)){
    MCriteriaVector cv;
    MUpdateVector uv;
    MCriteria c;
    MUpdate u;
    c.attribute = "filordnum";
    c.oper = TBL_EQUAL;
    c.value = order.fillerOrderNumber();
    cv.push_back(c);
    u.attribute = "plaordnum";
    u.func = TBL_SET;
    u.value = order.placerOrderNumber();
    uv.push_back(u);

    MOrder o;
    MPlacerOrder po;
    mDBInterface->update(order, cv, uv);
    mDBInterface->update(po, cv, uv);
    mDBInterface->update(o, cv, uv);

    return 0;
}

int
MDBOrderFiller::updateOrder(const MFillerOrder& order)
{
  // first do sanity check
  if (!mDBInterface)
    return 1;

  if (order.mapEmpty())
    return 0;

  MPatient p;

  p.patientID(order.patientID());
  p.issuerOfPatientID(order.issuerOfPatientID());

  if (recordExists(p)) {  
    updateRecord(order);
    return 0;
  } else {
    return 0;
  }
}

int
MDBOrderFiller::cancelOrder(const MFillerOrder& order)
{
  //first do sanity check
  if (!mDBInterface)
    return 1;

  if (order.mapEmpty())
    return 0;

  deleteRecord(order);

  return 1;
}

int
MDBOrderFiller::getOrder(MPatient& patient, MFillerOrder& order)
{
  //first do sanity check
  if (!mDBInterface)
    return 1;

  if (order.mapEmpty())
    return 0;

  if (patient.mapEmpty())
  {
    // set patient ID and issuer in patient object from order object
    patient.patientID(order.patientID());
    patient.issuerOfPatientID(order.issuerOfPatientID());
  }
  else
  {
    if (patient.patientID() != order.patientID())
      return 0;
  }

  if (recordExists(patient))
  {
    MCriteriaVector cv;
    setCriteria(patient, cv);
    mDBInterface->select(patient, cv, NULL);
  }
  else
    return 0;

  if (recordExists(order))
  {
    MCriteriaVector cv;
    setCriteria(order, cv);
    mDBInterface->select(order, cv, NULL);
  }
  else
    return 0;

  // now get all the orders belonging to the order placer
  MOrder o;
  MCriteriaVector cv;

  // set criteria
  o.placerOrderNumber(order.placerOrderNumber());
  o.fillerOrderNumber(order.fillerOrderNumber());
  setCriteria(o, cv);

  int numOrders = mDBInterface->select(o, cv, fillerOrderCallback, &order);
  // processFillerOrder() function will be repeatedly called with order
  // domain object.  This function will insert each order found in the
  // placerOrder object

  if (numOrders != order.numOrders())
  {
    cerr << "MDBOrderPlacer: Processing Error: " << endl;
    cerr << "Number of Orders in the database: " << numOrders << endl;
    cerr << "Number of Orders captured in the domain object: " \
         << order.numOrders() << endl;
  }

  return 1;
}

int
MDBOrderFiller::getOrder(MPatient& patient, MPlacerOrder& order)
{
  //first do sanity check
  if (!mDBInterface)
    return 1;

  if (order.mapEmpty())
    return 0;

  if (patient.mapEmpty())
  {
    // set patient ID and issuer in patient object from order object
    patient.patientID(order.patientID());
    patient.issuerOfPatientID(order.issuerOfPatientID());
  }
  else
  {
    if (patient.patientID() != order.patientID())
      return 0;
  }

  if (recordExists(patient))
  {
    MCriteriaVector cv;
    setCriteria(patient, cv);
    mDBInterface->select(patient, cv, NULL);
  }
  else
    return 0;

  if (recordExists(order))
  {
    MCriteriaVector cv;
    setCriteria(order, cv);
    mDBInterface->select(order, cv, NULL);
  }
  else
    return 0;

  // now get all the orders belonging to the order placer
  MOrder o;
  MCriteriaVector cv;

  // set criteria
  o.placerOrderNumber(order.placerOrderNumber());
  setCriteria(o, cv);

  int numOrders = mDBInterface->select(o, cv, placerOrderCallback, &order);
  // processPlacerOrder() function will be repeatedly called with order
  // domain object.  This function will insert each order found in the
  // placerOrder object

  if (numOrders != order.numOrders())
  {
    cerr << "MDBOrderPlacer: Processing Error: " << endl;
    cerr << "Number of Orders in the database: " << numOrders << endl;
    cerr << "Number of Orders captured in the domain object: " \
         << order.numOrders() << endl;
  }

  return 1;
}

void
mwlCallback(MDomainObject& domainObj, void* ctx)
{
  MDBOrderFiller* ordfil = (MDBOrderFiller*)ctx;

  MMWL mwl;
  mwl.import(domainObj);

  ordfil->addToVector(mwl);
}

void
upsCallback(MDomainObject& domainObj, void* ctx)
{
  MDBOrderFiller* ordfil = (MDBOrderFiller*)ctx;

  MUPS ups;
  ups.import(domainObj);

  ordfil->addToVector(ups);
}

void
actionItemCallback(MDomainObject& domainObj, void* ctx)
{
  MActionItemVector * av = (MActionItemVector*)ctx;
  MActionItem a;
  a.import(domainObj);
  (*av).push_back(a);
}

void
ssnCodeCallback(MDomainObject& domainObj, void* ctx)
{
  MUWLScheduledStationNameCodeVector* av = (MUWLScheduledStationNameCodeVector*)ctx;
  MUWLScheduledStationNameCode a;
  a.import(domainObj);
  (*av).push_back(a);
}

int
MDBOrderFiller::queryModalityWorkList(const MMWL& mwl, MDBOFClient& client)
{
  if (!mDBInterface)
    return 0;

  //clear the MMWLObjectsVector
  MMWLVector::iterator objIt = mMWLVector.end();
  for (; objIt != mMWLVector.begin(); objIt--) {
    mMWLVector.pop_back();
  }   


  //set up the search criteria
    char* searchCriteria[] = {
    "patid",
    "nam",
    "accnum",
    "reqproid",
    "spsstadat",
    "spsstatim",
    "mod",
    "schaet"
  };

  int i;
  MCriteriaVector criteria;

  const MDomainMap& m = mwl.map();
  for(i = 0; i < (int)DIM_OF(searchCriteria); i++) {
    MDomainMap::const_iterator iDomain = m.find(searchCriteria[i]);
    MString s = (*iDomain).second;

    // MString s = m[searchCriteria[i]];

    if (s != "") {
      if (searchCriteria[i] == "spsstadat" || searchCriteria[i] == "spsstatim") {
	MString lrange = s.getToken('-',0);
	MString hrange;
	if(s.tokenExists('-',1))
	  hrange = s.getToken('-',1);
	else
	  hrange = "";
	if ((lrange != "") && s.tokenExists('-',1)){
	  TBL_OPERATOR oper = TBL_GREATER_EQUAL;
	  MCriteria c;
	  c.attribute = searchCriteria[i];
	  c.oper      = oper;
	  c.value     = lrange;
	  criteria.push_back(c);
	}
	if (hrange != ""){
	  TBL_OPERATOR oper = TBL_LESS_EQUAL;
	  MCriteria c;
	  c.attribute = searchCriteria[i];
	  c.oper      = oper;
	  c.value     = hrange;
	  criteria.push_back(c);
	}
	if ((lrange != "") && !(s.tokenExists('-',1))){
	  TBL_OPERATOR oper = TBL_EQUAL;
	  if (s.find("*") != string::npos) {
	    s.substitute('*', '%');
	    oper = TBL_LIKE;
	  }
	  MCriteria c;
	  c.attribute = searchCriteria[i];
	  c.oper      = oper;
	  c.value     = s;
	  criteria.push_back(c);
	}
      } else {
	TBL_OPERATOR oper = TBL_EQUAL;
	if (s.find("*") != string::npos) {
	  s.substitute('*', '%');
	  oper = TBL_LIKE;
	}
	MCriteria c;
	c.attribute = searchCriteria[i];
	c.oper      = oper;
	c.value     = s;
	criteria.push_back(c);
      }  
    }
  }

  MMWL retMWLValues;

  mDBInterface->select(retMWLValues, criteria, mwlCallback, this);
  for (MMWLVector::iterator mwlIter = mMWLVector.begin();
		mwlIter != mMWLVector.end();
		mwlIter++) {

    MActionItemVector av;
    MActionItem actionItem;
    MCriteriaVector cv1;
    MCriteria c1;
    c1.attribute = "spsindex";
    c1.oper      = TBL_EQUAL;
    c1.value     = (*mwlIter).spsIndex();
    cv1.push_back(c1);
    mDBInterface->select(actionItem, cv1, actionItemCallback, &av);
    client.selectCallback(*mwlIter, av);
  }

  return 0;
}

int
MDBOrderFiller::queryUnifiedWorkList(const MUPS& ups, MDBOFClient& client)
{
  if (!mDBInterface)
    return 0;

  //clear the MUPSObjectsVector
  MUPSVector::iterator objIt = mUPSVector.end();
  for (; objIt != mUPSVector.begin(); objIt--) {
    mUPSVector.pop_back();
  }   


  //set up the search criteria
    char* searchCriteria[] = {
    "patid",
    "nam",
    "accnum",
    "reqproid",
    "spsstadat",
    "spsstatim",
    "mod",
    "schaet"
  };

  int i;
  MCriteriaVector criteria;

  const MDomainMap& m = ups.map();
  for(i = 0; i < (int)DIM_OF(searchCriteria); i++) {
    MDomainMap::const_iterator iDomain = m.find(searchCriteria[i]);
    MString s = (*iDomain).second;

    // MString s = m[searchCriteria[i]];

    if (s != "") {
      if (searchCriteria[i] == "spsstadat" || searchCriteria[i] == "spsstatim") {
	MString lrange = s.getToken('-',0);
	MString hrange;
	if(s.tokenExists('-',1))
	  hrange = s.getToken('-',1);
	else
	  hrange = "";
	if ((lrange != "") && s.tokenExists('-',1)){
	  TBL_OPERATOR oper = TBL_GREATER_EQUAL;
	  MCriteria c;
	  c.attribute = searchCriteria[i];
	  c.oper      = oper;
	  c.value     = lrange;
	  criteria.push_back(c);
	}
	if (hrange != ""){
	  TBL_OPERATOR oper = TBL_LESS_EQUAL;
	  MCriteria c;
	  c.attribute = searchCriteria[i];
	  c.oper      = oper;
	  c.value     = hrange;
	  criteria.push_back(c);
	}
	if ((lrange != "") && !(s.tokenExists('-',1))){
	  TBL_OPERATOR oper = TBL_EQUAL;
	  if (s.find("*") != string::npos) {
	    s.substitute('*', '%');
	    oper = TBL_LIKE;
	  }
	  MCriteria c;
	  c.attribute = searchCriteria[i];
	  c.oper      = oper;
	  c.value     = s;
	  criteria.push_back(c);
	}
      } else {
	TBL_OPERATOR oper = TBL_EQUAL;
	if (s.find("*") != string::npos) {
	  s.substitute('*', '%');
	  oper = TBL_LIKE;
	}
	MCriteria c;
	c.attribute = searchCriteria[i];
	c.oper      = oper;
	c.value     = s;
	criteria.push_back(c);
      }  
    }
  }

  MUPS retUPSValues;

  mDBInterface->select(retUPSValues, criteria, upsCallback, this);
  for (MUPSVector::iterator upsIter = mUPSVector.begin();
		upsIter != mUPSVector.end();
		upsIter++) {

    MUWLScheduledStationNameCodeVector ssnCodeVector;
    MUWLScheduledStationNameCode ssnCode;
    MCriteriaVector cv1;
    MCriteria c1;
    c1.attribute = "uwlindex";
    c1.oper      = TBL_EQUAL;
    c1.value     = (*upsIter).id();
    cv1.push_back(c1);
    mDBInterface->select(ssnCode, cv1, ssnCodeCallback, &ssnCodeVector);
    client.selectCallback(*upsIter, ssnCodeVector);
  }

  return 0;
}

int
MDBOrderFiller::addToVector(const MMWL& mwl)
{
  mMWLVector.push_back(mwl);

  return 0;
}

int
MDBOrderFiller::addToVector(const MUPS& ups)
{
  mUPSVector.push_back(ups);

  return 0;
}

// **********************************************************************************************
// FOLLOWING ARE PRIVATE FUNCTIONS ONLY MEANT TO BE USED BY THE CLASS MEMBER FUNCTIONS THEMSELVES
// **********************************************************************************************

int
MDBOrderFiller::recordExists(const MPatient& patient)
{
  if (patient.mapEmpty())
    return 0;

  MPatient p;
  MCriteriaVector cv;

  setCriteria(patient, cv);

  int status;
  status = mDBInterface->select(p, cv, NULL);
  if (status < 0) {
    // Maybe the table definition is not up to date.
    // Try a different table mapping
    int x = p.numAttributes();
    p.remove("addr");
    p.remove("xrefkey");
    MCriteriaVector cv1;
    setCriteria(patient, cv1);

    status = mDBInterface->select(p, cv1, NULL);
  }
  return status;
}

int
MDBOrderFiller::recordExists(const MVisit& visit)
{
  if (visit.mapEmpty())
    return 0;

  MVisit v;
  MCriteriaVector cv;

  setCriteria(visit, cv);

  return mDBInterface->select(v, cv, NULL);
}

int
MDBOrderFiller::recordExists(const MFillerOrder& order)
{
  if (order.mapEmpty())
    return 0;

  MFillerOrder fo;
  MCriteriaVector cv;
  
  setCriteria(order, cv);

  return mDBInterface->select(fo, cv, NULL);
}

int
MDBOrderFiller::recordExists(const MPlacerOrder& order)
{
  if (order.mapEmpty())
    return 0;

  MPlacerOrder po;
  MCriteriaVector cv;
  
  setCriteria(order, cv);

  return mDBInterface->select(po, cv, NULL);
}

int
MDBOrderFiller::recordExists(const MOrder& order)
{
  if (order.mapEmpty())
    return 0;

  MOrder o;
  MCriteriaVector cv;
  
  setCriteria(order, cv);

  return mDBInterface->select(o, cv, NULL);
}

int
MDBOrderFiller::addRecord(const MDomainObject& domainObject)
{
  MLogClient logClient;
  logClient.logTimeStamp(MLogClient::MLOG_VERBOSE,
	"MDBOrderFiller::addRecord(domainObj) enter method");
  int status = mDBInterface->insert(domainObject);
  if (status != 0) {
    logClient.logTimeStamp(MLogClient::MLOG_ERROR,
	"Could not insert patient record");
  }
  logClient.logTimeStamp(MLogClient::MLOG_VERBOSE,
	"MDBOrderFiller::addRecord(domainObj) exit method");
  return status;
}

int
MDBOrderFiller::addRecord(const MPatient& patient)
{
  MLogClient logClient;
  logClient.logTimeStamp(MLogClient::MLOG_VERBOSE,
	"MDBOrderFiller::addRecord(patient) enter method");

  int status = mDBInterface->insert(patient);
  if (status != 0) {
    logClient.logTimeStamp(MLogClient::MLOG_VERBOSE,
	"Could not insert patient record; about to remove addr and xrefkey");
    MPatient p (patient);
    p.remove("addr");
    p.remove("xrefkey");
    status = mDBInterface->insert(p);
    if (status == 0) {
      logClient.logTimeStamp(MLogClient::MLOG_VERBOSE,
	"Inserted Patient record w/o addr and xrefkey attributes");
    }
  }
  if (status != 0) {
    logClient.logTimeStamp(MLogClient::MLOG_ERROR,
	"Could not insert patient record");
  }
  logClient.logTimeStamp(MLogClient::MLOG_VERBOSE,
	"MDBOrderFiller::addRecord(patient) exit method");
  return status;
}

int
MDBOrderFiller::addOrder(const MFillerOrder& order)
{
  int status = mDBInterface->insert(order);
  if (status != 0) {
    return status;
  }

  for (int inx = 0; inx < order.numOrders(); inx++) {
    status = addRecord(order.order(inx));
    if (status != 0) {
      return status;
    }
  }
  return 0;
}

int
MDBOrderFiller::addOrder(const MPlacerOrder& order)
{
  // order.mesaStatus("REQUESTED");
  MPlacerOrder localOrder(order);
  mDBInterface->insert(localOrder);
  for (int inx = 0; inx < localOrder.numOrders(); inx++){
    addRecord(localOrder.order(inx));
  }
  return 0;
}

int
MDBOrderFiller::deleteRecord(const MPatient& patient)
{
  MCriteriaVector cv;

  setCriteria(patient, cv);
  int status = mDBInterface->remove(patient, cv);
  return status;
}

int
MDBOrderFiller::deleteRecord(const MVisit& visit)
{
  MCriteriaVector cv;

  setCriteria(visit, cv);
  int status = mDBInterface->remove(visit, cv);
  return status;
}

int
MDBOrderFiller::deleteRecord(const MFillerOrder& order)
{
  MCriteriaVector cv;

  setCriteria(order, cv);
  int status = mDBInterface->remove(order, cv);
  if (status != 0) {
    return status;
  }

  for (int inx = 0; inx < order.numOrders(); inx++) {
    status = deleteRecord(order.order(inx));
    if (status != 0) {
      return status;
    }
  }
  return 0;
}

int
MDBOrderFiller::deleteRecord(const MPlacerOrder& order)
{
  MCriteriaVector cv;
  MPlacerOrder localOrder(order);

  setCriteria(order, cv);
  int status = mDBInterface->remove(localOrder, cv);
  if (status != 0) {
    return status;
  }

  for (int inx = 0; inx < localOrder.numOrders(); inx++) {
    status = deleteRecord(localOrder.order(inx));
    if (status != 0) {
      return status;
    }
  }
  return status;
}

int
MDBOrderFiller::deleteRecord(const MOrder& order)
{
  MCriteriaVector cv;

  setCriteria(order, cv);
  int status = mDBInterface->remove(order, cv);
  return status;
}

int
MDBOrderFiller::updateRecord(const MPatient& patient)
{
  MLogClient logClient;
  logClient.logTimeStamp(MLogClient::MLOG_VERBOSE,
	"MDBOrderFiller::updateRecord(patient) enter method");
  MCriteriaVector cv;
  MUpdateVector   uv;

  setCriteria(patient, cv);
  setCriteria(patient, uv);

  int status = mDBInterface->update(patient, cv, uv);
  if (status != 0) {
    logClient.logTimeStamp(MLogClient::MLOG_VERBOSE,
	"Could not update patient; trying w/o addr, xrefkey");
    MPatient p(patient);
    p.remove("addr");
    p.remove("xrefkey");
    MCriteriaVector cv1;
    MUpdateVector   uv1;
    setCriteria(p, cv1);
    setCriteria(p, uv1);
    status = mDBInterface->update(p, cv1, uv1);
    if (status == 0) {
      logClient.logTimeStamp(MLogClient::MLOG_VERBOSE,
	"Updated patient successfully w/o addr, xrefkey");
    }
  }
  if (status != 0) {
    logClient.logTimeStamp(MLogClient::MLOG_ERROR,
	"Unable to update patient record");
  }
  logClient.logTimeStamp(MLogClient::MLOG_VERBOSE,
	"MDBOrderFiller::updateRecord(patient) exit method");
  return status;
}

int
MDBOrderFiller::updateRecord(const MVisit& visit)
{
  MCriteriaVector cv;
  MUpdateVector   uv;

  setCriteria(visit, cv);
  setCriteria(visit, uv);

  int status = mDBInterface->update(visit, cv, uv);
  return status;
}

int
MDBOrderFiller::updateRecord(const MFillerOrder& order)
{
  MCriteriaVector cv;
  MUpdateVector   uv;

  setCriteria(order, cv);
  setCriteria(order, uv);

  MFillerOrder localOrder(order);
  localOrder.remove("messta");
  int status = mDBInterface->update(order, cv, uv);
  if (status != 0) {
    return status;
  }

  for (int inx = 0; inx < order.numOrders(); inx++) {
    MOrder copyOfOrder(order.order(inx));
    copyOfOrder.remove("messta");
    status = updateRecord(copyOfOrder);
    if (status != 0) {
      return status;
    }
  }
  return 0;
}

int
MDBOrderFiller::updateRecord(const MPlacerOrder& order)
{
  MCriteriaVector cv;
  MUpdateVector   uv;
  MPlacerOrder    localOrder(order);
  localOrder.remove("messta");

  setCriteria(localOrder, cv);
  setCriteria(localOrder, uv);

  int status = mDBInterface->update(localOrder, cv, uv);
  if (status != 0) {
    return status;
  }

  for (int inx = 0; inx < localOrder.numOrders(); inx++) {
    MOrder o  = localOrder.order(inx);
    o.remove("messta");
    status = updateRecord(o);
    if (status != 0) {
      return status;
    }
  }
//    updateRecord(localOrder.order(inx));
  return 0;
}

int
MDBOrderFiller::updateRecord(const MOrder& order)
{
  MCriteriaVector cv;
  MUpdateVector   uv;

  setCriteria(order, cv);
  setCriteria(order, uv);

  int status = mDBInterface->update(order, cv, uv);
  return status;
}

int
MDBOrderFiller::updateRecord(const MMWL& mwl)
{
  MCriteriaVector cv;
  MUpdateVector   uv;

  setCriteria(mwl, cv);
  setCriteria(mwl, uv);

  int status = mDBInterface->update(mwl, cv, uv);
  return status;
}

void
MDBOrderFiller::setCriteria(const MPatient& patient, MCriteriaVector& cv)
{
  MCriteria c;
  
  c.attribute = "patid";
  c.oper      = TBL_EQUAL;
  c.value     = patient.patientID();
  cv.push_back(c);

  MString issuer(patient.issuerOfPatientID());

  if (issuer.size())
  {
    c.attribute = "issuer";
    c.oper      = TBL_EQUAL;
    c.value     = patient.issuerOfPatientID();
    cv.push_back(c);
  }
}

void
MDBOrderFiller::setCriteria(const MVisit& visit, MCriteriaVector& cv)
{
  MCriteria c;
  
  c.attribute = "patid";
  c.oper      = TBL_EQUAL;
  c.value     = visit.patientID();
  cv.push_back(c);

  MString issuer(visit.issuerOfPatientID());

  if (issuer.size())
  {
    c.attribute = "issuer";
    c.oper      = TBL_EQUAL;
    c.value     = visit.issuerOfPatientID();
    cv.push_back(c);
  }

  c.attribute = "visnum";
  c.oper      = TBL_EQUAL;
  c.value     = visit.visitNumber();
  cv.push_back(c);
}

void
MDBOrderFiller::setCriteria(const MPlacerOrder& order, MCriteriaVector& cv)
{
  MCriteria c;
  
  MString patientID(order.patientID());

  if (patientID.size())
  {
    c.attribute = "patid";
    c.oper      = TBL_EQUAL;
    c.value     = order.patientID();
    cv.push_back(c);
  }

  MString issuer(order.issuerOfPatientID());

  if (issuer.size())
  {
    c.attribute = "issuer";
    c.oper      = TBL_EQUAL;
    c.value     = order.issuerOfPatientID();
    cv.push_back(c);
  }

  c.attribute = "plaordnum";
  c.oper      = TBL_EQUAL;
  c.value     = order.placerOrderNumber();
  cv.push_back(c);

}

void
MDBOrderFiller::setCriteria(const MFillerOrder& order, MCriteriaVector& cv)
{
  MCriteria c;
  
  MString patientID(order.patientID());

  if (patientID.size())
  {
    c.attribute = "patid";
    c.oper      = TBL_EQUAL;
    c.value     = order.patientID();
    cv.push_back(c);
  }

  MString issuer(order.issuerOfPatientID());

  if (issuer.size())
  {
    c.attribute = "issuer";
    c.oper      = TBL_EQUAL;
    c.value     = order.issuerOfPatientID();
    cv.push_back(c);
  }

  MString poNum(order.placerOrderNumber());

  if (poNum.size())
  {
    c.attribute = "plaordnum";
    c.oper      = TBL_EQUAL;
    c.value     = order.placerOrderNumber();
    cv.push_back(c);
  }

  c.attribute = "filordnum";
  c.oper      = TBL_EQUAL;
  c.value     = order.fillerOrderNumber();
  cv.push_back(c);

//  may include accession number also
/*
  MString accNum(order.accessionNumber());

  if (accNum.size())
  {
    c.attribute = "accnum";
    c.oper      = TBL_EQUAL;
    c.value     = order.accessionNumber();
    cv.push_back(c);
  }  */
}

void
MDBOrderFiller::setCriteria(const MOrder& order, MCriteriaVector& cv)
{
  MCriteria c;
  
  MString poNum(order.placerOrderNumber());

  if (poNum.size())
  {
    c.attribute = "plaordnum";
    c.oper      = TBL_EQUAL;
    c.value     = order.placerOrderNumber();
    cv.push_back(c);
  }

  c.attribute = "filordnum";
  c.oper      = TBL_EQUAL;
  c.value     = order.fillerOrderNumber();
  cv.push_back(c);

  /* may be Universal Service ID also
  c.attribute = "uniserid";
  c.oper      = TBL_EQUAL;
  c.value     = order.universalServiceID();
  cv.push_back(c);
    */
}

void
MDBOrderFiller::setCriteria(const MMWL& mwl, MCriteriaVector& cv)
{
  MCriteria c;
  
  MString patID(mwl.patientID());

  if (patID.size()) {
    c.attribute = "patid";
    c.oper      = TBL_EQUAL;
    c.value     = mwl.patientID();
    cv.push_back(c);
  }
}

void
MDBOrderFiller::setCriteria(const MDomainObject& domainObject, MUpdateVector& uv)
{
  MUpdate u;
  MDomainMap m = domainObject.map();
  for (MDomainMap::iterator i = m.begin(); i != m.end(); i++)
  {
    u.attribute = (*i).first;
    u.func      = TBL_SET;
    u.value     = (*i).second;
    uv.push_back(u);
  }
}


MString
MDBOrderFiller::newStudyInstanceUID() const
{
  MString s;

  s = mIdentifier.dicomUID(MIdentifier::MUID_STUDY, *mDBInterface);

  return s;
}
