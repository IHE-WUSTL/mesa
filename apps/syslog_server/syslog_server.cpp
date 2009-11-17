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

#include "ctn_os.h"
#include <fstream>

#include "MESA.hpp"

#include "MAcceptor.hpp"
#include "MSyslogMessage.hpp"
#include "MSyslogMessage5424.hpp"
#include "MSyslogFactory.hpp"
#include "MFileOperations.hpp"
#include "MDBSyslogManager.hpp"
#include "MLogClient.hpp"
#include "MSyslogDomainXlate.hpp"
#include "MSyslogEntry.hpp"
#include "MNetworkProxy.hpp"
#include "MNetworkProxyTCP.hpp"
#ifdef RFC5425
#include "MNetworkProxyTLS.hpp"
#endif

using namespace std;

static void usage()
{
  char msg[] = "\
Usage: [-C cert] [-d db] [-K key] [-l level] [-P peer] [-R randoms] [-r rfc] [-v] [-x rfc] port\n\
\n\
  -C   File containing certificate for this application\n\
  -d   Set database name to store messages; default is syslog \n\
  -K   File containing private key for this application\n\
  -l   Set loglevel (0-4); default is 1 (error) \n\
  -P   File with list of peer certificates (might just be CA certificate\n\
  -R   File containing random numbers to initialze toolkit\n\
  -r   Receive messages formatted according to RFC (e.g., 5424)\n\
  -x   Use RFC as transmission mode (0, 5425, 5426)\n\
  -v   Enable verbose mode \n\
\n\
  port UDP port number of server";

  cerr << msg << endl;
  ::exit(1);
}

static void
dumpToFolder(const char* logPath, const char* remoteNode, char* transport, const char* buffer, const unsigned char* payload)
{
  MLogClient logClient;
  char date[20] = "";
  char time[30] = "";
  ::UTL_GetDicomDate(date);
  ::UTL_GetDicomTime(time);
  time[6] = '\0';
  MFileOperations f;

  char hostFolder[1024] = "";
  ::sprintf(hostFolder, "%s/%s", logPath, remoteNode);
  f.createDirectory(logPath);
  f.createDirectory(hostFolder);

  {
    char fileName[1024] = "";
    ::sprintf(fileName, "%s/%s_%s_%s_packet.txt", hostFolder, date, time, transport);
    ofstream thisMessage(fileName, ios_base::trunc);
    thisMessage << buffer;
    thisMessage.close();
  }
  {
    char fileName[1024] = "";
    ::sprintf(fileName, "%s/%s_%s_%s_payload.txt", hostFolder, date, time, transport);
    ofstream thisMessage(fileName, ios_base::trunc);
    thisMessage << payload;
    thisMessage.close();
  }
  {
    char fileName[1024] = "";
    ::sprintf(fileName, "%s/last_log.txt", logPath);
    ofstream thisMessage(fileName, ios_base::trunc);
    thisMessage << buffer;
    thisMessage.close();
  }
  bool bom = true;
  if (payload[0] != 0xef) bom = false;
  if (payload[1] != 0xbb) bom = false;
  if (payload[2] != 0xbf) bom = false;

  const unsigned char* p = payload;
  if (bom) p += 3;

  {
    char fileName[1024] = "";
    ::sprintf(fileName, "%s/%s_%s_%s_payload.xml", hostFolder, date, time, transport);
    ofstream thisMessage(fileName, ios_base::trunc);
    thisMessage << p;
    thisMessage.close();
    if (!bom) {
      logClient.logTimeStamp(MLogClient::MLOG_WARN, "Expected to find BOM at the front of this payload, but did not");
      logClient.logTimeStamp(MLogClient::MLOG_WARN, MString("Please inspect the file: ") + fileName);
    }
  }
  {
    char fileName[1024] = "";
    ::sprintf(fileName, "%s/last_log.xml", logPath);
    ofstream thisMessage(fileName, ios_base::trunc);
    thisMessage << p;
    thisMessage.close();
  }
}

