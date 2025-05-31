add_executable(simple_example
    main.cpp
)

# Link the example against our logger library.
target_link_libraries(simple_example
    PRIVATE
    vs-logger
)