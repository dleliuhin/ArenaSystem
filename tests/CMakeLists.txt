# \authors Dmitrii Leliuhin
# \date March 2021

#========================================================================================

cmake_minimum_required( VERSION 3.10 FATAL_ERROR )

#========================================================================================

project( test_arena_system )

#========================================================================================

option( CONNECTED FALSE )

if( CONNECTED )
    add_definitions( -DCONNECTED )
endif()

#========================================================================================

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage" )

#========================================================================================

include( ${CMAKE_CURRENT_SOURCE_DIR}/../external/external.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/../src/src.cmake )

#========================================================================================

include_directories( ${CMAKE_SOURCE_DIR} )

include( ${CMAKE_CURRENT_SOURCE_DIR}/arena_system_test/arena_system_test.cmake )

#========================================================================================

add_executable( ${PROJECT_NAME}
    ${ARENA_SYSTEM}
    ${ARENA_SYSTEM_TEST} )

target_link_libraries( ${PROJECT_NAME}
    ${ARENA_LIBS}
    -lgtest
    -fprofile-arcs )

#========================================================================================

unset ( QT_QMAKE_EXECUTABLE )

#========================================================================================
