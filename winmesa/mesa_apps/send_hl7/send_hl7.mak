# Microsoft Developer Studio Generated NMAKE File, Based on send_hl7.dsp
!IF "$(CFG)" == ""
CFG=send_hl7 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to send_hl7 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "send_hl7 - Win32 Release" && "$(CFG)" != "send_hl7 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "send_hl7.mak" CFG="send_hl7 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "send_hl7 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "send_hl7 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "send_hl7 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\send_hl7.exe"


CLEAN :
	-@erase "$(INTDIR)\MLDispatch.obj"
	-@erase "$(INTDIR)\MLDispatchQuery.obj"
	-@erase "$(INTDIR)\MLDispatchQueryContinue.obj"
	-@erase "$(INTDIR)\send_hl7.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\send_hl7.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\..\include" /I "..\..\..\external\ctn\include" /I "..\..\..\..\ACE_wrappers" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\send_hl7.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\send_hl7.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mesa_lib.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\send_hl7.pdb" /machine:I386 /out:"$(OUTDIR)\send_hl7.exe" /libpath:"..\..\..\winmesa\mesa_lib\Release" /libpath:"..\..\..\..\ACE_wrappers\ace"  /stack:3072000
LINK32_OBJS= \
	"$(INTDIR)\send_hl7.obj" \
	"$(INTDIR)\MLDispatchQuery.obj" \
	"$(INTDIR)\MLDispatchQueryContinue.obj" \
	"$(INTDIR)\MLDispatch.obj"

"$(OUTDIR)\send_hl7.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "send_hl7 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\send_hl7.exe"


CLEAN :
	-@erase "$(INTDIR)\MLDispatch.obj"
	-@erase "$(INTDIR)\MLDispatchQuery.obj"
	-@erase "$(INTDIR)\MLDispatchQueryContinue.obj"
	-@erase "$(INTDIR)\send_hl7.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\send_hl7.exe"
	-@erase "$(OUTDIR)\send_hl7.ilk"
	-@erase "$(OUTDIR)\send_hl7.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\external\ctn\include" /I "..\..\..\..\ACE_wrappers" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\send_hl7.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\send_hl7.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mesa_lib.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\send_hl7.pdb" /debug /machine:I386 /out:"$(OUTDIR)\send_hl7.exe" /pdbtype:sept /libpath:"..\..\..\winmesa\mesa_lib\Debug" /libpath:"..\..\..\..\ACE_wrappers\ace"  /stack:3072000
LINK32_OBJS= \
	"$(INTDIR)\send_hl7.obj" \
	"$(INTDIR)\MLDispatchQuery.obj" \
	"$(INTDIR)\MLDispatchQueryContinue.obj" \
	"$(INTDIR)\MLDispatch.obj"

"$(OUTDIR)\send_hl7.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("send_hl7.dep")
!INCLUDE "send_hl7.dep"
!ELSE 
!MESSAGE Warning: cannot find "send_hl7.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "send_hl7 - Win32 Release" || "$(CFG)" == "send_hl7 - Win32 Debug"
SOURCE=..\..\..\apps\send_hl7\MLDispatch.cpp

"$(INTDIR)\MLDispatch.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\apps\send_hl7\MLDispatchQuery.cpp

"$(INTDIR)\MLDispatchQuery.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\apps\send_hl7\MLDispatchQueryContinue.cpp

"$(INTDIR)\MLDispatchQueryContinue.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\apps\send_hl7\send_hl7.cpp

"$(INTDIR)\send_hl7.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

