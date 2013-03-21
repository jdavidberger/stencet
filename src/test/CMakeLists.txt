add_executable(stencet.test stencet.test.cc mscanf.test.cc stencet.tags.cc stencet.expr.cc stencet.filters.cc)
target_link_libraries(stencet.test cppunit stencet)
