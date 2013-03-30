
FIND_LIBRARY(MXCOMP_LIB mxcomp)

IF(NOT ${MXCOMP_LIB} AND NOT (TARGET mxcomp) )
       IF(NOT (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mxcomp))
       	      MESSAGE("Mxcomp missing, grabbing it.")
	      EXEC_PROGRAM(hg ARGS clone http://hg.code.sf.net/p/mxcomp/code ${CMAKE_CURRENT_SOURCE_DIR}/mxcomp)
       ENDIF()
       ADD_SUBDIRECTORY(mxcomp)
ENDIF()

