# Author : Samir Menon
# (c) Stanford University.
# All rights reserved.

############################# COMPILER OPTIONS ############################
CXX = g++

############################# INCLUDE OPTIONS ############################
SN_INC_DIR = ../../src/
SN_DBG_LIB_DIR = -L../sneuron_lib/debug/ -Wl,--rpath=../sneuron_lib/debug/
SN_REL_LIB_DIR = -L../sneuron_lib/release/ -Wl,--rpath=../sneuron_lib/release/
SN_LIB = -lsneuron
SN_DEFS_DBG = -DASSERT=assert -DDEBUG=1 -DSN_TESTING=1
SN_DEFS_REL = -DRELEASE=1

#3rd party lib : Eigen (local install)
EIGEN_INC_DIR = ../../3rdparty/eigen3.0.1/
             
#3rd party lib : chai3d (local install)
CHAI_INC_DIR = ../../3rdparty/chai3d-graphics/chai/
CHAI_DBG_LIB_DIR = -L$(CHAI_INC_DIR)../lib/debug/ -Wl,--rpath=$(CHAI_INC_DIR)../lib/debug/
CHAI_REL_LIB_DIR = -L$(CHAI_INC_DIR)../lib/release/ -Wl,--rpath=$(CHAI_INC_DIR)../lib/release/
CHAI_LIB = -lchai3d
CHAI_DEFS = -D_LINUX \
            -W -Wno-deprecated -Wno-unused-parameter -L/usr/lib \
					  -lpthread -lrt -lGL -lGLU -lglut
             
#3rd party lib: Uncomment these when using opencv
#-lcxcore -lcv -lhighgui -lcvaux -lml

############################# INCLUDE AND LINK OPTIONS ############################
#Collate all the include directiories
INCLUDEDIRS = -I$(SN_INC_DIR) -I$(EIGEN_INC_DIR) -I$(CHAI_INC_DIR)

#Combine all libs to be linked
###Debug
LINK_DBG_DIRS = $(SN_DBG_LIB_DIR) $(CHAI_DBG_LIB_DIR)
LINK_LIBS_DBG = $(SN_LIB) $(CHAI_LIB)

###Release
LINK_REL_DIRS = $(SN_REL_LIB_DIR) $(CHAI_REL_LIB_DIR)
LINK_LIBS_REL = $(SN_LIB) $(CHAI_LIB)

#Combine other defs
DEFS_DBG = $(SN_DEFS_DBG) $(CHAI_DEFS)
DEFS_REL = $(SN_DEFS_REL) $(CHAI_DEFS)

############################# Compile options ############################
DBGFLAGS = -Wall -g -ggdb -pg -O0 $(INCLUDEDIRS) \
           -fPIC $(LINK_DBG_DIRS) $(LINK_LIBS_DBG) \
           $(DEFS_DBG)
RELFLAGS = -Wall -O3 $(INCLUDEDIRS) \
           -fPIC $(LINK_FIN_DIRS) $(LINK_LIBS_FIN) \
           $(DEFS_FIN) 

############################ SOURCE FILES ############################
#The application source(s)
SOURCES = test_main.cpp

############################ BUILD SPECIFICATIONS ############################
TARGET = sneuron_test

.PHONY: all

#Build all simulations
all: 
	$(CXX) $(DBGFLAGS) -o $(TARGET) $(SOURCES)

final: 
	$(CXX) $(RELFLAGS) -o $(TARGET) $(SOURCES)

debug:
	$(CXX) $(DBGFLAGS) -o $(TARGET) $(SOURCES)

#Clean up options
.PHONY: clean
clean: 
	@rm -f *.o $(TARGET) gmon.out
