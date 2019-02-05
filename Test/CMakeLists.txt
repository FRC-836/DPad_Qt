cmake_minimum_required(VERSION 3.5.0)

#Project name
project(DPad_Qt_Test)

#setup include and linking directories
include_directories(inc
                      )

#setup source files
set(src main.cpp
        )
        
#setup header files
set(include 
            )
            
qt5_wrap_ui(UI_HEADERS ${CMAKE_SOURCE_DIR}/inc/DPad.ui
           )
#create the library
add_executable(${PROJECT_NAME} ${src} ${include} ${UI_HEADERS})

#linking
target_link_libraries(${PROJECT_NAME} Qt5::Widgets
                                      DPad_Qt
                                      Light_Qt
                                      )
