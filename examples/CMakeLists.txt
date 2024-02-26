file(GLOB_RECURSE EXAMPLE_SOURCES "example_*.c")

foreach(EXAMPLE_SOURCE IN LISTS EXAMPLE_SOURCES)
  get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)

  add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE} ../lib/fco.c)
endforeach()
