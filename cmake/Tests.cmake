option(CRONZ_ENABLE_TESTS "Enable tests." ON)

if (CRONZ_ENABLE_TESTS)
    find_package(GTest)

    if (NOT GTest_FOUND)
        message(WARNING "Google Test not found. Tests will not be built.")
        set(CRONZ_ENABLE_TESTS OFF)
    endif ()
endif ()

if (CRONZ_ENABLE_TESTS)
    enable_testing()

    file(GLOB_RECURSE CRONZ_TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")

    set(CRONZ_TEST_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")

    foreach (CRONZ_TEST_SOURCE ${CRONZ_TEST_SOURCES})
        file(RELATIVE_PATH CRONZ_TEST_REL_PATH ${CRONZ_TEST_ROOT_DIR} ${CRONZ_TEST_SOURCE})

        get_filename_component(CRONZ_TEST_DIR_PATH ${CRONZ_TEST_REL_PATH} DIRECTORY)
        get_filename_component(CRONZ_TEST_NAME_WE ${CRONZ_TEST_SOURCE} NAME_WE)

        if (CRONZ_TEST_DIR_PATH)
            string(REPLACE "/" "-" CRONZ_TEST_DIR_NAME ${CRONZ_TEST_DIR_PATH})
            set(CRONZ_TEST_TARGET_NAME "cronz-${CRONZ_TEST_DIR_NAME}-${CRONZ_TEST_NAME_WE}-test")
        else ()
            set(CRONZ_TEST_TARGET_NAME "cronz-${CRONZ_TEST_NAME_WE}-test")
        endif ()

        add_executable(${CRONZ_TEST_TARGET_NAME} ${CRONZ_TEST_SOURCE})

        target_include_directories(${CRONZ_TEST_TARGET_NAME} PRIVATE
                ${CRONZ_INCLUDE_DIR} ${GTEST_INCLUDE_DIRS}
        )

        target_link_libraries(${CRONZ_TEST_TARGET_NAME} PRIVATE
                ${CRONZ_LIBRARY_NAME} ${GTEST_BOTH_LIBRARIES}
        )

        set_target_properties(${CRONZ_TEST_TARGET_NAME} PROPERTIES
                CXX_STANDARD 23
                CXX_STANDARD_REQUIRED ON
                LINKER_LANGUAGE CXX
        )

        add_test(NAME ${CRONZ_TEST_TARGET_NAME} COMMAND ${CRONZ_TEST_TARGET_NAME})
    endforeach ()
endif ()