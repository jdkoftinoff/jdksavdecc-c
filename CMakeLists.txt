cmake_minimum_required (VERSION 2.8) 
project (jdksavdecc-c)
enable_testing()

set(LIBS ${LIBS} ${CHECK_LIBRARIES} jdksavdecc-c)

include_directories( include )

file(GLOB_RECURSE JDKSAVDECC_C_INCLUDES "include/*.h" )

file(GLOB_RECURSE JDKSAVDECC_C_SRC "src/*.c" )

add_library (jdksavdecc-c ${JDKSAVDECC_C_SRC} ${JDKSAVDECC_C_INCLUDES})

INSTALL(TARGETS jdksavdecc-c DESTINATION "lib")

INSTALL(FILES
   ${JDKSAVDECC_C_INCLUDES}
   DESTINATION include
)

link_directories( ${JDKSAVDECC_C_BINARY_DIR} )


