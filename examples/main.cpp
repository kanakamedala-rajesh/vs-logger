#include "vs/logger.hpp"
#include <iostream>

int main()
{
    // Create a logger instance
    vs::Logger my_logger("main_app");
    my_logger.set_level(vs::LogLevel::Debug);

    std::cout << "Logger '" << my_logger.name()
              << "' created with log level: " << static_cast<int>(my_logger.level()) << std::endl;

    std::cout << "vs-logger example initialized successfully." << std::endl;

    // In the future, we will replace std::cout with actual logging calls:
    // my_logger.info("This is an informational message.");
    // my_logger.warn("This is a warning message.");

    return 0;
}