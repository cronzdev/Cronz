# Project configuration
cmake_minimum_required(VERSION 3.30)
project(Cronz
        HOMEPAGE_URL https://lib.cronz.dev
        LANGUAGES CXX
        VERSION 2025.04.30.0
)

# Library definition
set(CRONZ_LIBRARY_NAME cronz)
mark_as_advanced(CRONZ_LIBRARY_NAME)

# Sources
set(CRONZ_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
mark_as_advanced(CRONZ_INCLUDE_DIR)

# Add library
add_library(${CRONZ_LIBRARY_NAME} INTERFACE)
add_library(${CRONZ_LIBRARY_NAME}::${CRONZ_LIBRARY_NAME} ALIAS ${CRONZ_LIBRARY_NAME})

set_target_properties(${CRONZ_LIBRARY_NAME} PROPERTIES
        CXX_STANDARD 26
        CXX_STANDARD_REQUIRED ON
        LINKER_LANGUAGE CXX
)

target_include_directories(${CRONZ_LIBRARY_NAME} INTERFACE
        ${CRONZ_INCLUDE_DIR}
        $<BUILD_INTERFACE:${CRONZ_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

include(cmake/Common.cmake)

# Dependencies
include(cmake/Dependencies.cmake)

# Tests
include(cmake/Tests.cmake)
