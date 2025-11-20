# Intel oneAPI ICX
CC=icx

INCLUDES = /I ../src /I ../cpp_src

# Optimization flags
CFLAGS = /O2 /arch:AVX2 /fp:fast /Qopenmp \
         /DMKL_ILP64 /D_HAS_STD_BYTE=0 \
         $(INCLUDES)

# MKL path
MKLROOT="C:\Program Files (x86)\Intel\oneAPI\mkl\latest"

LDFLAGS = /link \
  /LIBPATH:$(MKLROOT)\lib\intel64 \
  mkl_intel_lp64.lib \
  mkl_sequential.lib \
  mkl_core.lib \
  kernel32.lib user32.lib gdi32.lib winmm.lib

# Output
EXEC = main.exe

SRC = \
  ../src/CBitGenerator/CBitGenerator.cpp \
  ../src/CChanel/CChanel.cpp \
  ../src/CChanel/CChanelAWGN_MKL.cpp \
  ../src/CDecoder/template/CDecoder.cpp \
  ../src/CDecoder/template/CDecoder_fixed.cpp \
  ../src/CDecoder/template/CDecoder_fixed_AVX.cpp \
  ../src/CDecoder/template/CDecoder_fixed_SSE.cpp \
  ../src/CDecoder/OMS/CDecoder_OMS_fixed_SSE.cpp \
  ../src/CDecoder/OMS/CDecoder_OMS_fixed_AVX.cpp \
  ../src/CDecoder/NMS/CDecoder_NMS_fixed_SSE.cpp \
  ../src/CDecoder/NMS/CDecoder_NMS_fixed_AVX.cpp \
  ../src/CEncoder/CFakeEncoder.cpp \
  ../src/CEncoder/Encoder.cpp \
  ../src/CEncoder/GenericEncoder.cpp \
  ../src/CErrorAnalyzer/CErrorAnalyzer.cpp \
  ../src/CFixPointConversion/CFastFixConversion.cpp \
  ../src/CFixPointConversion/CFixConversion.cpp \
  ../src/CTerminal/CTerminal.cpp \
  ../src/CTimer/CTimer.cpp \
  ../src/CTools/CTools.cpp \
  ../src/CTools/transpose_avx.cpp \
  ../src/CTrame/CTrame.cpp \
  ../src/main_p.cpp

OBJ = $(SRC:.cpp=.obj)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS)

%.obj: %.cpp
	$(CC) $(CFLAGS) /c $< /Fo$@

clean:
	del /S /Q *.obj
	del /S /Q *.exe
