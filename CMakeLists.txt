cmake_minimum_required (VERSION 2.8)

set( CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH} )
set( CMAKE_PREFIX_PATH $ENV{CMAKE_PREFIX_PATH} )

project(OBJReader)

if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE "Debug"
		CACHE STRING "Build configuration 'Release' or 'Debug'"
		FORCE )
endif()

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin )
set( LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib )

add_subdirectory(${PROJECT_SOURCE_DIR}/src bin)

