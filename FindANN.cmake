#---------------------------------------------------------------------------
# Get and build ANN
message( "External project - ANN" )

#include(FindPackageHandleStandardArgs)

set (ANN_BUILD_CMD)
set (ANN_INSTALL_CMD)
if ( APPLE )
    set ( ANN_BUILD_CMD make macosx-g++ )
    set ( ANN_INSTALL_CMD cp lib/libANN.a ${DEP_LIBRARY_PATH}/lib )
endif()
if ( UNIX )
    set ( ANN_BUILD_CMD "make linux-g++" )
endif()
if ( WIN32 )
    set ( ANN_BUILD_CMD "make macosx-g++" )
endif()

macro(DO_FIND_ANN_DOWNLOAD)
    ExternalProject_Add(project_ANN
            GIT_REPOSITORY "https://github.com/lixun910/ann.git"
            GIT_TAG "master"
            BUILD_IN_SOURCE 1
            UPDATE_COMMAND ""
            PATCH_COMMAND ""
            CONFIGURE_COMMAND ""
            BUILD_COMMAND make macosx-g++
            INSTALL_COMMAND ${ANN_INSTALL_CMD}
            )
endmacro()

set( ANN_LIBRARY )
if( UNIX )
    set( ANN_LIBRARY ${DEP_LIBRARY_PATH}/lib/libANN.a )
else()
    if( WIN32 )
        set( ANN_LIBRARY ${DEP_LIBRARY_PATH}/lib/libANN.a )
    endif()
endif()

if(NOT ANN_FOUND)
    DO_FIND_ANN_DOWNLOAD()
    set(ANN_FOUND 1)
    set(ANN_INCLUDE_DIRS ${DEP_LIBRARY_PATH}/include)
    set(ANN_LIBRARIES ${ANN_LIBRARY})
endif()

# request ANN libray and compile on-the-fly
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
find_package(ANN)
if (ANN_FOUND)
    message(STATUS "Install ANN includes: ${ANN_INCLUDE_DIRS}")
    message(STATUS "Install ANN libraries: ${ANN_LIBRARIES}")
    include_directories(${ANN_INCLUDE_DIRS})
    target_link_libraries(SocialWeightsProject ${ANN_LIBRARIES})
endif()