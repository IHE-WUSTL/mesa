# Microsoft Developer Studio Generated NMAKE File, Based on tcp_connect.dsp
!IF "$(CFG)" == ""
CFG=tcp_connect - Win32 Debug
!MESSAGE No configuration specified. Defaulting to tcp_connect - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "tcp_connect - Win32 Release" && "$(CFG)" != "tcp_connect - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tcp_connect.mak" CFG="tcp_connect - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tcp_connect - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "tcp_connect - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "tcp_connect - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\tcp_connect.exe"


CLEAN :
	-@erase "$(INTDIR)\tcp_connect.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\tcp_connect.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\..\include" /I "..\..\..\external\ctn\include" /I "..\..\..\..\ACE_wrappers" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\tcp_connect.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tcp_connect.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mesa_lib.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\tcp_connect.pdb" /machine:I386 /out:"$(OUTDIR)\tcp_connect.exe" /libpath:"..\..\..\winmesa\mesa_lib\Release" /libpath:"..\..\..\..\ACE_wrappers\ace" 
LINK32_OBJS= \
	"$(INTDIR)\tcp_connect.obj"

"$(OUTDIR)\tcp_connect.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "tcp_connect - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\tcp_connect.exe"


CLEAN :
	-@erase "$(INTDIR)\tcp_connect.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\tcp_connect.exe"
	-@erase "$(OUTDIR)\tcp_connect.ilk"
	-@erase "$(OUTDIR)\tcp_connect.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\external\ctn\include" /I "..\..\..\..\ACE_wrappers" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\tcp_connect.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tcp_connect.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mesa_lib.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\tcp_connect.pdb" /debug /machine:I386 /out:"$(OUTDIR)\tcp_connect.exe" /pdbtype:sept /libpath:"..\..\..\winmesa\mesa_lib\Debug" /libpath:"..\..\..\..\ACE_wrappers\ace" 
LINK32_OBJS= \
	"$(INTDIR)\tcp_connect.obj"

"$(OUTDIR)\tcp_connect.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("tcp_connect.dep")
!INCLUDE "tcp_connect.dep"
!ELSE 
!MESSAGE Warning: cannot find "tcp_connect.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "tcp_connect - Win32 Release" || "$(CFG)" == "tcp_connect - Win32 Debug"
SOURCE=..\..\..\apps\tcp_connect\tcp_connect.cpp

"$(INTDIR)\tcp_connect.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

