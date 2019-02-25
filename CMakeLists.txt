project(xspy)
cmake_minimum_required(VERSION 2.8)

set(CompilerFlags CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE )
foreach(CompilerFlag ${CompilerFlags})
  string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
endforeach()

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(WTL_DIR "wtl include directory" CACHE PATH "wtl include directory")
include_directories(${WTL_DIR})

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
  # x64
  SET( PLATFORM_NAME "-x64" )
  SET( PLATFORM_NAME1 "x64" )
else( CMAKE_SIZEOF_VOID_P EQUAL 8 ) 
  # x86
  SET( PLATFORM_NAME "" )
  SET( PLATFORM_NAME1 "" )
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

set(LIB_LDE64 ${CMAKE_CURRENT_SOURCE_DIR}/xspydll/LDE64${PLATFORM_NAME1}.lib)

aux_source_directory(xspydll SRC_XSPYDLL)
# list(REMOVE_ITEM SRC_XSPYDLL )

add_library(xspydll SHARED ${SRC_XSPYDLL})
set(CMAKE_SHARED_LINKER_FLAGS
  "${CMAKE_SHARED_LINKER_FLAGS} /DEF:${CMAKE_CURRENT_SOURCE_DIR}/xspydll/xspydll.def /SUBSYSTEM:WINDOWS,5.01 /SAFESEH:NO")
set_target_properties(xspydll PROPERTIES SUFFIX ${PLATFORM_NAME}.dll)
target_link_libraries(xspydll ${LIB_LDE64} Psapi)
target_compile_definitions(xspydll PRIVATE XSPYDLL_EXPORTS=1)

aux_source_directory(xspy SRC_XSPY)
add_executable(xspy WIN32 ${SRC_XSPY} xspy/xspy.rc)
set_target_properties(xspy PROPERTIES SUFFIX ${PLATFORM_NAME}.exe)
target_link_libraries(xspy xspydll)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS,5.01")