cmake_minimum_required(VERSION 3.16)

project(CQLater
    VERSION 1.0
    LANGUAGES C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(CQLater
    src/main.c
    src/complex.c
    src/matrix.c
    src/quantum_circuit.c
    src/quantum_gate.c
)

target_include_directories(CQLater
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
