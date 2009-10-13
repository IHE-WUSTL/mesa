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

// Pattern 1
// 256 x 256 x 16 bits x 2 slices
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

// Pattern 2
// 256 x 256 x 16 bits x 12 slices
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

// Pattern 3
// 256 x 256 x 16 bits x 18 slices
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

// Pattern 4
// 256 x 256 x 16 bits
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


// Pattern 5
// 32 x 32 x 16 bits
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

// Pattern 6
// 1024 x 256 x 16 bits
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



// Pattern 13
// 256 x 256 x 16 bits
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

// Pattern 14
// 256 x 256 x 16 bits
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

// Pattern 20
// 1024 x 1024 x 2 bytes, 10 bit wedge, CR data
unsigned char* pattern20(unsigned long& byteCount)
{
  unsigned short *p = new unsigned short[1024 * 1024];
  byteCount = 1024 * 1024 * 2;
  memset(p, 0, byteCount);
  int row = 0;
  int col = 0;
  
  for (row = 0; row < 1024; row++) {
    for (col = 0; col < 750; col++) {
      p[row*1024 + col] = col;
    }
    for (col = 750; col < 1024; col++) {
      p[row*1024 + col] = (2*750)-col;
    }
  }

  return (unsigned char*)p;
}

// Pattern 21
// 256 x 256 x 8 bits x 32 frames
unsigned char* pattern21(const char* outputFile, unsigned long& byteCount)
{
  unsigned char *p = new unsigned char[256 * 256];
  byteCount = 256 * 256;
  memset(p, 0, 256 * 256);
  int row000 = 0;
  int col = 0;
  int frame = 0;
  
  ofstream f;
  f.open(outputFile, ios::binary);

  for (frame = 0; frame < 32; frame++) {
    for (row000 = 0; row000 < 64; row000++) {
      for (col = 0; col < 256; col++) {
	int row064 = row000+64;
	int row128 = row000+128;
	int row192 = row000+192;
	p[row000*256 + col] = 0;
	p[row064*256 + col] = 64;
	p[row128*256 + col] = 128;
	p[row192*256 + col] = 192;
      }
    }
    for (row000 = 16; row000 < 48; row000++) {
      for (col = 0; col < 32; col++) {
	p[(row000*256 + col+10) + (frame*6)] = 250;
      }
    }

    f.write((const char*)p, byteCount);
  }
  f.close();
  delete []p;

  byteCount = 0;
  return (unsigned char*)0;
}

// Pattern 22
// 512 x 256 x 16 bits x 32 frames
unsigned char* pattern22(const char* outputFile, unsigned long& byteCount)
{
  unsigned short *p = new unsigned short[512 * 256];
  byteCount = 512 * 256 * 2;
  memset(p, 0, 512 * 256 * 2);
  int row000 = 0;
  int col = 0;
  int frame = 0;
  
  ofstream f;
  f.open(outputFile, ios::binary);

  for (frame = 0; frame < 32; frame++) {
    for (row000 = 0; row000 < 64; row000++) {
      for (col = 0; col < 256; col++) {
	int row064 = row000+64;
	int row128 = row000+128;
	int row192 = row000+192;
	int row256 = row000+256;
	int row320 = row000+320;
	int row384 = row000+384;
	int row448 = row000+448;
	p[row000*256 + col] = 512;
	p[row064*256 + col] = 1024;
	p[row128*256 + col] = 1536;
	p[row192*256 + col] = 2048;
	p[row256*256 + col] = 0;
	p[row320*256 + col] = 1024;
	p[row384*256 + col] = 2048;
	p[row448*256 + col] = 4095;
      }
    }
    for (row000 = 16; row000 < 48; row000++) {
      for (col = 0; col < 32; col++) {
	p[(row000*256 + col+10) + (frame*6)] = 4095;
      }
    }

    f.write((const char*)p, byteCount);
  }
  f.close();
  delete []p;

  byteCount = 0;
  return (unsigned char*)0;
}

// Pattern 23A
// 256 x 256 x 1 bit x 32 frames
unsigned char* pattern23A(const char* outputFile, unsigned long& byteCount)
{
  unsigned char *p = new unsigned char[256 * 256];
  byteCount = 256 * 256;
  memset(p, 0, 256 * 256);
  int row000 = 0;
  int col = 0;
  int frame = 0;
  
  ofstream f;
  f.open(outputFile, ios::binary);

  for (frame = 0; frame < 32; frame++) {
    memset(p, 0, 256*256);
    for (row000 = 0; row000 < 255; row000++) {
      col = row000;
      p[row000*256 + col] = 200;
      col = 255 - row000;
      p[row000*256 + col] = 200;
    }
    for (row000 = 16; row000 < 48; row000++) {
      for (col = 0; col < 32; col++) {
	p[(row000*256 + col+10) + (frame*6)] = 250;
      }
    }

    f.write((const char*)p, byteCount);
  }
  f.close();
  delete []p;

  byteCount = 0;
  return (unsigned char*)0;
}

