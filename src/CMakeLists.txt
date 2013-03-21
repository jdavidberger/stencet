add_library(stencet 
		     template.cc 
		     viewModel.cc 
		     viewContext.cc 
		     parser.cc
		     variant.cc

		     tags/ForTag.cc 
		     tags/tag.cc 
		     tags/IfTag.cc 
		     tags/IncludeTag.cc 
		     tags/ExtendsTag.cc 
		     tags/BlockTag.cc 
		     	      
		     filters/capfirst.cc
		     expression.cc
	)

target_link_libraries(stencet dl)
install(TARGETS stencet DESTINATION lib)

add_subdirectory(examples)
add_subdirectory(test)
