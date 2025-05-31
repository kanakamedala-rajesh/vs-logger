add_executable(run_tests
    main_test.cpp
)

# Link the test runner against GoogleTest and our logger library.
target_link_libraries(run_tests
    PRIVATE
    gtest_main
    vs-logger
)

# Add this test to CTest.
add_test(NAME unit_tests COMMAND run_tests)