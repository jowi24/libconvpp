# --- determine some library dependend variables ------------------------------
STRING(REGEX REPLACE .*/lib "" LIBNAME ${CMAKE_CURRENT_LIST_DIR})
AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_LIST_DIR} SRCS)

# --- general setup -----------------------------------------------------------
cmake_minimum_required(VERSION 2.6)
project (lib${LIBNAME})

#set(CMAKE_VERBOSE_MAKEFILE true) # <-- enable for debugging
#set(CMAKE_BUILD_TYPE "Debug")    # <-- enable for debugging 

# --- compile and link --------------------------------------------------------
include_directories(${lib${LIBNAME}_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_library(${LIBNAME} STATIC ${SRCS})

# --- tests -------------------------------------------------------------------
if (EXISTS ${lib${LIBNAME}_SOURCE_DIR}/test)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undef -DSOURCE_DIR=\\\"${lib${LIBNAME}_SOURCE_DIR}\\\"")
  include_directories(${lib${LIBNAME}_SOURCE_DIR}/..)
  include_directories(${lib${LIBNAME}_SOURCE_DIR}/test)
  AUX_SOURCE_DIRECTORY(test LIBTESTFILES)
  add_executable(lib${LIBNAME}test ${LIBTESTFILES} test/gtest/gtest-all.cc test/gtest/gtest_main.cc)
  target_link_libraries(lib${LIBNAME}test ${LIBNAME} pthread
                        ${CMAKE_THREAD_LIBS_INIT}
                        )
endif (EXISTS ${lib${LIBNAME}_SOURCE_DIR}/test)

