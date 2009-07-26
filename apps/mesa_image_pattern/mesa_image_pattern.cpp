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

static char rcsid[] = "$Revision: 1.9 $ $RCSfile: mesa_image_pattern.cpp,v $";

#include "MESA.hpp"

#include <iomanip>
#include <vector>
#include <fstream>

static void usage()
{
  char msg[] = "\
Usage: pattern file \n\
\n\
  pattern     Pattern number (1, 2, ...)\n\
  file        Output file";

  cerr << msg << endl;
  ::exit(1);
}

unsigned char* pattern1(unsigned long& byteCount)
{
  unsigned short *p = new unsigned short[256 * 256 * 2];
  byteCount = 256 * 256 * 4;
  memset(p, 0, 256 * 256 * 4);
  int row = 0;
  int col = 0;
  
  unsigned short *p0;
  unsigned short *p1;

  p0 = &p[0];
  p1 = &p[256*256*1];

  for (row = 106; row < 150; row++) {
    for (col = 0; col < 44; col++) {
      p0[row*256 + col] = 1279;
    }
  }

  for (row = 0; row < 44; row++) {
    for (col = 106; col < 150; col++) {
      p1[row*256 + col] = 1279;
    }
  }

  return (unsigned char*)p;
}

unsigned char* pattern2(unsigned long& byteCount)
{
  unsigned short *p = new unsigned short[256 * 256 * 12];
  byteCount = 256 * 256 * 24;
  memset(p, 0, 256 * 256 * 24);
  int row = 0;
  int col = 0;
  
  unsigned short *p0;
  unsigned short *p1;
  unsigned short *p2;
  unsigned short *p3;
  unsigned short *p4;
  unsigned short *p5;
  unsigned short *p6;
  unsigned short *p7;
  unsigned short *p8;
  unsigned short *p9;
  unsigned short *p10;
  unsigned short *p11;

  p0 = &p[0];
  p1 = &p[256*256*1];
  p2 = &p[256*256*2];
  p3 = &p[256*256*3];
  p4 = &p[256*256*4];
  p5 = &p[256*256*5];
  p6 = &p[256*256*6];
  p7 = &p[256*256*7];
  p8 = &p[256*256*8];
  p9 = &p[256*256*9];
  p10 = &p[256*256*10];
  p11 = &p[256*256*11];

  for (row = 106; row < 150; row++) {
    for (col = 0; col < 44; col++) {
      p0[row*256 + col] = 1279;
    }
  }

  for (row = 106; row < 150; row++) {
    for (col = 44; col < 88; col++) {
      p1[row*256 + col] = 1279;
    }
  }

  for (row = 106; row < 150; row++) {
    for (col = 88; col < 132; col++) {
      p2[row*256 + col] = 1279;
    }
  }

  for (row = 106; row < 150; row++) {
    for (col = 132; col < 176; col++) {
      p3[row*256 + col] = 1279;
    }
  }

  for (row = 106; row < 150; row++) {
    for (col = 176; col < 220; col++) {
      p4[row*256 + col] = 1279;
    }
  }

  for (row = 106; row < 150; row++) {
    for (col = 220; col < 256; col++) {
      p5[row*256 + col] = 1279;
    }
  }

  for (row = 0; row < 44; row++) {
    for (col = 106; col < 150; col++) {
      p6[row*256 + col] = 1279;
    }
  }

  for (row = 44; row < 88; row++) {
    for (col = 106; col < 150; col++) {
      p7[row*256 + col] = 1279;
    }
  }

  for (row = 88; row < 132; row++) {
    for (col = 106; col < 150; col++) {
      p8[row*256 + col] = 1279;
    }
  }

  for (row = 132; row < 176; row++) {
    for (col = 106; col < 150; col++) {
      p9[row*256 + col] = 1279;
    }
  }

  for (row = 176; row < 220; row++) {
    for (col = 106; col < 150; col++) {
      p10[row*256 + col] = 1279;
    }
  }

  for (row = 220; row < 256; row++) {
    for (col = 106; col < 150; col++) {
      p11[row*256 + col] = 1279;
    }
  }

  return (unsigned char*)p;
}

