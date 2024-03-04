// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from ssafy_msgs:msg\BBox.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "ssafy_msgs/msg/b_box__rosidl_typesupport_introspection_c.h"
#include "ssafy_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "ssafy_msgs/msg/b_box__functions.h"
#include "ssafy_msgs/msg/b_box__struct.h"


// Include directives for member types
// Member `idx_bbox`
// Member `x`
// Member `y`
// Member `w`
// Member `h`
#include "rosidl_generator_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void BBox__rosidl_typesupport_introspection_c__BBox_init_function(
  void * message_memory, enum rosidl_runtime_c_message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ssafy_msgs__msg__BBox__init(message_memory);
}

void BBox__rosidl_typesupport_introspection_c__BBox_fini_function(void * message_memory)
{
  ssafy_msgs__msg__BBox__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember BBox__rosidl_typesupport_introspection_c__BBox_message_member_array[6] = {
  {
    "num_bbox",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs__msg__BBox, num_bbox),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "idx_bbox",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs__msg__BBox, idx_bbox),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs__msg__BBox, x),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs__msg__BBox, y),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "w",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs__msg__BBox, w),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "h",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs__msg__BBox, h),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers BBox__rosidl_typesupport_introspection_c__BBox_message_members = {
  "ssafy_msgs__msg",  // message namespace
  "BBox",  // message name
  6,  // number of fields
  sizeof(ssafy_msgs__msg__BBox),
  BBox__rosidl_typesupport_introspection_c__BBox_message_member_array,  // message members
  BBox__rosidl_typesupport_introspection_c__BBox_init_function,  // function to initialize message memory (memory has to be allocated)
  BBox__rosidl_typesupport_introspection_c__BBox_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t BBox__rosidl_typesupport_introspection_c__BBox_message_type_support_handle = {
  0,
  &BBox__rosidl_typesupport_introspection_c__BBox_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ssafy_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ssafy_msgs, msg, BBox)() {
  if (!BBox__rosidl_typesupport_introspection_c__BBox_message_type_support_handle.typesupport_identifier) {
    BBox__rosidl_typesupport_introspection_c__BBox_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &BBox__rosidl_typesupport_introspection_c__BBox_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
