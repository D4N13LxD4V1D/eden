cmake_minimum_required(VERSION 3.31.3 FATAL_ERROR)
project(eden VERSION 1.0.0)

add_library(eden)
file(GLOB_RECURSE CXX_SOURCES CONFIGURE_DEPENDS "src/*.cc")
target_include_directories(eden PUBLIC "include")
target_sources(eden PUBLIC FILE_SET CXX_MODULES FILES ${CXX_SOURCES})
target_compile_features(eden PRIVATE cxx_std_23)

if(APPLE)
    file(GLOB_RECURSE OBJCXX_SOURCES CONFIGURE_DEPENDS "src/*.mm")
    target_sources(eden PUBLIC ${OBJCXX_SOURCES})
    target_link_libraries(eden PUBLIC "-framework Cocoa" "-framework Metal" "-framework MetalKit")
endif()

add_subdirectory(tests)