cmake_minimum_required(VERSION 3.21)

project(
        parser
        DESCRIPTION "Shift-reduce parser for arithmetical language"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
  message(STATUS "CMAKE_BUILD_TYPE is not specified, using Release by default")
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(SRC_DIR src)
set(INC_DIR inc)

find_package(FLEX REQUIRED)
FLEX_TARGET(lexer ${CMAKE_SOURCE_DIR}/rules/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)

file(GLOB SOURCES CONFIGURE_DEPENDS ${SRC_DIR}/*.cpp)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(${PROJECT_NAME} 
  ${SOURCES}
  ${FLEX_lexer_OUTPUTS}
  )

target_include_directories(${PROJECT_NAME} PUBLIC ${INC_DIR})

option(VERBOSE "Dump parsing process" OFF)
if (VERBOSE)
  target_compile_definitions(${PROJECT_NAME} PRIVATE -DVERBOSE)
endif()

option(DUMP "Dump AST in DOT format" OFF)
if (DUMP)
  target_compile_definitions(${PROJECT_NAME} PRIVATE -DDUMP)
endif()

option(DUMP_JSON "Make lexer dump parsed tokens in json format" OFF)
if (DUMP_JSON)
  target_compile_definitions(${PROJECT_NAME} PRIVATE -DDUMP_JSON)
endif()
