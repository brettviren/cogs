cmake_minimum_required(VERSION 3.12)
project(cogs VERSION 1.0.0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../daq-buildtools/cmake ${CMAKE_MODULE_PATH})
include(DAQ)

daq_setup_environment()

find_package(ers REQUIRED)

find_package(nlohmann_json 3.8.0 )

if(NOT ${nlohmann_json_FOUND})
  message("nlohmann_json NOT FOUND! Downloading single-header from GitHub!")
  file(DOWNLOAD https://github.com/nlohmann/json/raw/v3.8.0/single_include/nlohmann/json.hpp nlohmann/json.hpp)
  include_directories(${CMAKE_BINARY_DIR})
endif()

# Can delete this include_directories line when "./inc" gets renamed "./include"
include_directories( ./inc )


##############################################################################
daq_point_build_to( src )

add_library(cogs src/stream.cpp)
target_link_libraries(cogs ers::ers)
target_include_directories(cogs PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> )

##############################################################################
daq_point_build_to( demo )

add_executable(cogs-demo demo/cogs-demo.cpp demo/comp.cpp  demo/factory.cpp  demo/node.cpp)
target_link_libraries(cogs-demo cogs)

install(FILES       demo/generate.sh demo/clean.sh 
        DESTINATION ./demo 
        PERMISSIONS OWNER_EXECUTE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ)

install(FILES       demo/comp-schema.jsonnet demo/demo-config.jsonnet demo/node-schema.jsonnet demo/demo-codegen.jsonnet demo/head-schema.jsonnet 
	DESTINATION ./demo
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)      

##############################################################################
daq_point_build_to( test )

function( cogs_add_test testlabel )
  add_executable(test_${testlabel} test/test_${testlabel}.cpp)
  target_link_libraries(test_${testlabel} cogs)
endfunction()

cogs_add_test(stream)
cogs_add_test(nljs_sub)
cogs_add_test(logging)
cogs_add_test(exceptions)

##############################################################################

daq_install( TARGETS cogs-demo cogs )

# Can delete this include_directories line when "./inc" gets renamed "./include"
install(DIRECTORY inc/${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*.h??")
