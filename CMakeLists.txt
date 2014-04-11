cmake_minimum_required (VERSION 2.8)
project (jdksavdecc-c)
enable_testing()

option(TODO "Enable TODO items that are in progress" OFF)
option(TESTS "Enable extended test code in library" OFF)

if(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")
    add_definitions("/W2")
else()
    add_definitions("-Wall -Wextra")
endif()

if(TODO MATCHES "ON")
   add_definitions("-DTODO=1")
   message(STATUS "TODO items that are in progress are enabled for compiling")
endif()


set(LIBS ${LIBS} ${CHECK_LIBRARIES} jdksavdecc-c)

include_directories( include )

if(TESTS MATCHES "ON")
   message(STATUS "Extended test code functions are enabled")
   file(GLOB JDKSAVDECC_C_INCLUDES "include/*.h" "include/tests/*.h" )
   file(GLOB JDKSAVDECC_C_SRC "src/*.c" "src/test/*.c")
else()
   file(GLOB JDKSAVDECC_C_INCLUDES "include/*.h" )
   file(GLOB JDKSAVDECC_C_SRC "src/*.c")
endif()

add_library (jdksavdecc-c ${JDKSAVDECC_C_SRC} ${JDKSAVDECC_C_INCLUDES})

INSTALL(TARGETS jdksavdecc-c DESTINATION "lib")

INSTALL(FILES
   ${JDKSAVDECC_C_INCLUDES}
   DESTINATION include
)

link_directories( ${JDKSAVDECC_C_BINARY_DIR} )

if(TESTS MATCHES "ON")
   file(GLOB JDKSAVDECC_C_TESTS "tests/*.c")
   foreach(item ${JDKSAVDECC_C_TESTS})
      GET_FILENAME_COMPONENT(testname ${item} NAME_WE )
      add_executable(${testname} ${item})
      target_link_libraries(${testname} ${LIBS} )
      add_test(NAME ${testname} COMMAND ${testname} )
   endforeach(item)
endif()
