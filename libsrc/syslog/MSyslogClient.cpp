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

#include <strstream>

//#include "ctn_os.h"
#include "MESA.hpp"
#include "MSyslogClient.hpp"
#include "MSyslogMessage.hpp"
#include "MConnector.hpp"
#include "MLogClient.hpp"

#include <strstream>

static char rcsid[] = "$Id: MSyslogClient.cpp,v 1.4 2002/09/13 21:29:24 smm Exp $";

#define ASCII_CR 0x0d
#define ASCII_LF 0x0a

MSyslogClient::MSyslogClient() :
  mSocket(0),
  mServerName(""),
  mTestMode(0)
{
}

MSyslogClient::MSyslogClient(const MSyslogClient& cpy) :
  mSocket(cpy.mSocket),
  mServerName(cpy.mServerName),
  mTestMode(cpy.mTestMode)
{
}

MSyslogClient::~MSyslogClient()
{
  if (mSocket != 0) {
    ::close(mSocket);
  }
}

void
MSyslogClient::printOn(ostream& s) const
{
  s << "MSyslogClient";
}

void
MSyslogClient::streamIn(istream& s)
{
  //s >> this->member;
}

// Non boiler plate methods follow



int
MSyslogClient::open(const MString& host, int port)
{
  MConnector c;
  CTN_SOCKET s;

  int status = c.connectUDP(host, port, s);
  if (status != 0) {
    char buf[512];
    strstream s(buf, sizeof(buf));
    s << "Unable to make UDP socket to host: " << host
	<< " at port: " << port << '\0';

    MLogClient logClient;
    logClient.log(MLogClient::MLOG_ERROR, "",
	"MSyslogClient::open", __LINE__,
	buf);
    return 1;
  }

  mSocket = s;
  return 0;
}

int
MSyslogClient::sendMessage(MSyslogMessage& m)
{
  if (mSocket == 0) {
    MLogClient logClient;
    logClient.log(MLogClient::MLOG_ERROR, "",
	"MSyslogClient::sendMessage", __LINE__,
	"No socket opened before trying to send message: ");
    return 1;
  }

  char buffer[2048];

  int exportedLength = 0;

  if (mTestMode == 0) {		// This is the standard behavior
    m.exportHeader(buffer, sizeof(buffer), exportedLength);
  }

  char *p = buffer + exportedLength;

  int messageLength = exportedLength;

  if (mTestMode == 0) {
    *p++ = ' ';
    messageLength++;
  }

  m.exportMessage(p, sizeof(buffer) - exportedLength, exportedLength);

  messageLength += exportedLength;

  int bytesWritten;

#ifdef _WIN32
  bytesWritten = ::send(mSocket, buffer, messageLength, 0);
#else
  bytesWritten = ::write(mSocket, buffer, messageLength);
#endif
  if (bytesWritten != messageLength) {
      ::perror("");
    char tmp[512];
    strstream s(tmp, sizeof(tmp));
    s << "Unable to send UDP datagram, requested: " << messageLength
	<< " bytes, but only sent " << bytesWritten
	<< " bytes";

    MLogClient logClient;
    logClient.log(MLogClient::MLOG_ERROR, "",
	"MSyslogClient::sendMessage", __LINE__,
	tmp);
  }

  return 0;
}

void
MSyslogClient::setTestMode(int mode)
{
  mTestMode = mode;
}
