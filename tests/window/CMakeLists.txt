add_executable(Window Main.cc)
target_compile_features(Window PRIVATE cxx_std_23)
target_link_libraries(Window PRIVATE eden)