# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "multirob_test: 2 messages, 0 services")

set(MSG_I_FLAGS "-Imultirob_test:/home/bas/catkin_ws_multirob/src/multirob_test/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(multirob_test_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/multirob_test/msg/cmdPickup.msg" NAME_WE)
add_custom_target(_multirob_test_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "multirob_test" "/home/bas/catkin_ws_multirob/src/multirob_test/msg/cmdPickup.msg" ""
)

get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/multirob_test/msg/r2rpickupresponse.msg" NAME_WE)
add_custom_target(_multirob_test_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "multirob_test" "/home/bas/catkin_ws_multirob/src/multirob_test/msg/r2rpickupresponse.msg" "multirob_test/cmdPickup"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(multirob_test
  "/home/bas/catkin_ws_multirob/src/multirob_test/msg/cmdPickup.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multirob_test
)
_generate_msg_cpp(multirob_test
  "/home/bas/catkin_ws_multirob/src/multirob_test/msg/r2rpickupresponse.msg"
  "${MSG_I_FLAGS}"
  "/home/bas/catkin_ws_multirob/src/multirob_test/msg/cmdPickup.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multirob_test
)

### Generating Services

### Generating Module File
_generate_module_cpp(multirob_test
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multirob_test
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(multirob_test_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(multirob_test_generate_messages multirob_test_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/multirob_test/msg/cmdPickup.msg" NAME_WE)
add_dependencies(multirob_test_generate_messages_cpp _multirob_test_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/multirob_test/msg/r2rpickupresponse.msg" NAME_WE)
add_dependencies(multirob_test_generate_messages_cpp _multirob_test_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(multirob_test_gencpp)
add_dependencies(multirob_test_gencpp multirob_test_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS multirob_test_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(multirob_test
  "/home/bas/catkin_ws_multirob/src/multirob_test/msg/cmdPickup.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multirob_test
)
_generate_msg_lisp(multirob_test
  "/home/bas/catkin_ws_multirob/src/multirob_test/msg/r2rpickupresponse.msg"
  "${MSG_I_FLAGS}"
  "/home/bas/catkin_ws_multirob/src/multirob_test/msg/cmdPickup.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multirob_test
)

### Generating Services

### Generating Module File
_generate_module_lisp(multirob_test
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multirob_test
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(multirob_test_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(multirob_test_generate_messages multirob_test_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/multirob_test/msg/cmdPickup.msg" NAME_WE)
add_dependencies(multirob_test_generate_messages_lisp _multirob_test_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/multirob_test/msg/r2rpickupresponse.msg" NAME_WE)
add_dependencies(multirob_test_generate_messages_lisp _multirob_test_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(multirob_test_genlisp)
add_dependencies(multirob_test_genlisp multirob_test_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS multirob_test_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(multirob_test
  "/home/bas/catkin_ws_multirob/src/multirob_test/msg/cmdPickup.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multirob_test
)
_generate_msg_py(multirob_test
  "/home/bas/catkin_ws_multirob/src/multirob_test/msg/r2rpickupresponse.msg"
  "${MSG_I_FLAGS}"
  "/home/bas/catkin_ws_multirob/src/multirob_test/msg/cmdPickup.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multirob_test
)

### Generating Services

### Generating Module File
_generate_module_py(multirob_test
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multirob_test
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(multirob_test_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(multirob_test_generate_messages multirob_test_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/multirob_test/msg/cmdPickup.msg" NAME_WE)
add_dependencies(multirob_test_generate_messages_py _multirob_test_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/multirob_test/msg/r2rpickupresponse.msg" NAME_WE)
add_dependencies(multirob_test_generate_messages_py _multirob_test_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(multirob_test_genpy)
add_dependencies(multirob_test_genpy multirob_test_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS multirob_test_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multirob_test)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/multirob_test
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(multirob_test_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multirob_test)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/multirob_test
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(multirob_test_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multirob_test)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multirob_test\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/multirob_test
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(multirob_test_generate_messages_py std_msgs_generate_messages_py)
endif()
