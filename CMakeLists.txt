cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)
project(Protein_pers)


set(DEP_LIBRARY_PATH ${CMAKE_BINARY_DIR}/INSTALL)
file(MAKE_DIRECTORY ${DEP_LIBRARY_PATH})
file(MAKE_DIRECTORY ${DEP_LIBRARY_PATH}/lib)

include(ExternalProject)

set (ANN_BUILD_CMD)
set (ANN_INSTALL_CMD)
if ( APPLE )
	set ( ANN_BUILD_CMD make macosx-g++ )
	set ( ANN_INSTALL_CMD cp lib/libANN.a ${DEP_LIBRARY_PATH}/lib/libANN.a && cp -rf include ${DEP_LIBRARY_PATH}/include )
endif()
if ( UNIX )
	set ( ANN_BUILD_CMD make linux-g++ )
endif()
if ( WIN32 )
	set ( ANN_BUILD_CMD make macosx-g++ )
endif()

ExternalProject_Add(project_ANN
		GIT_REPOSITORY "https://github.com/lixun910/ann.git"
		GIT_TAG "master"
		BUILD_IN_SOURCE 1
		UPDATE_COMMAND ""
		PATCH_COMMAND ""
		CONFIGURE_COMMAND ""
		BUILD_COMMAND make macosx-g++
		INSTALL_COMMAND ${ANN_INSTALL_CMD}
		INSTALL_DIR ${CMAKE_BINARY_DIR}/INSTALL
		)


ExternalProject_Get_Property(project_ANN install_dir)

message(STATUS "Install ANN includes: ${install_dir}/lib/libANN.a")


add_library(ANN STATIC IMPORTED)

set_property(TARGET ANN PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libANN.a)


add_dependencies(ANN project_ANN)

# Boost
find_package(Boost 1.40 COMPONENTS regex date_time system filesystem thread graph program_options REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )
#
#message("boost lib: ${Boost_LIBRARIES}")
#message("boost inc:${Boost_INCLUDE_DIR}")

#CGAL
find_package(CGAL)
include( ${CGAL_USE_FILE} )

#OpenCV
find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui imgcodecs REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories( "." ".." )


add_executable( pers
	Wrappers/GICWrapper.cpp
	Wrappers/GICWrapper.hpp
	Wrappers/SimPersWrapper.cpp
	Wrappers/SimPersWrapper.hpp
	SimPers/AnnotationMatrix.cpp
	SimPers/SimplexNode.h
	SimPers/SimplicialComplex.cpp
	SimPers/SimplicialComplex.h
	SimPers/UnionFindDeletion.cpp
	Graphs/Graph.hpp
	Graphs/KNN_Graph.cpp
	Graphs/KNN_Graph.hpp
	Graphs/NormalGraph.cpp
	Graphs/NormalGraph.hpp
	GIComplex/ANNSearchSampling.cpp
	GIComplex/ANNSearchSampling.h
	GIComplex/DijkstraAlgorithm.cpp
	GIComplex/DijkstraAlgorithm.h
	GIComplex/FibonacciHeap.cpp
	GIComplex/FibonacciHeap.h
	GIComplex/FlagComplex.h
	GIComplex/FlagComplex.cpp
	GIComplex/gic.cpp
	GIComplex/GIComplex.cpp
	GIComplex/GIComplex.h
	GIComplex/LongVector.h
	GIComplex/PointSet.cpp
	GIComplex/PointSet.h
	GIComplex/SimpleGraph.cpp
	GIComplex/SimpleGraph.h
	GIComplex/SimplexNodeGIC.h
	GIComplex/SimplicialComplexGIC.h
	Collapse.hpp
	Collapse.cpp
	Constants.cpp
	Constants.hpp
	GIC.hpp
	GIC.cpp
	main.cpp
	MortonCode.cpp
	MortonCode.hpp
	RandomHomology.cpp
	RandomHomology.hpp
	Utilities.cpp
	Utilities.hpp
	)

message("${Boost_LIBRARIES}")
target_link_libraries(pers  ${OpenCV_LIBS} ANN ${CGAL_LIBRARIES} Boost::program_options Boost::filesystem)
