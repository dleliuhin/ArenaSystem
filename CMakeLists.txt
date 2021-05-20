# \authors Dmitrii Leliuhin
# \date March 2021

#========================================================================================

cmake_minimum_required( VERSION 3.10 FATAL_ERROR )

#========================================================================================

project( arena_system
    LANGUAGES CXX )

#========================================================================================

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

#========================================================================================

include( ${CMAKE_CURRENT_SOURCE_DIR}/external/external.cmake )

#========================================================================================

include_directories( ${CMAKE_SOURCE_DIR} )

include( ${CMAKE_CURRENT_SOURCE_DIR}/src/src.cmake )

#========================================================================================

add_library( ${PROJECT_NAME} ${ARENA_SYSTEM} )

#========================================================================================

target_link_libraries( ${PROJECT_NAME} ${ARENA_LIBS} )

#========================================================================================

unset ( QT_QMAKE_EXECUTABLE )

#========================================================================================
