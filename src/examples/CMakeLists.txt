add_executable(demo main.cc)
target_link_libraries(demo templace)

add_executable(reflect reflect.cc)
target_link_libraries(reflect templace)

