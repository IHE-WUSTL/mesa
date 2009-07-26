//
//        Copyright (C) 2002, HIMSS, RSNA and Washington University
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

// File: syslog_server.cpp

#include <iostream>
#include <string>

#include "MESA.hpp"
#include "MSyslogMessage.hpp"
#include "MSyslogClient.hpp"
#include "MFileOperations.hpp"

using namespace std;

static void usage()
{
  char msg[] = "\
Usage: [-c] [-f fac] [-m mode] [-s sev] [-v] host port arg\n\
\n\
  -c     arg is the payload to send \n\
  -f     Set facility in message; default is 10 \n\
  -m     Set mode for syslog client class; default is 0 \n\
  -s     Set severity in message; default is 0 \n\
  -v     Verbose mode \n\
\n\
  host   Host name of system with syslog server \n\
  port   UDP port of syslog server \n\
  arg    Payload or path to file containing message payload ";

  cerr << msg << endl;
  ::exit(1);
}

int main(int argc, char** argv)
{
  int facility = 10;
  int severity = 0;
  int mode = 0;
  bool verbose = false;
  bool isCommand = false;
  MString tmp;
  MString tag = "";

  while (--argc > 0 && (*++argv)[0] == '-') {
    switch(*(argv[0] + 1)) {
    case 'c':
      isCommand = true;
      break;
    case 'f':
      if (argc < 1)
	usage();
      argc--; argv++;
      tmp = *argv;
      facility = tmp.intData();
      break;
    case 'm':
      if (argc < 1)
	usage();
      argc--; argv++;
      tmp = *argv;
      mode = tmp.intData();
      break;
    case 's':
      if (argc < 1)
	usage();
      argc--; argv++;
      tmp = *argv;
      severity = tmp.intData();
      break;
    case 't':
      if (argc < 1)
	usage();
      argc--; argv++;
      tag = *argv;
      break;
 
    case 'v':
      verbose = true;
      break;

    default:
      break;
    }
  }

  if (argc < 3)
    usage();

  char* syslogHost = argv[0];
  tmp = argv[1];
  int syslogPort = tmp.intData();

  MSyslogClient c;
  c.setTestMode(mode);

  int status = c.open(syslogHost, syslogPort);
  if (status != 0) {
    cout << "Unable to connect to server" << endl;
    return 1;
  }

  char* txt;
  if (isCommand) {
    txt = argv[2];
  } else {
    char* path = argv[2];
    MFileOperations f;
    txt = f.readAllText(path);
    if (txt == 0) {
      cout << "Unable to read XML text from: " << path << endl;
      return 1;
    }
  }

  MSyslogMessage m(facility, severity, tag, txt);
  if (!isCommand)
    delete []txt;

  status = c.sendMessage(m);
  if (status != 0) {
    cout << "Unable to send message to server" << endl;
    return 1;
  }

  return 0;
}
