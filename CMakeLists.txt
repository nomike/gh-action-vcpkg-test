cmake_minimum_required(VERSION 3.20)
project(vcpkg-test-app VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the lib3mf package
find_package(lib3mf REQUIRED)

# Create the executable
add_executable(vcpkg-test-app src/main.cpp)

# Link lib3mf
target_link_libraries(vcpkg-test-app PRIVATE lib3mf::lib3mf)

# Set output directory
set_target_properties(vcpkg-test-app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)