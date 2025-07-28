# if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/win_flex_bison.zip)
# 	# file(DOWNLOAD "https://jaist.dl.sourceforge.net/project/winflexbison/win_flex_bison-latest.zip" ${CMAKE_CURRENT_BINARY_DIR}/fb.zip)
# 	file(ARCHIVE_EXTRACT INPUT ${CMAKE_CURRENT_BINARY_DIR}/win_flex_bison.zip DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bison)
# endif()
# if(WIN32)
# set(ENV{PATH} "${CMAKE_CURRENT_BINARY_DIR}/bison;$ENV{PATH}")
# else()
# set(ENV{PATH} "${CMAKE_CURRENT_BINARY_DIR}/bison:$ENV{PATH}")
# endif()
cmake_path(GET CMAKE_CURRENT_LIST_DIR STEM PROJ)
flex_target(${PROJ}_SCANNER ok.l ${CMAKE_CURRENT_BINARY_DIR}/ok.lex.cpp
DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/ok.lex.h"
OPTIONS "--wincompat"
)
bison_target(${PROJ}_PARSER ok.y ${CMAKE_CURRENT_BINARY_DIR}/ok.yacc.cpp
DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/ok.yacc.h"
OPTIONS "")
add_flex_bison_dependency(${PROJ}_SCANNER ${PROJ}_PARSER)
cmake_path(GET FLEX_${PROJ}_SCANNER_OUTPUT_HEADER FILENAME ${PROJ}_SCANNER_HEADER)
cmake_path(GET BISON_${PROJ}_PARSER_OUTPUT_HEADER FILENAME ${PROJ}_PARSER_HEADER)
configure_file(pch.h.in pch.h)
include_directories(${FLEX_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
add_executable(${PROJ} yacc.cpp
${FLEX_${PROJ}_SCANNER_OUTPUTS}
${BISON_${PROJ}_PARSER_OUTPUTS}
)