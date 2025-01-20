cmake_minimum_required(VERSION 3.31.3 FATAL_ERROR)
project(EdenWindow VERSION 1.0.0)

include(FetchContent)
FetchContent_Declare(eden GIT_REPOSITORY https://github.com/D4N13LxD4V1D/eden.git)
FetchContent_MakeAvailable(eden)

add_executable(EdenWindow "Main.cc")
target_link_libraries(EdenWindow PRIVATE metal-cpp)