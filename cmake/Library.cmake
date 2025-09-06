# # # # # #
# Library #
# # # # # #
# Library name
set(CRONZ_LIBRARY_NAME cronz)

# Create library target
add_library(${CRONZ_LIBRARY_NAME} INTERFACE)
add_library(${CRONZ_LIBRARY_NAME}::${CRONZ_LIBRARY_NAME} ALIAS ${CRONZ_LIBRARY_NAME})

# Library configurations
set_target_properties(${CRONZ_LIBRARY_NAME} PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        LINKER_LANGUAGE CXX
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        PUBLIC_HEADER "${CRONZ_INCLUDE_DIR}/cronz.hpp"
        EXPORT_NAME ${CRONZ_LIBRARY_NAME}
)

# # # # # # # # # #
# Library sources #
# # # # # # # # # #
# Include directories
set(CRONZ_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
mark_as_advanced(CRONZ_INCLUDE_DIR)

target_include_directories(${CRONZ_LIBRARY_NAME} INTERFACE
        ${CRONZ_INCLUDE_DIR}
        $<BUILD_INTERFACE:${CRONZ_HEADER_FILES}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Header files
file(GLOB_RECURSE CRONZ_HEADER_XPP_FILES "${CRONZ_INCLUDE_DIR}/cronz/**/*.?pp")
file(GLOB_RECURSE CRONZ_HEADER_DEF_FILES "${CRONZ_INCLUDE_DIR}/cronz/**/*.def")

set(CRONZ_HEADER_FILES ${CRONZ_HEADER_XPP_FILES} ${CRONZ_HEADER_DEF_FILES})
source_group("Cronz Header Files" FILES ${CRONZ_HEADER_FILES})

# # # # # # # # # # # #
# User configuration  #
# # # # # # # # # # # #
# [[nodiscard]]
option(CRONZ_DISABLE_NODISCARD "Disable [[nodiscard]] attribute for all levels. This will also disable CRONZ_DISABLE_NODISCARD_L1 and CRONZ_DISABLE_NODISCARD_L2" OFF)
option(CRONZ_DISABLE_NODISCARD_L1 "Disable [[nodiscard]] attribute level 1" OFF)
option(CRONZ_DISABLE_NODISCARD_L2 "Disable [[nodiscard]] attribute level 2" OFF)

if (CRONZ_DISABLE_NODISCARD_L1)
    target_compile_definitions(${CRONZ_LIBRARY_NAME} INTERFACE CRONZ_DISABLE_NODISCARD_L1)
endif ()
