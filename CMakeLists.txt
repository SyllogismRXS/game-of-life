cmake_minimum_required (VERSION 2.6)
project (gol)

set(GOL_VERSION_MAJOR "0")
set(GOL_VERSION_MINOR "0")
set(GOL_VERSION_PATCH "0")
set(GOL_VERSION "${GOL_VERSION_MAJOR}.${GOL_VERSION_MINOR}.${GOL_VERSION_PATCH}")
set(GOL_VERSION_DATE "2012.12.30")

# give GOL 1 series a few more soversions
set(GOL_SOVERSION "00")

set(CMAKE_INSTALL_PREFIX /usr/local)

# fetch all the local directories for generated code
get_filename_component(GOL_LIB_DIR ./lib ABSOLUTE)
get_filename_component(GOL_BIN_DIR ./bin ABSOLUTE)
get_filename_component(GOL_INC_DIR ./include ABSOLUTE)
get_filename_component(GOL_SRC_DIR ./src ABSOLUTE)
get_filename_component(GOL_SHARE_DIR ./share ABSOLUTE)
get_filename_component(GOL_BUILD_DIR ./build ABSOLUTE)
get_filename_component(GOL_SCRIPTS_DIR ./scripts ABSOLUTE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "-g -Wall")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall") # -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall") # -fprofile-arcs -ftest-coverage")

set(EXECUTABLE_OUTPUT_PATH ${GOL_BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${GOL_LIB_DIR})

## set the cmake defaults for libraries and binaries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${GOL_LIB_DIR} CACHE PATH 
  "Output directory for the dynamic libraries" )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GOL_BIN_DIR} CACHE PATH
  "Output directory for the binaries" )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${GOL_LIB_DIR} CACHE PATH 
  "Output directory for the static libraries (archives)" )

INSTALL(DIRECTORY ${GOL_INC_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX}
  FILES_MATCHING REGEX .*\\.h|.*\\.proto
)

#INSTALL(TARGETS ${} 
#  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
#  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
#)

install(DIRECTORY ${GOL_LIB_DIR}/ 
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  )

## let cmake know where the headers are
include_directories(${GOL_INC_DIR})

## copy to gol/include
file(GLOB_RECURSE INCLUDE_FILES RELATIVE ${GOL_SRC_DIR} src/*.h)
foreach(I ${INCLUDE_FILES})
  configure_file(${GOL_SRC_DIR}/${I} ${GOL_INC_DIR}/${I} @ONLY)
endforeach()

add_subdirectory(src)
add_subdirectory(share)
