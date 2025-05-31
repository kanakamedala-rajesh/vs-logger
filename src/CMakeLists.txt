add_library(vs-logger
    logger.cpp
)

# Add compiler warnings to this target.
target_compile_options(vs-logger PRIVATE ${VS_LOGGER_CXX_WARNINGS})

# The public API is in the 'include' directory.
# This makes sure that consumers of our library know where to find the headers.
target_include_directories(vs-logger PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)