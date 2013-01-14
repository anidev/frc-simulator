cmake_minimum_required(VERSION 2.8.3)
project(612-code_frc-cpp-sim)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
file(GLOB_RECURSE 612-CODE_SOURCES src/*.cpp)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${VXWORKS-SYSTEM_DIR}/include)
include_directories(${WPILIB_DIR})
add_executable(612-code ${612-CODE_SOURCES})
set(LIBS
    wpilib
    frccomm
    ni-priv
    nivision
    ni-emb
    fpga
    vxworks-system
    opencv_core
    opencv_highgui
    opencv_imgproc
    pcre
    rt
)
target_link_libraries(612-code ${LIBS})