unsigned char* pattern3(unsigned long& byteCount)
{
  unsigned short *p = new unsigned short[256 * 256 * 18];
  byteCount = 256 * 256 * 36;
  memset(p, 0, 256 * 256 * 36);
  int row = 0;
  int col = 0;
  
  unsigned short *p0;
  unsigned short *p1;
  unsigned short *p2;
  unsigned short *p3;
  unsigned short *p4;
  unsigned short *p5;
  unsigned short *p6;
  unsigned short *p7;
  unsigned short *p8;
  unsigned short *p9;
  unsigned short *p10;
  unsigned short *p11;
  unsigned short *p12;
  unsigned short *p13;
  unsigned short *p14;
  unsigned short *p15;
  unsigned short *p16;
  unsigned short *p17;

  p0 = &p[0];
  p1 = &p[256*256*1];
  p2 = &p[256*256*2];
  p3 = &p[256*256*3];
  p4 = &p[256*256*4];
  p5 = &p[256*256*5];
  p6 = &p[256*256*6];
  p7 = &p[256*256*7];
  p8 = &p[256*256*8];
  p9 = &p[256*256*9];
  p10 = &p[256*256*10];
  p11 = &p[256*256*11];
  p12 = &p[256*256*12];
  p13 = &p[256*256*13];
  p14 = &p[256*256*14];
  p15 = &p[256*256*15];
  p16 = &p[256*256*16];
  p17 = &p[256*256*17];

  for (row = 10; row < 20; row++) {
    for (col = 10; col < 20; col++) {
      p0[row*256 + col] = 1279;
    }
  }

  for (row = 10; row < 30; row++) {
    for (col = 10; col < 30; col++) {
      p1[row*256 + col] = 1279;
    }
  }

  for (row = 10; row < 40; row++) {
    for (col = 10; col < 40; col++) {
      p2[row*256 + col] = 1279;
    }
  }

  for (row = 10; row < 50; row++) {
    for (col = 10; col < 50; col++) {
      p3[row*256 + col] = 1279;
    }
  }

  for (row = 10; row < 60; row++) {
    for (col = 10; col < 60; col++) {
      p4[row*256 + col] = 1279;
    }
  }

  for (row = 200; row < 210; row++) {
    for (col = 200; col < 210; col++) {
      p5[row*256 + col] = 1279;
    }
  }

  for (row = 200; row < 220; row++) {
    for (col = 200; col < 220; col++) {
      p6[row*256 + col] = 1279;
    }
  }

  for (row = 200; row < 230; row++) {
    for (col = 200; col < 230; col++) {
      p7[row*256 + col] = 1279;
    }
  }

  for (row = 200; row < 240; row++) {
    for (col = 200; col < 240; col++) {
      p8[row*256 + col] = 1279;
    }
  }

  for (row = 200; row < 250; row++) {
    for (col = 200; col < 250; col++) {
      p9[row*256 + col] = 1279;
    }
  }

  for (row = 58; row < 198; row++) {
    for (col = 58; col < 198; col++) {
      p10[row*256 + col] = 1279;
    }
  }

  for (row = 68; row < 188; row++) {
    for (col = 68; col < 188; col++) {
      p11[row*256 + col] = 1279;
    }
  }

  for (row = 78; row < 178; row++) {
    for (col = 78; col < 178; col++) {
      p12[row*256 + col] = 1279;
    }
  }

  for (row = 88; row < 168; row++) {
    for (col = 88; col < 168; col++) {
      p13[row*256 + col] = 1279;
    }
  }

  for (row = 98; row < 158; row++) {
    for (col = 98; col < 150; col++) {
      p14[row*256 + col] = 1279;
    }
  }

  for (row = 108; row < 148; row++) {
    for (col = 108; col < 148; col++) {
      p15[row*256 + col] = 1279;
    }
  }

  for (row = 118; row < 138; row++) {
    for (col = 118; col < 138; col++) {
      p16[row*256 + col] = 1279;
    }
  }

  for (row = 128; row < 128; row++) {
    for (col = 128; col < 128; col++) {
      p17[row*256 + col] = 1279;
    }
  }

  return (unsigned char*)p;
}

unsigned char* pattern4(unsigned long& byteCount)
{
  unsigned short *p = new unsigned short[256 * 256];
  byteCount = 256 * 256 * 2;
  memset(p, 0, 256 * 256 * 2);
  int row = 0;
  int col = 0;
  
  for (row = 0; row < 256; row++) {
    for (col = 0; col < 256; col++) {
      p[row*256 + col] = 512 + col*4;
    }
  }

  return (unsigned char*)p;
}