static int
processUDPPackets(CTN_SOCKET s, char* logPath, const MString& syslogDBName, int rfcType)
{
  MLogClient logClient;
  struct sockaddr client_addr;
  char buffer[32768];
  int bytesRead;
#ifdef MESA_USE_SOCKLEN_T
  socklen_t length;
#else
  int length;
#endif
  MSyslogFactory factory;
  char fileLastLog[32768];
  char fileLastXML[32768];

  ::sprintf(fileLastLog, "%s/last_log.txt", logPath);
  ::sprintf(fileLastXML, "%s/last_log.xml", logPath);

  MDBSyslogManager* mgr = 0;
  if (syslogDBName != "") {
    mgr = new MDBSyslogManager;
    if (mgr == 0) {
	logClient.log(MLogClient::MLOG_ERROR, "no peer",
		"processUDPPackets", __LINE__,
		"unable to allocate new Syslog Manager");
      return 1;
    }
    if (mgr->initialize(syslogDBName) != 0) {
	logClient.log(MLogClient::MLOG_ERROR, "no peer",
		"processUDPPackets", __LINE__,
		"unable to initialize Syslog database: ", syslogDBName);
      return 1;
    }
  }

  MSyslogDomainXlate xlate;

  while(1) {
    length = sizeof(client_addr);
    memset(&client_addr, 0, length);

    bytesRead = ::recvfrom(s, buffer, sizeof(buffer),
		0, &client_addr, &length);
    if (bytesRead < 0) {
      logClient.log(MLogClient::MLOG_ERROR, "",
		"processUDPPackets", __LINE__,
		MString("unable to receive packet from socket"));
      ::perror("Reading datagram");
      continue;
    }
    buffer[bytesRead] = '\0';

    char remoteNode[512];
    struct hostent* hp = 0;
    hp = ::gethostbyaddr(&client_addr.sa_data[2], 4, 2);
    if (hp == 0) {
      ::sprintf(remoteNode, "%-d.%-d.%-d.%-d",
		((int) client_addr.sa_data[2]) & 0xff,
		((int) client_addr.sa_data[3]) & 0xff,
		((int) client_addr.sa_data[4]) & 0xff,
		((int) client_addr.sa_data[5]) & 0xff);
    } else {
      ::strcpy(remoteNode, hp->h_name);
    }
    logClient.log(MLogClient::MLOG_CONVERSATION, "remoteNode",
		"processUDPPackets", __LINE__,
		"syslog buffer is: ", buffer);

    //cout << "Remote node: " << remoteNode << endl;
    //cout << buffer << endl;

    if (rfcType == 5424) {
      MSyslogMessage5424* m = factory.produceMessage5424(buffer, bytesRead);
      if (m == 0) {
        logClient.log(MLogClient::MLOG_ERROR, "remoteNode",
		"processUDPPackets", __LINE__,
		"unable to parse the syslog stream in current packet;",
		" most likely cause is a header that confused our parser");
        continue;
      } else {
        //cout << *m << endl;
      }
      unsigned long messageLength = 0;
      const char* ref = m->referenceToMessage(messageLength);
      if (::strncmp(ref, "<SHUTDOWN/>", messageLength) == 0) {
        delete m;
        break;
      }
      if (::strncmp(ref+3, "<SHUTDOWN/>", messageLength-3) == 0) {
        delete m;
        break;
      }

      dumpToFolder(logPath, remoteNode, "5426", buffer, (unsigned char*)ref);

#if 0
      if (mgr != 0) {
        MSyslogEntry entry;
        if (xlate.translateSyslog(*m, entry) == 0) {
	  logClient.log(MLogClient::MLOG_VERBOSE, remoteNode,
		"processUDPPackets", __LINE__,
		"about to enter new entry");
	  mgr->enterRecord(entry);
        }
      }
#endif
      delete m;
      logClient.log(MLogClient::MLOG_VERBOSE, remoteNode,
		"processUDPPackets", __LINE__,
		"Finished processing current packet");
    } else {
      MSyslogMessage* m = factory.produceMessage(buffer, bytesRead);
      if (m == 0) {
        logClient.log(MLogClient::MLOG_ERROR, "remoteNode",
		"processUDPPackets", __LINE__,
		"unable to parse the syslog stream in current packet;",
		" most likely cause is a header that confused our parser");
        continue;
      } else {
        //cout << *m << endl;
      }
      unsigned long messageLength = 0;
      const char* ref = m->referenceToMessage(messageLength);
      if (::strncmp(ref, "<SHUTDOWN/>", messageLength) == 0) {
        delete m;
        break;
      }

      if (mgr != 0) {
        MSyslogEntry entry;
        if (xlate.translateSyslog(*m, entry) == 0) {
	  logClient.log(MLogClient::MLOG_VERBOSE, remoteNode,
		"processUDPPackets", __LINE__,
		"about to enter new entry");
	  mgr->enterRecord(entry);
        }
      }
      delete m;
      logClient.log(MLogClient::MLOG_VERBOSE, remoteNode,
		"processUDPPackets", __LINE__,
		"Finished processing current packet");
    }
  }
  return 0;
}

