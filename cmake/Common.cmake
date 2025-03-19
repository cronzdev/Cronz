set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-module)

macro (cronz_add_dependency_link_library libraries)
    target_link_libraries(${CRONZ_LIBRARY_NAME} INTERFACE ${libraries})
endmacro()

function(cronz_add_dependency name version is_required)
    if (is_required)
        find_package(${name} ${version} REQUIRED QUIET)
    else ()
        find_package(${name} ${version} QUIET)
    endif ()

    if (${name}_FOUND)
        target_include_directories(${CRONZ_LIBRARY_NAME} INTERFACE ${${name}_INCLUDE_DIRS})
        target_link_libraries(${CRONZ_LIBRARY_NAME} INTERFACE ${${name}_LIBRARIES})
    else ()
        message(WARNING "${name} not found; disabling ${name} support.")
    endif ()

    string(TOUPPER ${name} upper_name)
    target_compile_definitions(${CRONZ_LIBRARY_NAME} INTERFACE CRONZ_ENABLE_${upper_name}=$<BOOL:${${name}_FOUND}>)
endfunction()

function(cronz_add_boolean_definition name value)
    target_compile_definitions(${CRONZ_LIBRARY_NAME} INTERFACE ${name}=$<BOOL:${value}>)
endfunction()
