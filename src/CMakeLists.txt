﻿if(NOT EXISTS ${CMAKE_BINARY_DIR}/fb.zip)
	# file(DOWNLOAD "https://jaist.dl.sourceforge.net/project/winflexbison/win_flex_bison-latest.zip" ${CMAKE_BINARY_DIR}/fb.zip)
	file(DOWNLOAD "https://github.com/lexxmark/winflexbison/releases/download/v2.5.25/win_flex_bison-2.5.25.zip" ${CMAKE_BINARY_DIR}/fb.zip)
	file(ARCHIVE_EXTRACT INPUT ${CMAKE_BINARY_DIR}/fb.zip DESTINATION ${CMAKE_BINARY_DIR}/bison)
endif()
if(WIN32)
set(ENV{PATH} "${CMAKE_BINARY_DIR}/bison;$ENV{PATH}")
else()
set(ENV{PATH} "${CMAKE_BINARY_DIR}/bison:$ENV{PATH}")
endif()
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
router_directories()