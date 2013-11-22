cmake_minimum_required (VERSION 2.8) 
project (jdksavdecc-c)
enable_testing()

set(LIBS ${LIBS} ${CHECK_LIBRARIES} jdksavdecc-c)

include_directories( include )

file(GLOB_RECURSE JDKSAVDECC_C_INCLUDES include  "*.h" )

file(GLOB_RECURSE JDKSAVDECC_C_SRC src  "*.c" )

add_library (jdksavdecc-c ${JDKSAVDECC_C_SRC} ${JDKSAVDECC_C_INCLUDES})

INSTALL(TARGETS jdksavdecc-c DESTINATION "lib")

INSTALL(FILES
   ${JDKSAVDECC_C_INCLUDES}
   DESTINATION include
)

link_directories( ${JDKSAVDECC_C_BINARY_DIR} )

add_executable(test_jdksavdecc_acmp_controller tests/test_jdksavdecc_acmp_controller.c)
target_link_libraries(test_jdksavdecc_acmp_controller ${LIBS})
add_test(test_jdksavdecc_acmp_controller ${CMAKE_CURRENT_BINARY_DIR}/test_jdksavdecc_acmp_controller)

add_executable(test_jdksavdecc_acmp_conversations tests/test_jdksavdecc_acmp_conversations.c)
target_link_libraries(test_jdksavdecc_acmp_conversations ${LIBS})
add_test(test_jdksavdecc_acmp_conversations ${CMAKE_CURRENT_BINARY_DIR}/test_jdksavdecc_acmp_conversations)

add_executable(test_jdksavdecc_acmp_listener tests/test_jdksavdecc_acmp_listener.c)
target_link_libraries(test_jdksavdecc_acmp_listener ${LIBS})
add_test(test_jdksavdecc_acmp_listener ${CMAKE_CURRENT_BINARY_DIR}/test_jdksavdecc_acmp_listener)

add_executable(test_jdksavdecc_acmp_talker tests/test_jdksavdecc_acmp_talker.c)
target_link_libraries(test_jdksavdecc_acmp_talker ${LIBS})
add_test(test_jdksavdecc_acmp_talker ${CMAKE_CURRENT_BINARY_DIR}/test_jdksavdecc_acmp_talker)

add_executable(test_jdksavdecc_adp_advertise tests/test_jdksavdecc_adp_advertise.c)
target_link_libraries(test_jdksavdecc_adp_advertise ${LIBS})
add_test(test_jdksavdecc_adp_advertise ${CMAKE_CURRENT_BINARY_DIR}/test_jdksavdecc_adp_advertise)

add_executable(test_jdksavdecc_adp_discover tests/test_jdksavdecc_adp_discover.c)
target_link_libraries(test_jdksavdecc_adp_discover ${LIBS})
add_test(test_jdksavdecc_adp_discover ${CMAKE_CURRENT_BINARY_DIR}/test_jdksavdecc_adp_discover)

add_executable(test_jdksavdecc_aecp tests/test_jdksavdecc_aecp.c)
target_link_libraries(test_jdksavdecc_aecp ${LIBS})
add_test(test_jdksavdecc_aecp ${CMAKE_CURRENT_BINARY_DIR}/test_jdksavdecc_aecp)

add_executable(test_jdksavdecc_aem_entity tests/test_jdksavdecc_aem_entity.c)
target_link_libraries(test_jdksavdecc_aem_entity ${LIBS})
add_test(test_jdksavdecc_aem_entity ${CMAKE_CURRENT_BINARY_DIR}/test_jdksavdecc_aem_entity)

add_executable(test_jdksavdecc_apc tests/test_jdksavdecc_apc.c)
target_link_libraries(test_jdksavdecc_apc ${LIBS})
add_test(test_jdksavdecc_apc ${CMAKE_CURRENT_BINARY_DIR}/test_jdksavdecc_apc)

add_executable(test_jdksavdecc_aps tests/test_jdksavdecc_aps.c)
target_link_libraries(test_jdksavdecc_aps ${LIBS})
add_test(test_jdksavdecc_aps ${CMAKE_CURRENT_BINARY_DIR}/test_jdksavdecc_aps)

add_executable(test_jdksavdecc_command_dispatch tests/test_jdksavdecc_command_dispatch.c)
target_link_libraries(test_jdksavdecc_command_dispatch ${LIBS})
add_test(test_jdksavdecc_command_dispatch ${CMAKE_CURRENT_BINARY_DIR}/test_jdksavdecc_command_dispatch)

add_executable(test_jdksavdecc_descriptor_dispatch tests/test_jdksavdecc_descriptor_dispatch.c)
target_link_libraries(test_jdksavdecc_descriptor_dispatch ${LIBS})
add_test(test_jdksavdecc_descriptor_dispatch ${CMAKE_CURRENT_BINARY_DIR}/test_jdksavdecc_descriptor_dispatch)

add_executable(test_jdksavdecc_maap tests/test_jdksavdecc_maap.c)
target_link_libraries(test_jdksavdecc_maap ${LIBS})
add_test(test_jdksavdecc_maap ${CMAKE_CURRENT_BINARY_DIR}/test_jdksavdecc_maap)

add_executable(test_jdksavdecc_pdu tests/test_jdksavdecc_pdu.c)
target_link_libraries(test_jdksavdecc_pdu ${LIBS})
add_test(test_jdksavdecc_pdu ${CMAKE_CURRENT_BINARY_DIR}/test_jdksavdecc_pdu)

add_executable(test_jdksavdecc_pdu_dispatch tests/test_jdksavdecc_pdu_dispatch.c)
target_link_libraries(test_jdksavdecc_pdu_dispatch ${LIBS})
add_test(test_jdksavdecc_pdu_dispatch ${CMAKE_CURRENT_BINARY_DIR}/test_jdksavdecc_pdu_dispatch)

add_executable(test_jdksavdecc_util tests/test_jdksavdecc_util.c)
target_link_libraries(test_jdksavdecc_util ${LIBS})
add_test(test_jdksavdecc_util ${CMAKE_CURRENT_BINARY_DIR}/test_jdksavdecc_util)


add_executable(test_jdksavdecc_descriptor_storage tests/test_jdksavdecc_descriptor_storage.c)
target_link_libraries(test_jdksavdecc_descriptor_storage ${LIBS})
add_test(test_jdksavdecc_descriptor_storage ${CMAKE_CURRENT_BINARY_DIR}/test_jdksavdecc_descriptor_storage)
