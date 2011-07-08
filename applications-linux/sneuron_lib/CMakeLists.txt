cmake_minimum_required(VERSION 2.0)

MACRO(CREATE_EXECUTABLE NAME
  SOURCES LIBRARIES)
  ADD_EXECUTABLE(${NAME} ${SOURCES})
  TARGET_LINK_LIBRARIES(${NAME} 
    ${LIBRARIES})
ENDMACRO(CREATE_EXECUTABLE)

#Name the project
project(sneuron)

#Set Include directory
SET(SN_INC_DIR ../../src/)
SET(EIGEN_INC_DIR ../3rdparty/eigen3.0.1/)
INCLUDE_DIRECTORIES(${SN_INC_DIR} ${EIGEN_INC_DIR})

#Set all the sources required for the library
SET(PAR ${SN_INC_DIR}sneuron/parser/syaml/CSParserYaml.cpp
   )

SET(UT ${SN_INC_DIR}sneuron/util/CImageAscii.cpp
       ${SN_INC_DIR}sneuron/util/CSystemClock.cpp
       ${SN_INC_DIR}sneuron/util/FileFunctions.cpp
       ${SN_INC_DIR}sneuron/util/HelperFunctions.cpp
       ${SN_INC_DIR}sneuron/util/logging/CFileLogger.cpp
       ${SN_INC_DIR}sneuron/util/logging/CTCPStreamLogger.cpp
       ${SN_INC_DIR}sneuron/util/logging/CSLogVecToFile.cpp
   )

SET(SN_SRC ${PAR} ${UT})

IF(CMAKE_BUILD_TYPE MATCHES Debug)
  #Add debug definitions
  ADD_DEFINITIONS(-DASSERT=assert -DDEBUG=1 -DSN_TESTING=1)
  SET(CMAKE_CXX_FLAGS_DEBUG "-Wall -ggdb -O0 -pg -fPIC")
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

IF(CMAKE_BUILD_TYPE MATCHES Release)
  #Add release definitions
  SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3 -fPIC")
ENDIF(CMAKE_BUILD_TYPE MATCHES Release)

#Make sure the generated makefile is not shortened
SET(CMAKE_VERBOSE_MAKEFILE ON)

#Define the library to be built
add_library(sneuron SHARED ${SN_SRC})
