# Microsoft Developer Studio Generated NMAKE File, Based on of_dcmps_secure.dsp
!IF "$(CFG)" == ""
CFG=of_dcmps_secure - Win32 Debug
!MESSAGE No configuration specified. Defaulting to of_dcmps_secure - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "of_dcmps_secure - Win32 Release" && "$(CFG)" != "of_dcmps_secure - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "of_dcmps_secure.mak" CFG="of_dcmps_secure - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "of_dcmps_secure - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "of_dcmps_secure - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "of_dcmps_secure - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\of_dcmps_secure.exe"


CLEAN :
	-@erase "$(INTDIR)\MLMPPS.obj"
	-@erase "$(INTDIR)\MLQuery.obj"
	-@erase "$(INTDIR)\MLStorageCommitment.obj"
	-@erase "$(INTDIR)\of_dcmps_secure.obj"
	-@erase "$(INTDIR)\sscond.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\of_dcmps_secure.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /GX /O2 /I "..\..\..\..\ctn\include" /I "..\..\..\include" /I "..\..\..\..\openssl-0.9.8k\inc32" /I "..\..\..\apps\of_dcmps" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\of_dcmps_secure.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\of_dcmps_secure.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mesa_lib.lib mesa_lib_secure.lib ssleay32.lib libeay32.lib  wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\of_dcmps_secure.pdb" /machine:I386 /out:"$(OUTDIR)\of_dcmps_secure.exe" /libpath:"..\..\..\winmesa\mesa_lib\Debug" /libpath:"..\..\..\winmesa\mesa_lib_secure\Release" /libpath:"..\..\..\..\openssl-0.9.8k\out32dll" 
LINK32_OBJS= \
	"$(INTDIR)\MLMPPS.obj" \
	"$(INTDIR)\MLQuery.obj" \
	"$(INTDIR)\MLStorageCommitment.obj" \
	"$(INTDIR)\of_dcmps_secure.obj" \
	"$(INTDIR)\sscond.obj"

"$(OUTDIR)\of_dcmps_secure.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "of_dcmps_secure - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\of_dcmps_secure.exe"


CLEAN :
	-@erase "$(INTDIR)\MLMPPS.obj"
	-@erase "$(INTDIR)\MLQuery.obj"
	-@erase "$(INTDIR)\MLStorageCommitment.obj"
	-@erase "$(INTDIR)\of_dcmps_secure.obj"
	-@erase "$(INTDIR)\sscond.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\of_dcmps_secure.exe"
	-@erase "$(OUTDIR)\of_dcmps_secure.ilk"
	-@erase "$(OUTDIR)\of_dcmps_secure.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\ctn\include" /I "..\..\..\include" /I "..\..\..\..\openssl-0.9.8k\inc32" /I "..\..\..\apps\of_dcmps" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\of_dcmps_secure.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\of_dcmps_secure.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mesa_lib.lib mesa_lib_secure.lib ssleay32.lib libeay32.lib  wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\of_dcmps_secure.pdb" /debug /machine:I386 /out:"$(OUTDIR)\of_dcmps_secure.exe" /pdbtype:sept /libpath:"..\..\..\winmesa\mesa_lib\Debug" /libpath:"..\..\..\winmesa\mesa_lib_secure\Debug" /libpath:"..\..\..\..\openssl-0.9.8k\out32dll" 
LINK32_OBJS= \
	"$(INTDIR)\MLMPPS.obj" \
	"$(INTDIR)\MLQuery.obj" \
	"$(INTDIR)\MLStorageCommitment.obj" \
	"$(INTDIR)\of_dcmps_secure.obj" \
	"$(INTDIR)\sscond.obj"

"$(OUTDIR)\of_dcmps_secure.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("of_dcmps_secure.dep")
!INCLUDE "of_dcmps_secure.dep"
!ELSE 
!MESSAGE Warning: cannot find "of_dcmps_secure.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "of_dcmps_secure - Win32 Release" || "$(CFG)" == "of_dcmps_secure - Win32 Debug"
SOURCE=..\..\..\apps\of_dcmps\MLMPPS.cpp

"$(INTDIR)\MLMPPS.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\apps\of_dcmps\MLQuery.cpp

"$(INTDIR)\MLQuery.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\apps\of_dcmps\MLStorageCommitment.cpp

"$(INTDIR)\MLStorageCommitment.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\secure_apps\of_dcmps_secure\of_dcmps_secure.cpp

"$(INTDIR)\of_dcmps_secure.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\apps\of_dcmps\sscond.cpp

"$(INTDIR)\sscond.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

