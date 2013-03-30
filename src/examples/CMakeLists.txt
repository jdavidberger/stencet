add_executable(demo main.cc)
target_link_libraries(demo stencet)

add_executable(reflect reflect.cc)
add_library(ReflectTest SHARED reflect.cc)
target_link_libraries(reflect stencet boost_python python2.7)
target_link_libraries(ReflectTest stencet boost_python python2.7)

