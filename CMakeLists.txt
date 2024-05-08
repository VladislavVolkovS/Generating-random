cmake_minimum_required(VERSION 3.0.0)
project(sampler-generators VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(
    sampler-generators main.cpp
    halton/halton.cpp
    sobol/sobol.cpp
    scrambling/scramble.cpp
    random.cpp sampler.cpp
    # blue_noise/bridson_bn.cpp
    # blue_noise/mitchels_bn.cpp
    # blue_noise/blue_noise_1D.cpp
    # blue_noise/blue_noise_2D.cpp
    uniform/uniform.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
