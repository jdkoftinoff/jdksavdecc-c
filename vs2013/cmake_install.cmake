# Install script for directory: C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/jdksavdecc-c")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/vs2013/Debug/jdksavdecc-c.lib")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/vs2013/Release/jdksavdecc-c.lib")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/vs2013/MinSizeRel/jdksavdecc-c.lib")
  ELSEIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/vs2013/RelWithDebInfo/jdksavdecc-c.lib")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_acmp.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_acmp_print.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_adp.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_adp_manager.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_adp_print.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_aecp.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_aecp_aa.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_aecp_aem.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_aecp_avc.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_aecp_hdcp_apm.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_aecp_print.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_aecp_vendor.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_aem_command.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_aem_descriptor.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_aem_print.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_allocator.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_app.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_app_print.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_avr.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_control.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_controller_manager.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_descriptor_storage.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_descriptor_storage_gen.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_entity_manager.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_entity_model.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_frame.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_inflight.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_jdks.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_maap.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_maap_print.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_ms.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_msinttypes.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_msstdint.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_pdu.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_pdu_print.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_print.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_util.h"
    "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/include/jdksavdecc_world.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/vs2013/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "C:/Users/Jeff Koftinoff/Source/Repos/jdksavdecc-c/vs2013/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
