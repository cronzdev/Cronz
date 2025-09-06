# # # # # # # # # # # # #
# Project configuration #
# # # # # # # # # # # # #
# Cmake version
cmake_minimum_required(VERSION 3.25.0)

# Project definition
project(Cronz
        HOMEPAGE_URL https://lib.cronz.dev
        LANGUAGES CXX
        VERSION 1.0.0
)

# # # # # # # # # # # # # #
# Compiler configuration  #
# # # # # # # # # # # # # #
# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable compiler-specific extensions
set(CMAKE_CXX_EXTENSIONS OFF)

# # # # # #
# Helpers #
# # # # # #
include(cmake/Library.cmake)
