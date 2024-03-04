// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from ssafy_msgs:msg\ObjectInfo.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "ssafy_msgs/msg/object_info__rosidl_typesupport_introspection_c.h"
#include "ssafy_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "ssafy_msgs/msg/object_info__functions.h"
#include "ssafy_msgs/msg/object_info__struct.h"


// Include directives for member types
// Member `idx_obj`
// Member `x`
// Member `y`
#include "rosidl_generator_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void ObjectInfo__rosidl_typesupport_introspection_c__ObjectInfo_init_function(
  void * message_memory, enum rosidl_runtime_c_message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ssafy_msgs__msg__ObjectInfo__init(message_memory);
}

void ObjectInfo__rosidl_typesupport_introspection_c__ObjectInfo_fini_function(void * message_memory)
{
  ssafy_msgs__msg__ObjectInfo__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember ObjectInfo__rosidl_typesupport_introspection_c__ObjectInfo_message_member_array[4] = {
  {
    "num_obj",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs__msg__ObjectInfo, num_obj),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "idx_obj",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs__msg__ObjectInfo, idx_obj),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs__msg__ObjectInfo, x),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs__msg__ObjectInfo, y),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers ObjectInfo__rosidl_typesupport_introspection_c__ObjectInfo_message_members = {
  "ssafy_msgs__msg",  // message namespace
  "ObjectInfo",  // message name
  4,  // number of fields
  sizeof(ssafy_msgs__msg__ObjectInfo),
  ObjectInfo__rosidl_typesupport_introspection_c__ObjectInfo_message_member_array,  // message members
  ObjectInfo__rosidl_typesupport_introspection_c__ObjectInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  ObjectInfo__rosidl_typesupport_introspection_c__ObjectInfo_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t ObjectInfo__rosidl_typesupport_introspection_c__ObjectInfo_message_type_support_handle = {
  0,
  &ObjectInfo__rosidl_typesupport_introspection_c__ObjectInfo_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ssafy_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ssafy_msgs, msg, ObjectInfo)() {
  if (!ObjectInfo__rosidl_typesupport_introspection_c__ObjectInfo_message_type_support_handle.typesupport_identifier) {
    ObjectInfo__rosidl_typesupport_introspection_c__ObjectInfo_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &ObjectInfo__rosidl_typesupport_introspection_c__ObjectInfo_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
