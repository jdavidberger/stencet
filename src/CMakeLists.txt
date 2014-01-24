add_library(stencet 
		     template.cc 
		     viewModel.cc 
		     viewContext.cc 
		     parser.cc
		     variant.cc
		     expression.cc
		     region.cc

		     tags/ForTag.cc 
		     tags/tag.cc 
		     tags/IfTag.cc 
		     tags/IncludeTag.cc 
		     tags/ExtendsTag.cc 
		     tags/BlockTag.cc 
		     tags/CycleTag.cc
		     tags/NowTag.cc
		     tags/SpacelessTag.cc
		     tags/CommentTag.cc
		     tags/VerbatimTag.cc

		     filters/filter.cc
		     filters/capfirst.cc
		     filters/default.cc
	)


IF(NOT ${WIN32})
	target_link_libraries(stencet dl)
ENDIF()

install(TARGETS stencet DESTINATION lib)

IF( ${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})
    message("Making stencet examples and tests")
    add_subdirectory(examples)
    add_subdirectory(test)
ENDIF()
