cmake_minimum_required(VERSION 3.31.3 FATAL_ERROR)
project(Eden VERSION 1.0.0)

file(GLOB_RECURSE CXX_SOURCES CONFIGURE_DEPENDS "src/*.cc")

add_library(Eden)
target_sources(Eden PUBLIC FILE_SET CXX_MODULES FILES ${CXX_SOURCES})
target_compile_features(Eden PUBLIC cxx_std_23)

include(FetchContent)
if(APPLE)
    FetchContent_Declare(metal-cpp GIT_REPOSITORY https://github.com/D4N13LxD4V1D/metal-cpp.git)
    FetchContent_MakeAvailable(metal-cpp)
    target_link_libraries(Eden PUBLIC metal-cpp)
endif()