// Pattern 23
// 256 x 256 x 1 bit x 32 frames
unsigned char* pattern23(const char* outputFile, unsigned long& byteCount)
{
  unsigned char *p = new unsigned char[256 * 32];
  byteCount = 256 * 32;
  memset(p, 0, 256 * 32);
  int row000 = 0;
  int col = 0;
  int frame = 0;
  
  ofstream f;
  f.open(outputFile, ios::binary);

  for (frame = 0; frame < 32; frame++) {
    memset(p, 0, 256*32);
    for (row000 = 0; row000 < 255; row000++) {
      int rowOffset = row000*32;
      int colOffset = row000/8;
      p[rowOffset + colOffset] = 255;
      colOffset = 31 - row000/8;
      p[rowOffset + colOffset] = 255;
    }
//    for (row000 = 16; row000 < 48; row000++) {
//      for (col = 0; col < 32; col++) {
//	p[(row000*256 + col+10) + (frame*6)] = 250;
//      }
//    }

    f.write((const char*)p, byteCount);
  }
  f.close();
  delete []p;

  byteCount = 0;
  return (unsigned char*)0;
}

// Pattern 24
// 256 x 256 x 8 bits x 3 bytes (RGB) x 96 frames
unsigned char* pattern24(const char* outputFile, unsigned long& byteCount)
{
  unsigned char *p = new unsigned char[256 * 256 * 3];
  byteCount = 256 * 256 * 3;
  memset(p, 0, byteCount);
  int row000 = 0;
  int col = 0;
  int frame = 0;
  
  ofstream f;
  f.open(outputFile, ios::binary);

  // Frames 0-31 are red background with a blue square moving around
  for (frame = 0; frame < 32; frame++) {
    for (row000 = 0; row000 < 256; row000++) {
      for (col = 0; col < 256; col++) {
	p[row000*256*3 + col*3] = 255;				// Red
	p[row000*256*3 + col*3 + 1] = (unsigned char) row000;	// Green
	p[row000*256*3 + col*3 + 2] = (unsigned char) row000;	// Blue
      }
    }
    for (row000 = 200; row000 < 231; row000++) {
      for (col = 0; col < 32; col++) {
	p[((row000*256 + col+10) + (frame*6))*3] = 0;		// Red
	p[((row000*256 + col+10) + (frame*6))*3 + 1] = 0;	// Green
	p[((row000*256 + col+10) + (frame*6))*3 + 2] = 255;	// Blue
      }
    }
    f.write((const char*)p, byteCount);
  }

  // Frames 32-63 are yellow background with a blue square moving around
  for (frame = 0; frame < 32; frame++) {
    for (row000 = 0; row000 < 256; row000++) {
      for (col = 0; col < 256; col++) {
	p[row000*256*3 + col*3]     = 255;		// red
	p[row000*256*3 + col*3 + 1] = 255;	// Green
	p[row000*256*3 + col*3 + 2] = (unsigned char) row000;	// Blue
      }
    }
    for (row000 = 200; row000 < 231; row000++) {
      for (col = 0; col < 32; col++) {
	p[((row000*256 + col+10) + (frame*6))*3] = 0;		// Red
	p[((row000*256 + col+10) + (frame*6))*3 + 1] = 0;	// Green
	p[((row000*256 + col+10) + (frame*6))*3 + 2] = 255;	// Blue
      }
    }
    f.write((const char*)p, byteCount);
  }

  f.close();
  delete []p;

  byteCount = 0;
  return (unsigned char*)0;
}

// Pattern 25
// 512 x 512 x 1 bytes, 8 bit data, pyramid
unsigned char* pattern25(unsigned long& byteCount)
{
  unsigned char *p = new unsigned char[512 * 512];
  byteCount = 512 * 512 * 1;
  memset(p, 0, byteCount);
  int row = 0;
  int col = 0;
  
  unsigned char x;
  for (row = 0; row < 256; row++) {
    for (col = 0; col < 256; col++) {
      x = (col < row) ? col : row;
      p[row*512 + col] = x;
      p[row*512 + 511 - col] = x;

      p[(511-row)*512 + col] = x;
      p[(511-row)*512 + 511 - col] = x;
    }
  }

  return (unsigned char*)p;
}