static int
processTCPPackets(MNetworkProxy& n, char* logPath, const MString& syslogDBName, int rfcType)
{
  MLogClient logClient;
  struct sockaddr client_addr;
  char buffer[32768];
  int bytesRead;
#ifdef MESA_USE_SOCKLEN_T
  socklen_t length;
#else
  int length;
#endif
  MSyslogFactory factory;
//  char fileLastLog[32768];
//  char fileLastXML[32768];

//  ::sprintf(fileLastLog, "%s/last_log.txt", logPath);
//  ::sprintf(fileLastXML, "%s/last_log.xml", logPath);

  MDBSyslogManager* mgr = 0;
  if (syslogDBName != "") {
    mgr = new MDBSyslogManager;
    if (mgr == 0) {
	logClient.log(MLogClient::MLOG_ERROR, "no peer",
		"processUDPPackets", __LINE__,
		"unable to allocate new Syslog Manager");
      return 1;
    }
    if (mgr->initialize(syslogDBName) != 0) {
	logClient.log(MLogClient::MLOG_ERROR, "no peer",
		"processUDPPackets", __LINE__,
		"unable to initialize Syslog database: ", syslogDBName);
      return 1;
    }
  }

  MSyslogDomainXlate xlate;
  while (1) {
    MString remoteHost = "";
    if (n.acceptConnection(remoteHost, -1) != 0) {
      logClient.logTimeStamp(MLogClient::MLOG_ERROR, "Unable to receive TCP connection");
      return 1;
    }
    bool socketOpen = true;
    char buffer[16384] = "";
    char tmpBuffer[1024] = "";
    int ix = 0;
    int bytesRead = 0;
    int toRead = 0;
    while ((bytesRead = n.readBytes(tmpBuffer+ix, 1)) > 0) {
      if (tmpBuffer[ix] == ' ') {
	tmpBuffer[ix] = '\0';
	MString xx(tmpBuffer);
	toRead = xx.intData();
	break;
      }
      ix++;
    }
    if (bytesRead <= 0) {
      logClient.logTimeStamp(MLogClient::MLOG_ERROR, "Socket closed reading msg length");
      socketOpen = false;
      break;
    }
    ix = 0;
    while (socketOpen && (toRead > 0) &&((bytesRead = n.readBytes(buffer+ix, toRead))) > 0) {
      buffer[ix + bytesRead] = '\0';
      ix += bytesRead;
      toRead -= bytesRead;
    }
    if (bytesRead <= 0) {
      socketOpen = false;
      cout << "Socket closed reading msg length" << endl;
    } else {

      char remoteNode[512]="";
      remoteHost.safeExport(remoteNode, sizeof remoteNode);

      logClient.log(MLogClient::MLOG_CONVERSATION, "remoteNode",
		"processUDPPackets", __LINE__,
		"syslog buffer is: ", buffer);

      if (rfcType == 5424) {
	MSyslogMessage5424* m = factory.produceMessage5424(buffer, bytesRead);
	if (m == 0) {
          logClient.log(MLogClient::MLOG_ERROR, "remoteNode",
		"processTCPPackets", __LINE__,
		"unable to parse the syslog stream in current packet;",
		" most likely cause is a header that confused our parser");
	  continue;
	} else {
	  //cout << *m << endl;
	}
	unsigned long messageLength = 0;
	const char* ref = m->referenceToMessage(messageLength);
	if (::strncmp(ref, "<SHUTDOWN/>", messageLength) == 0) {
	  delete m;
	  break;
	}
	if (::strncmp(ref+3, "<SHUTDOWN/>", messageLength-3) == 0) {
	  delete m;
	  break;
	}
	dumpToFolder(logPath, remoteNode, "5425", buffer, (unsigned char*)ref);

#if 0
	if (mgr != 0) {
	  MSyslogEntry entry;
	  if (xlate.translateSyslog(*m, entry) == 0) {
	    logClient.log(MLogClient::MLOG_VERBOSE, remoteNode,
		"processUDPPackets", __LINE__,
		"about to enter new entry");
	    mgr->enterRecord(entry);
	  }
	}
#endif
	delete m;
	logClient.log(MLogClient::MLOG_VERBOSE, remoteNode,
		"processUDPPackets", __LINE__,
		"Finished processing current packet");
      } else {
	MSyslogMessage* m = factory.produceMessage(buffer, bytesRead);
	if (m == 0) {
	  logClient.log(MLogClient::MLOG_ERROR, "remoteNode",
		"processUDPPackets", __LINE__,
		"unable to parse the syslog stream in current packet;",
		" most likely cause is a header that confused our parser");
	  continue;
	} else {
	  //cout << *m << endl;
	}
	unsigned long messageLength = 0;
	const char* ref = m->referenceToMessage(messageLength);
	if (::strncmp(ref, "<SHUTDOWN/>", messageLength) == 0) {
	  delete m;
	  break;
	}

	if (mgr != 0) {
	  MSyslogEntry entry;
	  if (xlate.translateSyslog(*m, entry) == 0) {
	  logClient.log(MLogClient::MLOG_VERBOSE, remoteNode,
		"processUDPPackets", __LINE__,
		"about to enter new entry");
	  mgr->enterRecord(entry);
	  }
	}
	delete m;
	logClient.log(MLogClient::MLOG_VERBOSE, remoteNode,
		"processUDPPackets", __LINE__,
		"Finished processing current packet");
      }
    }
  }

  return 0;
}

