if (CRONZ_ENABLE_TESTS)
    # Check dependencies
    find_package(GTest 1.14 REQUIRED)

    # Enable testing
    enable_testing()

    # Get and iterate targets
    file(GLOB_RECURSE CRONZ_TEST_TARGETS_RAW ${CRONZ_TEST_DIR}/*.cpp)
    
    set(CRONZ_TEST_TARGETS "")

    list(LENGTH CRONZ_TEST_TARGETS_RAW CRONZ_TEST_TARGET_COUNT)
    math(EXPR CRONZ_TEST_TARGET_COUNT "${CRONZ_TEST_TARGET_COUNT}-1" OUTPUT_FORMAT DECIMAL)

    foreach (target ${CRONZ_TEST_TARGETS_RAW})
        string(SUBSTRING "${target}" ${CRONZ_TEST_DIR_LENGTH} -1 CRONZ_TEST_TARGET_FILENAME)
        string(SUBSTRING "${CRONZ_TEST_TARGET_FILENAME}" 1 -1 CRONZ_TEST_TARGET_FILENAME)

        string(REPLACE "/" "-" CRONZ_TEST_TARGET_FILENAME ${CRONZ_TEST_TARGET_FILENAME})

        list(APPEND CRONZ_TEST_TARGETS "${CRONZ_TEST_TARGET_FILENAME}")
    endforeach ()

    foreach (index RANGE ${CRONZ_TEST_TARGET_COUNT})
        # Fetch values
        list(GET CRONZ_TEST_TARGETS ${index} CRONZ_TEST_TARGET_NAME)
        list(GET CRONZ_TEST_TARGETS_RAW ${index} CRONZ_TEST_TARGET_FILENAME)

        # Build target name
        set(CRONZ_TEST_TARGET_NAME "${CRONZ_LIBRARY_NAME}-test-${CRONZ_TEST_TARGET_NAME}")

        # Add target
        add_executable(${CRONZ_TEST_TARGET_NAME} ${CRONZ_TEST_TARGET_FILENAME})

        # Configure target
        target_include_directories(${CRONZ_TEST_TARGET_NAME}
                                   PRIVATE ${CRONZ_INCLUDE_DIR}
        )

        target_link_libraries(${CRONZ_TEST_TARGET_NAME}
                              PRIVATE ${CRONZ_LIBRARY_NAME} gtest
        )

        set_target_properties(${CRONZ_TEST_TARGET_NAME} PROPERTIES
                              CXX_STANDARD 20
                              CXX_STANDARD_REQUIRED ON
        )

        target_compile_definitions(${CRONZ_TEST_TARGET_NAME}
                                   PRIVATE "CRONZ_TEST_DIR=\"${CRONZ_TEST_DIR}\""
        )

        # Add test target
        add_test(NAME ${CRONZ_TEST_TARGET_NAME}
                 COMMAND ${CRONZ_TEST_TARGET_NAME}
        )

        # Clean temporary loop variables
        unset(CRONZ_TEST_TARGET_NAME)
        unset(CRONZ_TEST_TARGET_FILENAME)
    endforeach ()

    # Cleanup
    unset(CRONZ_TEST_TARGET_COUNT)
    unset(CRONZ_TEST_TARGET_FILENAME)
    unset(CRONZ_TEST_TARGETS_RAW)
    unset(CRONZ_TEST_TARGETS)
endif ()
