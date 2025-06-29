cmake_minimum_required(VERSION 3.22)
project(f83ystcv)

set(CMAKE_CXX_STANDARD 17)

include_directories(lib)
include_directories(src/step1/include)

find_package(LLVM 11.1.0 REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

execute_process(COMMAND llvm-config-11 --includedir
        OUTPUT_VARIABLE LLVM_INCLUDE_DIRS)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


add_executable(codegen
        lib/sylib.c
        lib/sylib.h
        src/step1/include/codegen.h
        src/step1/include/opt.h
        src/step1/codegen.cc
        src/step1/main.cc
        src/step1/opt.cc)

execute_process(COMMAND llvm-config-11 --libs all
        OUTPUT_VARIABLE llvm_libraries)

string(STRIP ${llvm_libraries} llvm_libraries)

target_link_libraries(codegen ${llvm_libraries})
