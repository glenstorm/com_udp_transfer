cmake_minimum_required(VERSION 3.9)
set(PROJECT_NAME com_upd_transfer)
project(${PROJECT_NAME})

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -rdynamic")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -rdynamic -s")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -rdynamic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -rdynamic")

if(UNIX)
	if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.9)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color")
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11")
	else(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.9)
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++0x")
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++0x")
	endif(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.9)
	set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")
endif(UNIX)


set(SOURCE
main.cpp
serialstream.cpp
)

include_directories(
${PROJECT_SOURCE_DIR}
)

find_package(Boost COMPONENTS date_time system REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost::{date_time|system}")
	return()
else()
	include_directories(${Boost_INCLUDE_DIRS})
endif()

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

##########################################################
add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME}
                      ${Boost_LIBRARIES})
