cmake_minimum_required(VERSION 3.10)
project(CajeroCierreDiario)
set(CMAKE_CXX_STANDARD 17)

# ESTA LÍNEA ES LA QUE SOLUCIONA TU ERROR:
include_directories(include)

add_executable(cajero_app 
    src/main.cpp 
    src/cajero.cpp 
    src/repositorio.cpp
)

add_executable(cajero_tests 
    tests/cajero_tests.cpp 
    src/cajero.cpp 
    src/repositorio.cpp
)