cmake_minimum_required(VERSION 3.5.0)

#Project name
project(DPad_Qt)

#setup qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

#fine QtWidgets library
find_package(Qt5Widgets REQUIRED)

#configure output directories
if(WIN32)
  if(CMAKE_CL_64)
    set(ARCH "64")
  else(CMAKE_CL_64)
    set(ARCH "32")
  endif(CMAKE_CL_64)
else(WIN32)
  string(REGEX MATCH ".*[86|32]$" matches "${CMAKE_SYSTEM_PROCESSOR}")
  if(matches)
    set(ARCH "32")
  else(matches)
    set(ARCH "64")
  endif(matches)
endif(WIN32)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_NAME}${ARCH}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_NAME}${ARCH}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_NAME}${ARCH}/lib)

#setup include and linking directories
include_directories(inc
                    )

#setup source files
set(src src/DPad.cpp
        )
        
#setup header files
set(include inc/DPad.h
            )
            
#create the library
add_library(${PROJECT_NAME} ${src} ${include})

#linking
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

set(BUILD_TEST true)
if(BUILD_TEST)
  add_subdirectory(Test)
endif(BUILD_TEST)