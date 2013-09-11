cmake_minimum_required (VERSION 2.8) 
project (jdksavdecc)
enable_testing()

set(LIBS ${LIBS} ${CHECK_LIBRARIES} jdksavdecc)

include_directories( include )

add_library (jdksavdecc src/jdksavdecc.c src/jdksavdecc_acmp.c src/jdksavdecc_acmp_controller.c src/jdksavdecc_acmp_listener.c src/jdksavdecc_acmp_print.c src/jdksavdecc_acmp_talker.c src/jdksavdecc_adp.c src/jdksavdecc_adp_advertise.c src/jdksavdecc_adp_advertising_entity.c src/jdksavdecc_adp_advertising_interface.c src/jdksavdecc_adp_discover.c src/jdksavdecc_adp_print.c src/jdksavdecc_aecp.c src/jdksavdecc_aecp_aa.c src/jdksavdecc_aecp_aem.c src/jdksavdecc_aecp_avc.c src/jdksavdecc_aecp_hdcp_apm.c src/jdksavdecc_aecp_print.c src/jdksavdecc_aecp_vendor.c src/jdksavdecc_aem_command.c src/jdksavdecc_aem_descriptor.c src/jdksavdecc_aem_entity.c src/jdksavdecc_apc.c src/jdksavdecc_app.c src/jdksavdecc_app_print.c src/jdksavdecc_aps.c src/jdksavdecc_command_dispatch.c src/jdksavdecc_command_dispatch_print.c src/jdksavdecc_descriptor_dispatch.c src/jdksavdecc_descriptor_dispatch_print.c src/jdksavdecc_log.c src/jdksavdecc_maap.c src/jdksavdecc_maap_print.c src/jdksavdecc_pcapfile.c src/jdksavdecc_pdu.c src/jdksavdecc_pdu_dispatch.c src/jdksavdecc_pdu_dispatch_print.c src/jdksavdecc_pdu_print.c src/jdksavdecc_print.c src/jdksavdecc_state_machine.c src/jdksavdecc_state_machines.c src/jdksavdecc_test.c src/jdksavdecc_util.c src/jdksavdecc_world.c
    include/jdksavdecc.h include/jdksavdecc_acmp.h include/jdksavdecc_acmp_controller.h include/jdksavdecc_acmp_listener.h include/jdksavdecc_acmp_print.h include/jdksavdecc_acmp_talker.h include/jdksavdecc_adp.h include/jdksavdecc_adp_advertise.h include/jdksavdecc_adp_advertising_entity.h include/jdksavdecc_adp_advertising_interface.h include/jdksavdecc_adp_discover.h include/jdksavdecc_adp_print.h include/jdksavdecc_aecp.h include/jdksavdecc_aecp_aa.h include/jdksavdecc_aecp_aem.h include/jdksavdecc_aecp_avc.h include/jdksavdecc_aecp_hdcp_apm.h include/jdksavdecc_aecp_print.h include/jdksavdecc_aecp_vendor.h include/jdksavdecc_aem_command.h include/jdksavdecc_aem_descriptor.h include/jdksavdecc_aem_entity.h include/jdksavdecc_apc.h include/jdksavdecc_app.h include/jdksavdecc_app_print.h include/jdksavdecc_aps.h include/jdksavdecc_command_dispatch.h include/jdksavdecc_command_dispatch_print.h include/jdksavdecc_descriptor_dispatch.h include/jdksavdecc_descriptor_dispatch_print.h include/jdksavdecc_log.h include/jdksavdecc_maap.h include/jdksavdecc_maap_print.h include/jdksavdecc_msinttypes.h include/jdksavdecc_msstdint.h include/jdksavdecc_pcapfile.h include/jdksavdecc_pdu.h include/jdksavdecc_pdu_dispatch.h include/jdksavdecc_pdu_dispatch_print.h include/jdksavdecc_pdu_print.h include/jdksavdecc_print.h include/jdksavdecc_state_machine.h include/jdksavdecc_state_machines.h include/jdksavdecc_test.h include/jdksavdecc_util.h include/jdksavdecc_world.h
)

INSTALL(TARGETS jdksavdecc DESTINATION "lib")

INSTALL(FILES
include/jdksavdecc.h include/jdksavdecc_acmp.h include/jdksavdecc_acmp_controller.h include/jdksavdecc_acmp_listener.h include/jdksavdecc_acmp_print.h include/jdksavdecc_acmp_talker.h include/jdksavdecc_adp.h include/jdksavdecc_adp_advertise.h include/jdksavdecc_adp_advertising_entity.h include/jdksavdecc_adp_advertising_interface.h include/jdksavdecc_adp_discover.h include/jdksavdecc_adp_print.h include/jdksavdecc_aecp.h include/jdksavdecc_aecp_aa.h include/jdksavdecc_aecp_aem.h include/jdksavdecc_aecp_avc.h include/jdksavdecc_aecp_hdcp_apm.h include/jdksavdecc_aecp_print.h include/jdksavdecc_aecp_vendor.h include/jdksavdecc_aem_command.h include/jdksavdecc_aem_descriptor.h include/jdksavdecc_aem_entity.h include/jdksavdecc_apc.h include/jdksavdecc_app.h include/jdksavdecc_app_print.h include/jdksavdecc_aps.h include/jdksavdecc_command_dispatch.h include/jdksavdecc_command_dispatch_print.h include/jdksavdecc_descriptor_dispatch.h include/jdksavdecc_descriptor_dispatch_print.h include/jdksavdecc_log.h include/jdksavdecc_maap.h include/jdksavdecc_maap_print.h include/jdksavdecc_msinttypes.h include/jdksavdecc_msstdint.h include/jdksavdecc_pcapfile.h include/jdksavdecc_pdu.h include/jdksavdecc_pdu_dispatch.h include/jdksavdecc_pdu_dispatch_print.h include/jdksavdecc_pdu_print.h include/jdksavdecc_print.h include/jdksavdecc_state_machine.h include/jdksavdecc_state_machines.h include/jdksavdecc_test.h include/jdksavdecc_util.h include/jdksavdecc_world.h
   DESTINATION include
)

link_directories( ${JDKSAVDECC_BINARY_DIR} )

add_executable(test_jdksavdecc_acmp_controller tests/test_jdksavdecc_acmp_controller.c)
target_link_libraries(test_jdksavdecc_acmp_controller ${LIBS})
add_test(test_jdksavdecc_acmp_controller ${CMAKE_CURRENT_BINARY_DIR}/test_jdksavdecc_acmp_controller)

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

