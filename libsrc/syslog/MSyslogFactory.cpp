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

#include "ctn_os.h"
#include "MESA.hpp"
#include "MSyslogFactory.hpp"
#include "MSyslogMessage.hpp"
#include "MLogClient.hpp"

#include <strstream>

static char rcsid[] = "$Id: MSyslogFactory.cpp,v 1.6 2007/04/09 16:11:51 smm Exp $";

#define ASCII_CR 0x0d
#define ASCII_LF 0x0a

MSyslogFactory::MSyslogFactory()
{
}

MSyslogFactory::MSyslogFactory(const MSyslogFactory& cpy)
{
}

MSyslogFactory::~MSyslogFactory()
{
}

void
MSyslogFactory::printOn(ostream& s) const
{
  s << "MSyslogFactory";
}

void
MSyslogFactory::streamIn(istream& s)
{
  //s >> this->member;
}

// Non boiler plate methods follow

MSyslogMessage*
MSyslogFactory::produceMessage(const char* str, int length)
{
  MLogClient logClient;

  logClient.log(MLogClient::MLOG_VERBOSE, "", "MSyslogFactory::produceMessage",
	__LINE__, "Enter method");

  if (*str != '<') {
    logClient.log(MLogClient::MLOG_ERROR,
	MString("MSyslogFactory::produceMessage first character of message expected to be '<'; input message to follow"));
    logClient.log(MLogClient::MLOG_ERROR, str);
    logClient.log(MLogClient::MLOG_VERBOSE, "", "MSyslogFactory::produceMessage",
	__LINE__, "Enter method");
    return 0;
  }

  str++;
  length--;

  char tmp[32768];
  char* p = tmp;

  while (isdigit(*str)) {
    *p++ = *str++;
    length--;
  }
  *p = '\0';

  istrstream s(tmp, ::strlen(tmp));
  int priority;

  s	>> priority;

  int facility = (priority >> 3) & 0xff;
  int severity = priority & 0x7;

  if (*str != '>')
    return 0;
  str++;
  length--;

  if (length < 15)	// Characters in time stamp
    return 0;

  char timeStamp[16];
  ::memcpy(timeStamp, str, 15);
  timeStamp[15] = '\0';

  str += 15;
  length--;

  if (*str != ' ')
    return 0;
  str++;
  length--;

  // Space past the hostname
  char hostName[1024];
  p = hostName;

  while(length > 0 && *str != ' ') {
    *p++ = *str++;
    length--;
  }
  *p = '\0';

  if (length == 0)
    return 0;

  str++;
  length--;

  while(length > 0 && *str != ' ' && *str != '<') {
    str++;
    length--;
  }
  if (length == 0)
    return 0;

  char message[32768];
  if (length == 0)
    return 0;

  if (length > sizeof(message) - 1)
    length = sizeof(message)-1;

  ::memcpy(message, str, length);
  message[length] = '\0';

  MSyslogMessage* m = new MSyslogMessage(facility,
					severity,
					"",		// Tag, empty
					message,
					timeStamp,
					hostName);


  logClient.log(MLogClient::MLOG_VERBOSE,
	MString("Syslog message extracted: ") + message);

  logClient.log(MLogClient::MLOG_VERBOSE, "", "MSyslogFactory::produceMessage",
	__LINE__, "Exit method");
  return m;
}

