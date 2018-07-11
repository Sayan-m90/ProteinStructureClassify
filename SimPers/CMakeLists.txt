#project( Simpers )

#cmake_minimum_required( VERSION 2.8 FATAL_ERROR )

include_directories( ${CMAKE_SOURCE_DIR}/src) 
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# Boost
find_package( Boost 1.4 COMPONENTS program_options system REQUIRED )
include_directories( ${Boost_INCLUDE_DIRS} )
link_directories(${Boost_LIBRARY_DIRS})

#include_directories( "." ".." ) 

add_executable( Simpers  
	Simpers.cpp 
	SimplexNode.h 
	SimplicialComplex.h
	SimplicialComplex.cpp
	UnionFindDeletion.cpp
	AnnotationMatrix.cpp ) 
target_link_libraries( Simpers  ${Boost_LIBRARIES})
