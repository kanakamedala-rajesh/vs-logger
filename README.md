# vs-logger

**A high-performance, low-resource C++11 logging library for demanding environments.**

`vs-logger` is a production-ready, enterprise-standard C++ logger designed from the ground up for extreme performance and minimal resource utilization (CPU, memory, I/O). It is an ideal logging solution for resource-constrained systems such as IoT devices, automotive ECUs, and legacy embedded platforms.

## Key Features

- **Blazing Fast**: Asynchronous, non-blocking API with a focus on minimizing hot-path latency.
- **Low Resource Footprint**: Optimized for minimal CPU overhead, low memory usage, and efficient I/O.
- **C++11 Compatible**: Built with strict C++11 compliance for broad platform support.
- **Cross-Platform**: Designed for seamless compilation on Linux, Android (NDK), and other POSIX-compliant systems.
- **Highly Configurable**: Features are extensively strippable at compile-time to tailor the library to specific needs.
- **Modern & Clean API**: Intuitive, type-safe, and easy to integrate into new or existing projects.
- **Quality Assured**: Enforces modern C++ best practices with integrated static analysis and unit testing.

## Getting Started

### Prerequisites

To build and use `vs-logger`, you will need the following tools:

- **CMake**: Version 3.14 or higher
- **C++ Compiler**: A compiler with full C++11 support (e.g., GCC 4.8+, Clang 3.3+)
- **Git**: For cloning the repository

### Building the Project

In depth detailed instructions are provided below inside section [Environment Setup and Build Guide](#environment-setup-and-build-guide)

1. **Clone the repository:**

   ```sh
   git clone <your-repository-url>/vs-logger.git
   cd vs-logger
   ```

2. **Configure the build using CMake:**

   ```sh
   mkdir build
   cd build
   cmake ..
   ```

   _Tip: You can customize the build by passing CMake options, e.g., `cmake -DBUILD_SHARED_LIBS=ON ..`_

3. **Compile the code:**

   ```sh
   cmake --build .
   ```

   This will build the `vs-logger` library, along with the tests and examples (if enabled).

### Quick Example

Here is a simple example of how to use `vs-logger`:

```cpp
#include "vs/logger.hpp"
#include <memory>

int main() {
    // Create a logger instance
    auto my_logger = std::make_shared<vs::Logger>("WebApp");

    // Set the desired log level
    my_logger->set_level(vs::LogLevel::Debug);

    // Logging calls (future implementation)
    // VS_LOG_INFO(my_logger, "User {} logged in successfully.", "Alice");
    // VS_LOG_WARN(my_logger, "Disk space is running low: {}% free.", 20);
    // VS_LOG_CRITICAL(my_logger, "Failed to connect to database!");

    return 0;
}
```

### Running Tests

`vs-logger` uses Google Test for unit testing. The tests are automatically built if `VS_LOGGER_ENABLE_TESTING` is `ON` (the default).

To run the tests, execute the following command from your `build` directory:

```Bash
ctest --verbose
```

## Environment Setup and Build Guide

This guide provides detailed instructions for setting up your development environment and compiling the `vs-logger` library, its tests, and examples.

### 1. Development Environment Setup

To ensure a consistent and correct build, your development environment must have a set of core tools.

#### Core Dependencies

- **C++11 Compliant Compiler**: The library strictly adheres to the C++11 standard. A modern compiler is required.
  - **GCC**: Version 4.8 or newer
  - **Clang**: Version 3.3 or newer
- **CMake**: The project uses CMake as its build system.
  - **Version**: 3.14 or newer
- **Git**: Required for cloning the source code repository.

#### Recommended Tools for Code Quality

To maintain code quality and adhere to project standards, we have integrated the following tools into our build process. It is highly recommended to install them:

- **clang-format**: Used to enforce a uniform code style across the project.
- **clang-tidy**: A static analysis tool to detect common programming errors and style issues.

#### Example Setup on Ubuntu 20.04 / 22.04

You can install all required and recommended dependencies with the following command:

```bash
sudo apt-get update
sudo apt-get install -y build-essential g++ git cmake clang-format clang-tidy
```

### 2. Build Instructions

The following steps will guide you through compiling the project from source.

#### Step 1: Clone the Repository

First, clone the project from your Git repository to your local machine.

```bash
git clone kanakamedala-rajesh/vs-logger.git
cd vs-logger
```

#### Step 2: Configure the Project with CMake

We will create a separate directory for the build artifacts to keep the main source tree clean. This is a standard best practice. The default build type is `Debug`, which is suitable for development and testing.

```bash
# Create a build directory
mkdir build

# Navigate into it

cd build

# Configure the project by running CMake from the build directory

# The '..' points to the parent directory where the root CMakeLists.txt is located

cmake ..
```

#### Step 3: Compile the Code

Once CMake has successfully configured the project, you can compile the library, tests, and examples using a single command. This command invokes the underlying build tool (e.g., make).

```bash
cmake --build .
```

#### Step 4: Running Unit Tests

The unit tests are built by default. To run them and verify the correctness of the library, use `CTest`, CMake's testing driver, from within the build directory.

```bash
# Run tests and print detailed output

ctest --verbose
```

### Advanced Build Options

#### Building for Release (Performance)

To benchmark performance or for deployment, you must build the library in `Release` mode. This enables critical compiler optimizations such as `-O3` and Link-Time Optimization (LTO).

To configure a release build, specify the `CMAKE_BUILD_TYPE` variable during the CMake configuration step.

```bash
# From a clean build directory
cmake -D CMAKE_BUILD_TYPE=Release ..

# Compile the optimized code

cmake --build .
```

#### Controlling the Build with CMake Options

The project provides several options to control the build, as defined in the root `CMakeLists.txt`. You can enable or disable them using the `-D` flag with `cmake`.

- `VS_LOGGER_ENABLE_TESTING`: ON | OFF (default: ON)
- `VS_LOGGER_BUILD_EXAMPLES`: ON | OFF (default: ON)
- `BUILD_SHARED_LIBS`: ON | OFF (default: OFF)
- `VS_LOGGER_ENABLE_STATIC_ANALYSIS`: ON | OFF (default: ON)

**Example:** To build a static release library without tests or examples:

```bash
cmake -D CMAKE_BUILD_TYPE=Release -D VS_LOGGER_ENABLE_TESTING=OFF -D VS_LOGGER_BUILD_EXAMPLES=OFF ..
```

### Maintaining Code Quality

#### Code Formatting

To format all source files according to the project's style guide, run the `format` target.

```bash
# Run this from the build directory

cmake --build . --target format
```

#### Static Analysis

Static analysis with `clang-tidy` is automatically integrated into the build process when `VS_LOGGER_ENABLE_STATIC_ANALYSIS` is `ON`. It will run alongside the compiler, and any findings will be printed to the console.

## Contributing

Contributions are welcome! To maintain code quality and consistency, please ensure your contributions adhere to the following guidelines:

- Code Style: All code must be formatted with `clang-format` using the project's `.clang-format` configuration. You can format the entire codebase by running the format target:

```Bash
cmake --build . --target format
```

- Static Analysis: Code should be free of `clang-tidy` warnings. The build system automatically runs `clang-tidy` if it is found on your system.
- Tests: New features should be accompanied by corresponding unit tests.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
