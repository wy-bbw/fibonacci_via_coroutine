project(fibo_via_coroutines)
cmake_minimum_required(VERSION 4.0.1)

add_executable(fibo)
target_sources(fibo PRIVATE
    src/fibo.cpp
    src/main.cpp
)

target_include_directories(fibo PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(fibo PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED yes
    CXX_EXTENSIONS OFF
)