unsigned char* pattern5(unsigned long& byteCount)
{
  unsigned short *p = new unsigned short[32 * 32];
  byteCount = 32 * 32 * 2;
  memset(p, 0, 32 * 32 * 2);
  int row = 0;
  int col = 0;
  
  for (row = 0; row < 32; row++) {
    for (col = 0; col < 32; col++) {
      p[row*32 + col] = 512 + 16*(row+col);
    }
  }

  return (unsigned char*)p;
}

unsigned char* pattern6(unsigned long& byteCount)
{
  unsigned short *p = new unsigned short[1024 * 256];
  byteCount = 256 * 1024 * 2;
  memset(p, 0, 1024 * 256 * 2);
  int row = 0;
  int col = 0;
  
  for (row = 0; row < 1024; row++) {
    for (col = 0; col < 256; col++) {
      p[row*256 + col] = 512 + 2*col + row/2;
    }
  }

  return (unsigned char*)p;
}



unsigned char* pattern13(unsigned long& byteCount)
{
  unsigned short *p = new unsigned short[256 * 256];
  byteCount = 256 * 256 * 2;
  memset(p, 0, 256 * 256 * 2);
  int row = 0;
  int col = 0;

  for (row = 96; row < 160; row++) {
    for (col = 0; col < 64; col++) {
      p[row*256 + col] = 1024;
      cout << "row: "<< row << endl;
      cout << "col: "<< col << endl;
    }
  }

  for (row = 96; row < 160; row++) {
    for (col = 64; col < 128; col++) {
      p[row*256 + col] = 1100;
      cout << "row: "<< row << endl;
      cout << "col: "<< col << endl;
    }
  }

  for (row = 96; row < 160; row++) {
    for (col = 128; col < 192; col++) {
      p[row*256 + col] = 1279;
      cout << "row: "<< row << endl;
      cout << "col: "<< col << endl;
    }
  }

  for (row = 96; row < 160; row++) {
    for (col = 192; col < 256; col++) {
      p[row*256 + col] = 1100;
      cout << "row: "<< row << endl;
      cout << "col: "<< col << endl;
    }
  }
  return (unsigned char*)p;
}

unsigned char* pattern14(unsigned long& byteCount)
{
  unsigned short *p = new unsigned short[256 * 256];
  byteCount = 256 * 256 * 2;
  memset(p, 0, 256 * 256 * 2);
  int row = 0;
  int col = 0;

  for (row = 0; row < 64; row++) {
    for (col = 96; col < 160; col++) {
      p[row*256 + col] = 1024;
      cout << "row: "<< row << endl;
      cout << "col: "<< col << endl;
    }
  }

  for (row = 64; row < 128; row++) {
    for (col = 96; col < 160; col++) {
      p[row*256 + col] = 1100;
      cout << "row: "<< row << endl;
      cout << "col: "<< col << endl;
    }
  }

  for (row = 128; row < 192; row++) {
    for (col = 96; col < 160; col++) {
      p[row*256 + col] = 1279;
      cout << "row: "<< row << endl;
      cout << "col: "<< col << endl;
    }
  }

  for (row = 192; row < 256; row++) {
    for (col = 96; col < 160; col++) {
      p[row*256 + col] = 1100;
      cout << "row: "<< row << endl;
      cout << "col: "<< col << endl;
    }
  }
  return (unsigned char*)p;
}



int main(int argc, char **argv)
{
  int patternNumber;
  char* outputFile = 0;
  bool verbose = false;

  while (--argc > 0 && (*++argv)[0] == '-') {
    switch (*(argv[0] + 1)) {
    case 'v':
      verbose = true;
      break;
    default:
      break;
    }
  }

  if (argc < 2)
    usage();

  patternNumber = atoi(*argv++);
  outputFile = *argv++;

  unsigned char* pixels = 0;
  unsigned long byteCount = 0;

  switch(patternNumber) {
  case 1:
    pixels = pattern1(byteCount);
    break;
  case 2:
    pixels = pattern2(byteCount);
    break;
  case 3:
    pixels = pattern3(byteCount);
    break;
  case 4:
    pixels = pattern4(byteCount);
    break;
  case 5:
    pixels = pattern5(byteCount);
    break;
  case 6:
    pixels = pattern6(byteCount);
    break;
  case 13:
    pixels = pattern13(byteCount);
    break;
  case 14:
    pixels = pattern14(byteCount);
    break;
  default:
    cout << "Unrecognized pattern number: " << patternNumber << endl;
    return 1;
  }

  ofstream f;
  f.open(outputFile, ios::binary);

  f.write((const char*)pixels, byteCount);
  f.close();
  delete []pixels;
  return 0;
}
