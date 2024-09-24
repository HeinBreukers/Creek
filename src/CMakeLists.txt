cmake_minimum_required(VERSION 3.2)
project(DataStreamingCPP_src)


set(SOURCE
main.cpp
)

set(HEADER
../include/DataStreams/dataStream.hpp
../include/DataStreams/dataStreamManager.hpp
)

add_executable(example
      ${HEADER}
      ${SOURCE}
)

target_include_directories(example PRIVATE ../include/DataStreams)
# target_link_libraries(example pthread)
target_compile_options(example PRIVATE -Werror -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wnull-dereference -Wdouble-promotion -Wformat=2)
# if GCC
#target_compile_options(SQLiteCPP PRIVATE -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast)
# target_include_directories(example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SPSCQueue)