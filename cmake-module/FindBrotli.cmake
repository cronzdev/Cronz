#
# Cronz - https://lib.cronz.dev
#
# Copyright (c) 2025 - present. All rights reserved.
# Tuğrul Güngör - https://tugrulgungor.me
#
# Distributed under the MIT License.
# https://opensource.org/license/mit/
#

#[=======================================================================[.rst:
FindBrotli
--------

Find the Brotli headers and libraries.

Imported Targets
^^^^^^^^^^^^^^^^

``brotli::brotli``
  The Brotli library, if found.

Result Variables
^^^^^^^^^^^^^^^^

This script defines the following variables:

``BROTLI_FOUND``
  TRUE if Brotli is available.
``BROTLI_VERSION``
  the version of Brotli found.
``BROTLI_LIBRARIES``
  list of fount Brotli libraries.
``BROTLI_INCLUDE_DIRS``
  where to find the Brotli headers.

Hints
^^^^^

``BROTLI_ROOT`` can be set to tell this script where to look.

#]=======================================================================]

if (EXISTS "${CMAKE_ROOT}/Modules/FindBrotli.cmake")
    include("${CMAKE_ROOT}/Modules/FindBrotli.cmake")
    return()
endif ()

include(FindPackageHandleStandardArgs)

if (BROTLI_ROOT)
    set(_BROTLI_SEARCH_ROOT PATH ${BROTLI_ROOT} NO_DEFAULT_PATH)
    list(APPEND _BROTLI_SEARCHERS _BROTLI_SEARCH_ROOT)
endif ()

find_path(Brotli_INCLUDE_DIRS
        NAMES brotli/decode.h brotli/encode.h
        HINTS ${Brotli_ROOT}/include
)

find_library(Brotli_LIBRARY_COMMON
        NAMES brotlicommon
        HINTS ${Brotli_ROOT}/lib
)

find_library(Brotli_LIBRARY_DEC
        NAMES brotlidec
        HINTS ${Brotli_ROOT}/lib
)

find_library(Brotli_LIBRARY_ENC
        NAMES brotlienc
        HINTS ${Brotli_ROOT}/lib
)

if (Brotli_INCLUDE_DIRS AND Brotli_LIBRARY_COMMON AND Brotli_LIBRARY_DEC AND Brotli_LIBRARY_ENC)
    set(Brotli_FOUND TRUE)

    set(Brotli_LIBRARIES ${Brotli_LIBRARY_COMMON} ${Brotli_LIBRARY_DEC} ${Brotli_LIBRARY_ENC})

    mark_as_advanced(Brotli_INCLUDE_DIRS Brotli_LIBRARIES)
else ()
    set(Brotli_FOUND FALSE)
endif ()

find_package_handle_standard_args(Brotli
        REQUIRED_VARS Brotli_LIBRARIES Brotli_INCLUDE_DIRS
        VERSION_VAR ${Brotli_VERSION}
        HANDLE_COMPONENTS
)
