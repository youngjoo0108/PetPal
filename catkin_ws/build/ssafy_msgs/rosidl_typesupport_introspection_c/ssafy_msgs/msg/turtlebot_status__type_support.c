// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from ssafy_msgs:msg\TurtlebotStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "ssafy_msgs/msg/turtlebot_status__rosidl_typesupport_introspection_c.h"
#include "ssafy_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "ssafy_msgs/msg/turtlebot_status__functions.h"
#include "ssafy_msgs/msg/turtlebot_status__struct.h"


// Include directives for member types
// Member `twist`
#include "geometry_msgs/msg/twist.h"
// Member `twist`
#include "geometry_msgs/msg/twist__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void TurtlebotStatus__rosidl_typesupport_introspection_c__TurtlebotStatus_init_function(
  void * message_memory, enum rosidl_runtime_c_message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ssafy_msgs__msg__TurtlebotStatus__init(message_memory);
}

void TurtlebotStatus__rosidl_typesupport_introspection_c__TurtlebotStatus_fini_function(void * message_memory)
{
  ssafy_msgs__msg__TurtlebotStatus__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember TurtlebotStatus__rosidl_typesupport_introspection_c__TurtlebotStatus_message_member_array[6] = {
  {
    "twist",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs__msg__TurtlebotStatus, twist),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "power_supply_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs__msg__TurtlebotStatus, power_supply_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "battery_percentage",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs__msg__TurtlebotStatus, battery_percentage),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "can_use_hand",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs__msg__TurtlebotStatus, can_use_hand),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "can_put",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs__msg__TurtlebotStatus, can_put),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "can_lift",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs__msg__TurtlebotStatus, can_lift),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers TurtlebotStatus__rosidl_typesupport_introspection_c__TurtlebotStatus_message_members = {
  "ssafy_msgs__msg",  // message namespace
  "TurtlebotStatus",  // message name
  6,  // number of fields
  sizeof(ssafy_msgs__msg__TurtlebotStatus),
  TurtlebotStatus__rosidl_typesupport_introspection_c__TurtlebotStatus_message_member_array,  // message members
  TurtlebotStatus__rosidl_typesupport_introspection_c__TurtlebotStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  TurtlebotStatus__rosidl_typesupport_introspection_c__TurtlebotStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t TurtlebotStatus__rosidl_typesupport_introspection_c__TurtlebotStatus_message_type_support_handle = {
  0,
  &TurtlebotStatus__rosidl_typesupport_introspection_c__TurtlebotStatus_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ssafy_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ssafy_msgs, msg, TurtlebotStatus)() {
  TurtlebotStatus__rosidl_typesupport_introspection_c__TurtlebotStatus_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Twist)();
  if (!TurtlebotStatus__rosidl_typesupport_introspection_c__TurtlebotStatus_message_type_support_handle.typesupport_identifier) {
    TurtlebotStatus__rosidl_typesupport_introspection_c__TurtlebotStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &TurtlebotStatus__rosidl_typesupport_introspection_c__TurtlebotStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
