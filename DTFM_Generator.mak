# Microsoft Developer Studio Generated NMAKE File, Based on DTFM_Generator.dsp
!IF "$(CFG)" == ""
CFG=DTFM_Generator - Win32 Debug
!MESSAGE No configuration specified. Defaulting to DTFM_Generator - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "DTFM_Generator - Win32 Release" && "$(CFG)" != "DTFM_Generator - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DTFM_Generator.mak" CFG="DTFM_Generator - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DTFM_Generator - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DTFM_Generator - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DTFM_Generator - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : ".\ASIOSynthesizer_release.exe" "$(OUTDIR)\DTFM_Generator.bsc"


CLEAN :
	-@erase "$(INTDIR)\DialogASIOConnect.obj"
	-@erase "$(INTDIR)\DialogASIOConnect.sbr"
	-@erase "$(INTDIR)\DTFM_Generator.obj"
	-@erase "$(INTDIR)\DTFM_Generator.pch"
	-@erase "$(INTDIR)\DTFM_Generator.res"
	-@erase "$(INTDIR)\DTFM_Generator.sbr"
	-@erase "$(INTDIR)\DTFM_GeneratorDlg.obj"
	-@erase "$(INTDIR)\DTFM_GeneratorDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\synth.obj"
	-@erase "$(INTDIR)\synth.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\DTFM_Generator.bsc"
	-@erase ".\ASIOSynthesizer_release.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\DTFM_Generator.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\DTFM_Generator.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DTFM_Generator.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\DialogASIOConnect.sbr" \
	"$(INTDIR)\DTFM_Generator.sbr" \
	"$(INTDIR)\DTFM_GeneratorDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\synth.sbr"

"$(OUTDIR)\DTFM_Generator.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=winmm.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\ASIOSynthesizer_release.pdb" /machine:I386 /out:"ASIOSynthesizer_release.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DialogASIOConnect.obj" \
	"$(INTDIR)\DTFM_Generator.obj" \
	"$(INTDIR)\DTFM_GeneratorDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\synth.obj" \
	"$(INTDIR)\DTFM_Generator.res" \
	".\BassASIO\c\synth\bass.lib" \
	".\BassASIO\c\bassasio.lib"

".\ASIOSynthesizer_release.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DTFM_Generator - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\ASIOSynthesizer_debug.exe" "$(OUTDIR)\DTFM_Generator.bsc"


CLEAN :
	-@erase "$(INTDIR)\DialogASIOConnect.obj"
	-@erase "$(INTDIR)\DialogASIOConnect.sbr"
	-@erase "$(INTDIR)\DTFM_Generator.obj"
	-@erase "$(INTDIR)\DTFM_Generator.pch"
	-@erase "$(INTDIR)\DTFM_Generator.res"
	-@erase "$(INTDIR)\DTFM_Generator.sbr"
	-@erase "$(INTDIR)\DTFM_GeneratorDlg.obj"
	-@erase "$(INTDIR)\DTFM_GeneratorDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\synth.obj"
	-@erase "$(INTDIR)\synth.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ASIOSynthesizer_debug.pdb"
	-@erase "$(OUTDIR)\DTFM_Generator.bsc"
	-@erase ".\ASIOSynthesizer_debug.exe"
	-@erase ".\ASIOSynthesizer_debug.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\DTFM_Generator.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x419 /fo"$(INTDIR)\DTFM_Generator.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\DTFM_Generator.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\DialogASIOConnect.sbr" \
	"$(INTDIR)\DTFM_Generator.sbr" \
	"$(INTDIR)\DTFM_GeneratorDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\synth.sbr"

"$(OUTDIR)\DTFM_Generator.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=winmm.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\ASIOSynthesizer_debug.pdb" /debug /machine:I386 /out:"ASIOSynthesizer_debug.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\DialogASIOConnect.obj" \
	"$(INTDIR)\DTFM_Generator.obj" \
	"$(INTDIR)\DTFM_GeneratorDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\synth.obj" \
	"$(INTDIR)\DTFM_Generator.res" \
	".\BassASIO\c\synth\bass.lib" \
	".\BassASIO\c\bassasio.lib"

".\ASIOSynthesizer_debug.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("DTFM_Generator.dep")
!INCLUDE "DTFM_Generator.dep"
!ELSE 
!MESSAGE Warning: cannot find "DTFM_Generator.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "DTFM_Generator - Win32 Release" || "$(CFG)" == "DTFM_Generator - Win32 Debug"
SOURCE=.\DialogASIOConnect.cpp

"$(INTDIR)\DialogASIOConnect.obj"	"$(INTDIR)\DialogASIOConnect.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DTFM_Generator.pch"


SOURCE=.\DTFM_Generator.cpp

"$(INTDIR)\DTFM_Generator.obj"	"$(INTDIR)\DTFM_Generator.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DTFM_Generator.pch"


SOURCE=.\DTFM_Generator.rc

"$(INTDIR)\DTFM_Generator.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\DTFM_GeneratorDlg.cpp

"$(INTDIR)\DTFM_GeneratorDlg.obj"	"$(INTDIR)\DTFM_GeneratorDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DTFM_Generator.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "DTFM_Generator - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\DTFM_Generator.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\DTFM_Generator.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "DTFM_Generator - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\DTFM_Generator.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\DTFM_Generator.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\BassASIO\c\synth\synth.cpp

"$(INTDIR)\synth.obj"	"$(INTDIR)\synth.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\DTFM_Generator.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

