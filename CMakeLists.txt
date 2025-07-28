cmake_minimum_required(VERSION 3.10)
find_package(Git REQUIRED)
if(NOT EXISTS ${CMAKE_BINARY_DIR}/cmake_module)
execute_process(COMMAND ${GIT_EXECUTABLE} clone https://gitee.com/yingquelou/cmakeModule.git ${CMAKE_BINARY_DIR}/cmake_module
COMMAND_ECHO STDOUT)
endif()
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR}/cmake_module ${CMAKE_MODULE_PATH})
cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME PROJ)


project(${PROJ})
include(router)
if(MINGW)
    add_link_options(-static)
endif()
router_directories()
