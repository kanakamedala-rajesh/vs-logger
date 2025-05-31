#include <gtest/gtest.h>
#include "vs/logger.hpp"

/**
 * @test LoggerConstruction.
 * @brief Verifies that the Logger class can be constructed correctly and that
 * its initial state (name and level) is as expected.
 */
TEST(LoggerConstruction, InitializesNameAndLevelCorrectly)
{
    vs::Logger logger("test_logger", vs::LogLevel::Debug);
    ASSERT_EQ(logger.name(), "test_logger");
    ASSERT_EQ(logger.level(), vs::LogLevel::Debug);
}

/**
 * @test LoggerLevelChange.
 * @brief Verifies that the logger's log level can be changed at runtime and
 * that the change is reflected correctly.
 */
TEST(LoggerLevelChange, SetLevelUpdatesTheLevel)
{
    vs::Logger logger("test_logger");
    ASSERT_EQ(logger.level(), vs::LogLevel::Info); // Default level

    logger.set_level(vs::LogLevel::Warn);
    ASSERT_EQ(logger.level(), vs::LogLevel::Warn);
}