int main(int argc, char** argv)
{ 
  bool verbose = false;
  MString syslogDBName("syslog");
  MFileOperations f;
  char path[256];
  int rfcType = 0;
  MString xmitRFC = "3164";
  MString randomsFile = "";
  MString keyFile = "";
  MString certificateFile = "";
  MString peerCertificateList = "";
  MString ciphers = "NULL-SHA";


  f.expandPath(path, "MESA_TARGET", "logs");
  MString logDir(path);
  MLogClient::LOGLEVEL logLevel = MLogClient::MLOG_ERROR;
 
  while (--argc > 0 && (*++argv)[0] == '-') {
    int l1 = 0;
    switch(*(argv[0] + 1)) {
    case 'C':
      argc--; argv++;
      if (argc < 1)
	usage();
      certificateFile = *argv;
      break;
    case 'd':
      argc--; argv++;
      if (argc < 1)
	usage();
      syslogDBName = *argv;
      break;
    case 'K':
      argc--; argv++;
      if (argc < 1)
	usage();
      keyFile = *argv;
      break;

    case 'l':
      argc--; argv++;
      if (argc < 1)
	usage();
      if (::sscanf(*argv, "%d", &l1) != 1)
	usage();
      logLevel = (MLogClient::LOGLEVEL)l1;
      break;
    case 'P':
      argc--; argv++;
      if (argc < 1)
	usage();
      peerCertificateList = *argv;
      break;
    case 'R':
      argc--; argv++;
      if (argc < 1)
	usage();
      randomsFile = *argv;
      break;

    case 'r':
      argc--; argv++;
      if (argc < 1)
	usage();
      if (::sscanf(*argv, "%d", &l1) != 1)
	usage();
      rfcType = l1;
      break;

    case 'v':
      verbose = true;
      break;

    case 'x':
      argc--; argv++;
      if (argc < 1)
	usage();
      xmitRFC = *argv;
      break;

    default:
      break;
    }
  }
  if (argc < 1)
    usage();

  char logPath[1024];
  if (f.expandPath(logPath, "MESA_TARGET", "logs/syslog") != 0) {
    cout << "Unable to expand path for $MESA_TARGET/logs" << endl;
    return 1;
  }

  if (f.createDirectory(logPath) != 0) {
    cout << "Unable to create directory: " << logPath << endl;
    return 1;
  }

  MLogClient logClient;
  if (logLevel != MLogClient::MLOG_NONE) {
    MString logName = logDir + "/syslog_server.log";
    if      (xmitRFC == "3164") logName = logDir + "/syslog_server_3164.log";
    else if (xmitRFC == "5425") logName = logDir + "/syslog_server_5425.log";
    else if (xmitRFC == "5426") logName = logDir + "/syslog_server_5426.log";
    else if (xmitRFC == "TCP")  logName = logDir + "/syslog_server_TCP.log";

    logClient.initialize(logLevel, logName);

    logClient.log(MLogClient::MLOG_VERBOSE,
                  "<no peer>", "syslog_server<main>", __LINE__,
                  "Begin server process");
    cerr << "syslog_server logging messages at level "
         << logLevel
         << " to "
         << logName
         << endl;
  }

  int port = atoi(*argv);
  MNetworkProxy* networkProxy = 0;

  MAcceptor acc;
  CTN_SOCKET s = 0;

  if (xmitRFC == "TCP") {
    networkProxy = new MNetworkProxyTCP;
    if (networkProxy->registerPort(port) != 0) {
      logClient.logTimeStamp(MLogClient::MLOG_ERROR, "Unable to initialize TCP listening port");
      return 1;
    }
    processTCPPackets(*networkProxy, logPath, syslogDBName, rfcType);

  } else if (xmitRFC=="3164") {
    if (acc.bindUDPListener(s, port) != 0) {
      cout << "Unable to bind to UDP port: " << port << endl;
      return 1;
    }
    processUDPPackets(s, logPath, syslogDBName, rfcType);

  } else if (xmitRFC=="5426") {
    if (acc.bindUDPListener(s, port) != 0) {
      cout << "Unable to bind to UDP port: " << port << endl;
      return 1;
    }
    processUDPPackets(s, logPath, syslogDBName, rfcType);

  } else if (xmitRFC=="5425") {
#ifdef RFC5425
    MNetworkProxyTLS proxyTLS = new MNetworkProxyTLS;
//    networkProxy = proxyTLS;
    MString proxyParams =
	randomsFile + ","
	+ keyFile + ","
	+ certificateFile + ","
	+ peerCertificateList + ","
	+ ciphers;
    if (proxyTls->initializeServer(proxyParams) != 0) {
      logClient.logTimeStamp(MLogClient::MLOG_ERROR,
	MString("Unable to initialize TLS proxy class with params: ") + proxyParams);
      return 1;
    }
    if (proxyTLS->registerPort(port) != 0) {
      logClient.logTimeStamp(MLogClient::MLOG_ERROR, "Unable to initialize TCP/TLS listening port");
      return 1;
    }
    processTCPPackets(*proxyTLS, logPath, syslogDBName, rfcType);
    delete proxyTLS;
#else
    cout << "syslog server not ready for RFC 5425" << endl;
    return 1;
#endif
  } else {
    cout << "Unrecognized transport specification: " << xmitRFC << endl;
    return 1;
  }

  return 0;
}
