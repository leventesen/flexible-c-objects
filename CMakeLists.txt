cmake_minimum_required(VERSION 3.15)

project(FCO)

set(CMAKE_C_STANDARD 11)

set(EXAMPLES_DIR examples)
set(LIB_DIR lib)

add_library(FCO SHARED ${LIB_DIR}/fco.c)
target_include_directories(FCO PUBLIC ${LIB_DIR})

file(GLOB_RECURSE EXAMPLE_SOURCES "${EXAMPLES_DIR}/*.c")

foreach(EXAMPLE_SOURCE IN LISTS EXAMPLE_SOURCES)
  get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)

  add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})
  target_include_directories(${EXAMPLE_NAME} PUBLIC ${LIB_DIR})
  target_link_libraries(${EXAMPLE_NAME} PUBLIC FCO)
endforeach()
