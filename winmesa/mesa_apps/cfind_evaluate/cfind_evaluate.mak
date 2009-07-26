# Microsoft Developer Studio Generated NMAKE File, Based on cfind_evaluate.dsp
!IF "$(CFG)" == ""
CFG=cfind_evaluate - Win32 Debug
!MESSAGE No configuration specified. Defaulting to cfind_evaluate - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "cfind_evaluate - Win32 Release" && "$(CFG)" != "cfind_evaluate - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cfind_evaluate.mak" CFG="cfind_evaluate - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cfind_evaluate - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "cfind_evaluate - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "cfind_evaluate - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\cfind_evaluate.exe"


CLEAN :
	-@erase "$(INTDIR)\cfind_evaluate.obj"
	-@erase "$(INTDIR)\MLCFindEval.obj"
	-@erase "$(INTDIR)\MLEvalImageAvail.obj"
	-@erase "$(INTDIR)\MLEvalMWL.obj"
	-@erase "$(INTDIR)\MLEvalStudy.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\cfind_evaluate.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\..\include" /I "..\..\..\external\ctn\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\cfind_evaluate.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\cfind_evaluate.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mesa_lib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\cfind_evaluate.pdb" /machine:I386 /out:"$(OUTDIR)\cfind_evaluate.exe" /libpath:"..\..\..\winmesa\mesa_lib\Release" 
LINK32_OBJS= \
	"$(INTDIR)\cfind_evaluate.obj" \
	"$(INTDIR)\MLCFindEval.obj" \
	"$(INTDIR)\MLEvalImageAvail.obj" \
	"$(INTDIR)\MLEvalMWL.obj" \
	"$(INTDIR)\MLEvalStudy.obj"

"$(OUTDIR)\cfind_evaluate.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "cfind_evaluate - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\cfind_evaluate.exe"


CLEAN :
	-@erase "$(INTDIR)\cfind_evaluate.obj"
	-@erase "$(INTDIR)\MLCFindEval.obj"
	-@erase "$(INTDIR)\MLEvalImageAvail.obj"
	-@erase "$(INTDIR)\MLEvalMWL.obj"
	-@erase "$(INTDIR)\MLEvalStudy.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\cfind_evaluate.exe"
	-@erase "$(OUTDIR)\cfind_evaluate.ilk"
	-@erase "$(OUTDIR)\cfind_evaluate.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\external\ctn\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\cfind_evaluate.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\cfind_evaluate.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=mesa_lib.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\cfind_evaluate.pdb" /debug /machine:I386 /out:"$(OUTDIR)\cfind_evaluate.exe" /pdbtype:sept /libpath:"..\..\..\winmesa\mesa_lib\Debug" 
LINK32_OBJS= \
	"$(INTDIR)\cfind_evaluate.obj" \
	"$(INTDIR)\MLCFindEval.obj" \
	"$(INTDIR)\MLEvalImageAvail.obj" \
	"$(INTDIR)\MLEvalMWL.obj" \
	"$(INTDIR)\MLEvalStudy.obj"

"$(OUTDIR)\cfind_evaluate.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("cfind_evaluate.dep")
!INCLUDE "cfind_evaluate.dep"
!ELSE 
!MESSAGE Warning: cannot find "cfind_evaluate.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "cfind_evaluate - Win32 Release" || "$(CFG)" == "cfind_evaluate - Win32 Debug"
SOURCE=..\..\..\apps\cfind_evaluate\cfind_evaluate.cpp

"$(INTDIR)\cfind_evaluate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\apps\cfind_evaluate\MLCFindEval.cpp

"$(INTDIR)\MLCFindEval.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\apps\cfind_evaluate\MLEvalImageAvail.cpp

"$(INTDIR)\MLEvalImageAvail.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\apps\cfind_evaluate\MLEvalMWL.cpp

"$(INTDIR)\MLEvalMWL.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\apps\cfind_evaluate\MLEvalStudy.cpp

"$(INTDIR)\MLEvalStudy.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

