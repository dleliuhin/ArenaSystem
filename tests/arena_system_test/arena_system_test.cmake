#========================================================================================

include_directories( ${CMAKE_CURRENT_LIST_DIR} )

set( ARENA_SYSTEM_TEST
    ${CMAKE_CURRENT_LIST_DIR}/test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/arena_system_test.h
    ${CMAKE_CURRENT_LIST_DIR}/arena_system_test.cpp )

if ( CONNECTED )
	list( APPEND ARENA_SYSTEM_TEST
    	${CMAKE_CURRENT_LIST_DIR}/arena_system_test_connected.cpp )
elseif()
	list( APPEND ARENA_SYSTEM_TEST
    	${CMAKE_CURRENT_LIST_DIR}/arena_system_test_disconnected.cpp )
endif()

#========================================================================================
