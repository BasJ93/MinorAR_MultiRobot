# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "micros_swarm_framework: 1 messages, 3 services")

set(MSG_I_FLAGS "-Imicros_swarm_framework:/home/bas/catkin_ws_multirob/src/micros_swarm_framework/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg;-Inav_msgs:/opt/ros/indigo/share/nav_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/indigo/share/geometry_msgs/cmake/../msg;-Iactionlib_msgs:/opt/ros/indigo/share/actionlib_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(micros_swarm_framework_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/AppUnload.srv" NAME_WE)
add_custom_target(_micros_swarm_framework_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "micros_swarm_framework" "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/AppUnload.srv" ""
)

get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/RTPDestroy.srv" NAME_WE)
add_custom_target(_micros_swarm_framework_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "micros_swarm_framework" "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/RTPDestroy.srv" ""
)

get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/AppLoad.srv" NAME_WE)
add_custom_target(_micros_swarm_framework_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "micros_swarm_framework" "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/AppLoad.srv" ""
)

get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/msg/MSFPPacket.msg" NAME_WE)
add_custom_target(_micros_swarm_framework_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "micros_swarm_framework" "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/msg/MSFPPacket.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(micros_swarm_framework
  "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/msg/MSFPPacket.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/micros_swarm_framework
)

### Generating Services
_generate_srv_cpp(micros_swarm_framework
  "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/RTPDestroy.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/micros_swarm_framework
)
_generate_srv_cpp(micros_swarm_framework
  "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/AppLoad.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/micros_swarm_framework
)
_generate_srv_cpp(micros_swarm_framework
  "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/AppUnload.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/micros_swarm_framework
)

### Generating Module File
_generate_module_cpp(micros_swarm_framework
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/micros_swarm_framework
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(micros_swarm_framework_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(micros_swarm_framework_generate_messages micros_swarm_framework_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/AppUnload.srv" NAME_WE)
add_dependencies(micros_swarm_framework_generate_messages_cpp _micros_swarm_framework_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/RTPDestroy.srv" NAME_WE)
add_dependencies(micros_swarm_framework_generate_messages_cpp _micros_swarm_framework_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/AppLoad.srv" NAME_WE)
add_dependencies(micros_swarm_framework_generate_messages_cpp _micros_swarm_framework_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/msg/MSFPPacket.msg" NAME_WE)
add_dependencies(micros_swarm_framework_generate_messages_cpp _micros_swarm_framework_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(micros_swarm_framework_gencpp)
add_dependencies(micros_swarm_framework_gencpp micros_swarm_framework_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS micros_swarm_framework_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(micros_swarm_framework
  "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/msg/MSFPPacket.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/micros_swarm_framework
)

### Generating Services
_generate_srv_lisp(micros_swarm_framework
  "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/RTPDestroy.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/micros_swarm_framework
)
_generate_srv_lisp(micros_swarm_framework
  "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/AppLoad.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/micros_swarm_framework
)
_generate_srv_lisp(micros_swarm_framework
  "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/AppUnload.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/micros_swarm_framework
)

### Generating Module File
_generate_module_lisp(micros_swarm_framework
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/micros_swarm_framework
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(micros_swarm_framework_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(micros_swarm_framework_generate_messages micros_swarm_framework_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/AppUnload.srv" NAME_WE)
add_dependencies(micros_swarm_framework_generate_messages_lisp _micros_swarm_framework_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/RTPDestroy.srv" NAME_WE)
add_dependencies(micros_swarm_framework_generate_messages_lisp _micros_swarm_framework_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/AppLoad.srv" NAME_WE)
add_dependencies(micros_swarm_framework_generate_messages_lisp _micros_swarm_framework_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/msg/MSFPPacket.msg" NAME_WE)
add_dependencies(micros_swarm_framework_generate_messages_lisp _micros_swarm_framework_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(micros_swarm_framework_genlisp)
add_dependencies(micros_swarm_framework_genlisp micros_swarm_framework_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS micros_swarm_framework_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(micros_swarm_framework
  "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/msg/MSFPPacket.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/micros_swarm_framework
)

### Generating Services
_generate_srv_py(micros_swarm_framework
  "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/RTPDestroy.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/micros_swarm_framework
)
_generate_srv_py(micros_swarm_framework
  "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/AppLoad.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/micros_swarm_framework
)
_generate_srv_py(micros_swarm_framework
  "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/AppUnload.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/micros_swarm_framework
)

### Generating Module File
_generate_module_py(micros_swarm_framework
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/micros_swarm_framework
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(micros_swarm_framework_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(micros_swarm_framework_generate_messages micros_swarm_framework_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/AppUnload.srv" NAME_WE)
add_dependencies(micros_swarm_framework_generate_messages_py _micros_swarm_framework_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/RTPDestroy.srv" NAME_WE)
add_dependencies(micros_swarm_framework_generate_messages_py _micros_swarm_framework_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/srv/AppLoad.srv" NAME_WE)
add_dependencies(micros_swarm_framework_generate_messages_py _micros_swarm_framework_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/bas/catkin_ws_multirob/src/micros_swarm_framework/msg/MSFPPacket.msg" NAME_WE)
add_dependencies(micros_swarm_framework_generate_messages_py _micros_swarm_framework_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(micros_swarm_framework_genpy)
add_dependencies(micros_swarm_framework_genpy micros_swarm_framework_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS micros_swarm_framework_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/micros_swarm_framework)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/micros_swarm_framework
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(micros_swarm_framework_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET nav_msgs_generate_messages_cpp)
  add_dependencies(micros_swarm_framework_generate_messages_cpp nav_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(micros_swarm_framework_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/micros_swarm_framework)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/micros_swarm_framework
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(micros_swarm_framework_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET nav_msgs_generate_messages_lisp)
  add_dependencies(micros_swarm_framework_generate_messages_lisp nav_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(micros_swarm_framework_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/micros_swarm_framework)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/micros_swarm_framework\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/micros_swarm_framework
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(micros_swarm_framework_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET nav_msgs_generate_messages_py)
  add_dependencies(micros_swarm_framework_generate_messages_py nav_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(micros_swarm_framework_generate_messages_py geometry_msgs_generate_messages_py)
endif()
