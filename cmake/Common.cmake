set(CRONZ_LIBRARY_NAME cronz)
mark_as_advanced(CRONZ_LIBRARY_NAME)

set(CRONZ_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
mark_as_advanced(CRONZ_INCLUDE_DIR)

set(CRONZ_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
string(LENGTH ${CRONZ_TEST_DIR} CRONZ_TEST_DIR_LENGTH)
