#required on windows to link to qtmain.lib
cmake_minimum_required(VERSION 2.8.11)

set(PROJECT_NAME DPad_Qt)

project(${PROJECT_NAME})

#setup c++14 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

#instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_OPTIONS -o inc/)

#Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)

#dependencies
add_subdirectory(deps/Light_Qt)

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

set(src src/DPad.cpp
        )
        
set(inc inc/DPad.h
        )
        
set(forms inc/DPad.ui
          )


#setup inc as a valid include directory
include_directories(inc
                    ${CMAKE_CURRENT_BINARY_DIR}
                    deps/Light_Qt/inc
                    )
                    
#create executable
add_library(${PROJECT_NAME} ${src} ${inc} ${forms})

#move the generated Ui file to the include directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy  ${CMAKE_CURRENT_BINARY_DIR}/DPad_Qt_autogen/include/ui_DPad.h ${CMAKE_CURRENT_SOURCE_DIR}/inc
                   )

#use the widgets moduole from Qt 5
target_link_libraries(${PROJECT_NAME} 
                      Qt5::Widgets
                      Light_Qt
                      )

set(BUILD_TEST false)
if(BUILD_TEST)
  add_subdirectory(Test)
endif(BUILD_TEST)
