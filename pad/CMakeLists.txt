cmake_minimum_required(VERSION 4.2)
project(pad LANGUAGES CXX)

add_library(pad STATIC pad.cpp tokenizer.cpp parser.cpp)
target_include_directories(pad PUBLIC .)

option(PAD_TEST "Build pad tests" OFF)
option(PAD_CLI "Build pad-cli" OFF)

if(PAD_CLI)
  find_package(Curses REQUIRED)
  add_executable(pad-cli pad-cli.cc)
  target_include_directories(pad-cli PRIVATE ${CURSES_INCLUDE_DIR})
  target_link_libraries(pad-cli PRIVATE pad ${CURSES_LIBRARIES})
endif()

if(PAD_TEST)
  find_package(GTest REQUIRED)
  add_executable(pad-test pad-test.cc tokenizer-test.cc parser-test.cc)
  target_link_libraries(pad-test PRIVATE pad GTest::gtest_main GTest::gmock)
endif()
