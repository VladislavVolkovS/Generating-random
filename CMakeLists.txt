cmake_minimum_required(VERSION 3.0.0)
project(sampler-generators VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(sampler-generators main.cpp halton.cpp sobol.cpp scramble.cpp random.cpp sampler.cpp blue_noise.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
