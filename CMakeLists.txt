cmake_minimum_required(VERSION 3.5.0)

project(seuif97 VERSION  2.0.0)

include_directories(./src/common ./src/algo ./src/r1 ./src/r2 ./src/r3 ./src/r4 ./src/r5 ) 

aux_source_directory(./src/common/ SRC_COM)
aux_source_directory(./src/algo/ SRC_ALGO)
aux_source_directory(./src/r1/ SRC_R1)
aux_source_directory(./src/r2/ SRC_R2)
aux_source_directory(./src/r3/ SRC_R3)
aux_source_directory(./src/r4/ SRC_R4)
aux_source_directory(./src/r5/ SRC_R5)
if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()
add_library(seuif97 SHARED ${SRC_COM}  ${SRC_ALGO} ${SRC_R1} ${SRC_R2} ${SRC_R3} ${SRC_R4} ${SRC_R5})

set(EXE_SOURCES ./demo/demo-c/demo.c)
add_executable(demoif97 ${EXE_SOURCES})
target_include_directories(demoif97  PRIVATE  ${PROJECT_SOURCE_DIR}/demo/demo-c/include)
target_link_libraries(demoif97 PRIVATE seuif97)