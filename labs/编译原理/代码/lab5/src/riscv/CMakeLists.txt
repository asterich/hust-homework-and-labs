cmake_minimum_required(VERSION 3.16)

set(SOURCE_FILES "riscv.cpp" instruction.cpp optimize.cpp backend.cpp regalloc.cpp)

add_library(riscv STATIC ${SOURCE_FILES})

target_link_libraries(riscv PRIVATE ir)
target_include_directories(riscv PRIVATE ${CMAKE_SOURCE_DIR}/src/ir)