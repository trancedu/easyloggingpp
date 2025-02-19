cmake_minimum_required(VERSION 3.10)
project(EasyloggingTest CXX)

# Add this line to generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
add_executable(performance_test
    main.cpp
    ${CMAKE_SOURCE_DIR}/../src/easylogging++.cc
)

# Add include directories
target_include_directories(performance_test PRIVATE
    ${CMAKE_SOURCE_DIR}/../src
)

# Define required preprocessor macros
target_compile_definitions(performance_test PRIVATE
    ELPP_FEATURE_ALL
    ELPP_FEATURE_PERFORMANCE_TRACKING
    ELPP_STL_LOGGING
    ELPP_THREAD_SAFE
)

# Link against required libraries
target_link_libraries(performance_test PRIVATE
    pthread
) 