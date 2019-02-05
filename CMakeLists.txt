#required on windows to link to qtmain.lib
cmake_minimum_required(VERSION 2.8.11)

set(PROJECT_NAME DPad_Qt)

project(${PROJECT_NAME})

#setup c++14 standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

#instruct CMake to run moc automatically when needed
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_OPTIONS -o inc/)

#Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)

#dependencies
add_subdirectory(deps/Light_Qt)

set(src src/DPad.cpp
        )
        
set(inc inc/DPad.h
        )
        
set(forms inc/DPad.ui
          )

set(CMAKE_INCLUDE_CURRENT_BINARY_DIR ON)

#setup inc as a valid include directory
include_directories(inc
                    ${CMAKE_CURRENT_BINARY_DIR}
                    deps/Light_Qt/inc
                    )
                    
#create executable
add_library(${PROJECT_NAME} ${src} ${inc} ${forms})

target_compile_definitions(${PROJECT_NAME} PRIVATE INCLUDE_DPAD_GENERATED)

#use the widgets moduole from Qt 5
target_link_libraries(${PROJECT_NAME} 
                      Qt5::Widgets
                      Light_Qt
                      )

set(BUILD_TEST false)
if(BUILD_TEST)
  add_subdirectory(Test)
endif(BUILD_TEST)
