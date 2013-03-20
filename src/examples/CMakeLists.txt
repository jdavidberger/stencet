add_executable(demo main.cc)
target_link_libraries(demo stencet)

add_executable(reflect reflect.cc)
target_link_libraries(reflect stencet)

