cmake_minimum_required(VERSION 3.2)
project(PAL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
BISON_TARGET(PARSER src/Parser/parser.y ${CMAKE_CURRENT_BINARY_DIR}/Parser.cpp)
FLEX_TARGET(LEXER src/Parser/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/Lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(LEXER PARSER)

include_directories(${CMAKE_CURRENT_BINARY_DIR} src/Include)
add_executable(pal_parser src/main.cpp src/Rule.cpp src/Include/Rule.h src/Act.cpp src/Include/Act.h src/Predicate.cpp src/Include/Predicate.h src/APS.cpp src/Include/APS.h ${BISON_PARSER_OUTPUTS} ${FLEX_LEXER_OUTPUTS} src/Include/Helpers.h)
