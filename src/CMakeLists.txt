add_library(templace 
		     template.cc 
		     viewModel.cc 
		     viewContext.cc 
		     tags/ForTag.cc 
		     tags/tag.cc 
		     tags/IfTag.cc 
		     tags/IncludeTag.cc 
		     tags/ExtendsTag.cc 
		     tags/BlockTag.cc 
		     expression.cc
	)

target_link_libraries(templace dl)
add_subdirectory(examples)
add_subdirectory(test)
