file(GLOB_RECURSE TEST_SOURCES "test_*.c")

foreach(TEST_SOURCE IN LISTS TEST_SOURCES)
  get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

  add_executable(${TEST_NAME} ${TEST_SOURCE} ../lib/fco.c)

  add_test(NAME ${TEST_NAME}
           COMMAND ${TEST_NAME}
           WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

  set_tests_properties(${TEST_NAME} PROPERTIES
			           PASS_REGULAR_EXPRESSION "Test passed")
endforeach()