// Pattern 26
// 512 x 512 x 16 bits, 20 slices of CT data
unsigned char* pattern26(const char* outputFile, unsigned long& byteCount)
{
  short *p = new short[512 * 512];
  byteCount = 512 * 512 * 2;
  int row000 = 0;
  int col = 0;
  int frame = 0;
  
  ofstream f;
  f.open(outputFile, ios::binary);

  // 4 corners
  for (frame = 0; frame < 20; frame++) {
    memset(p, 0, byteCount);
    for (row000 = 0; row000 < 32; row000++) {
      for (col = 0; col < 32; col++) {
	p[row000*512 + col] = 400;
	p[row000*512 + 383-col] = 400;
	p[(row000+480)*512 + col] = 400;
	p[(row000+480)*512 + 383-col] = 400;
	// Add some more squares as markers outside the anatomy
	p[row000*512 + 511-col] = 200;
	p[(row000+240)*512 + 511-col] = 200;
	p[(row000+480)*512 + 511-col] = 200;
      }
    }
    // 2 pixel outline
    for (row000 = 0; row000 < 512; row000++) {
      p[row000*512] = 400;
      p[row000*512+1] = 400;
      p[row000*512 + 382] = 400;
      p[row000*512 + 383] = 400;
    }
    for (col = 0; col < 384; col++) {
      p[col] = 400;
      p[512+col] = 400;
      p[510*512 + col] = 400;
      p[511*512 + col] = 400;
    }
    // 2 rectangles in the center
    for (row000 = 256; row000 < 264 +(frame*3); row000++) {
      for (col = 100; col < 132; col++) {
	p[row000*512 + col] = 400;
      }
    }
    for (row000 = 256; row000 < 320; row000++) {
      for (col = 164; col < 196; col++) {
	p[row000*512 + col] = 400;
      }
    }

    f.write((const char*)p, byteCount);
  }

  f.close();
  delete []p;

  byteCount = 0;
  return (unsigned char*)0;
}

// Pattern 27
// 512 x 512 x 16 bits, 24 slices of CT data
unsigned char* pattern27(const char* outputFile, unsigned long& byteCount)
{
  short *p = new short[512 * 512];
  byteCount = 512 * 512 * 2;
  int row000 = 0;
  int col = 0;
  int frame = 0;
  
  ofstream f;
  f.open(outputFile, ios::binary);

  // 4 corners
  for (frame = 0; frame < 24; frame++) {
    memset(p, 0, byteCount);
    for (row000 = 0; row000 < 32; row000++) {
      for (col = 0; col < 32; col++) {
	p[128+ row000*512 + col] = 400;
	p[128+ row000*512 + 383-col] = 400;
	p[128+ (row000+480)*512 + col] = 400;
	p[128+ (row000+480)*512 + 383-col] = 400;
	// Add some more squares as markers outside the anatomy
	int diag = 0;
	diag = (col < row000) ? col: row000;
	p[row000*512 + diag] = 200;
	p[(row000+240)*512 + diag] = 200;
	p[(row000+480)*512 + diag] = 200;
      }
    }
    // 2 pixel outline
    for (row000 = 0; row000 < 512; row000++) {
      p[128+ row000*512] = 400;
      p[128+ row000*512+1] = 400;
      p[128+ row000*512 + 382] = 400;
      p[128+ row000*512 + 383] = 400;
    }
    for (col = 0; col < 384; col++) {
      p[128+ col] = 400;
      p[128+ 512+col] = 400;
      p[128+ 510*512 + col] = 400;
      p[128+ 511*512 + col] = 400;
    }
    // 3 rectangles in the center
    // In the first four frames, we put a large square. In frames 21-24, a smaller rectangle that is growing.
    if (frame < 4) {
      for (row000 = 128; row000 < 256; row000++) {
	for (col = 300; col < 356; col++) {
	  p[128+ row000*512 + col] = 400;
	}
      }
    }

    for (row000 = 256; row000 < 264 +((frame-4)*3); row000++) {
      for (col = 100; col < 132; col++) {
	p[128+ row000*512 + col] = 400;
      }
    }
    for (row000 = 256; row000 < 320; row000++) {
      for (col = 164; col < 196; col++) {
	p[128+ row000*512 + col] = 400;
      }
    }

    f.write((const char*)p, byteCount);
  }

  f.close();
  delete []p;

  byteCount = 0;
  return (unsigned char*)0;
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
  case 20:		// 1024 x 1024 x 2 bytes, 10 bit wedge, CR data
    pixels = pattern20(byteCount);
    break;
  case 21:		// 256 x 256 x 1 byte, 8 bit step pattern with moving square, multi-frame SC
    pixels = pattern21(outputFile, byteCount);
    break;
  case 22:		// 512 x 256 x 2 byte, 16 bit step pattern with moving square, multi-frame SC
    pixels = pattern22(outputFile, byteCount);
    break;
  case 23:		// 256 x 256 x 1 bit, X pattern with moving square, multi-frame SC
    pixels = pattern23(outputFile, byteCount);
    break;
  case 24:		// 256 x 256 x 8 bit color, 32/96 frames
    pixels = pattern24(outputFile, byteCount);
    break;
  case 25:		// 512 x 512 x 8 bit pyramid
    pixels = pattern25(byteCount);
    break;
  case 26:		// 512 x 512 x 20 CT square patterns
    pixels = pattern26(outputFile, byteCount);
    break;
  case 27:		// 512 x 512 x 24 CT square patterns
    pixels = pattern27(outputFile, byteCount);
    break;
  default:
    cout << "Unrecognized pattern number: " << patternNumber << endl;
    return 1;
  }

  if (byteCount != 0) {
    ofstream f;
    f.open(outputFile, ios::binary);
    f.write((const char*)pixels, byteCount);
    f.close();
    delete []pixels;
  }
  return 0;
}
