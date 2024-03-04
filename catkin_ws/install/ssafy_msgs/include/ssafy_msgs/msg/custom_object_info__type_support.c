// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from ssafy_msgs:msg\CustomObjectInfo.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "ssafy_msgs/msg/custom_object_info__rosidl_typesupport_introspection_c.h"
#include "ssafy_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "ssafy_msgs/msg/custom_object_info__functions.h"
#include "ssafy_msgs/msg/custom_object_info__struct.h"


// Include directives for member types
// Member `position`
#include "geometry_msgs/msg/vector3.h"
// Member `position`
#include "geometry_msgs/msg/vector3__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void CustomObjectInfo__rosidl_typesupport_introspection_c__CustomObjectInfo_init_function(
  void * message_memory, enum rosidl_runtime_c_message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ssafy_msgs__msg__CustomObjectInfo__init(message_memory);
}

void CustomObjectInfo__rosidl_typesupport_introspection_c__CustomObjectInfo_fini_function(void * message_memory)
{
  ssafy_msgs__msg__CustomObjectInfo__fini(message_memory);
}

size_t CustomObjectInfo__rosidl_typesupport_introspection_c__size_function__Vector3__position(
  const void * untyped_member)
{
  const geometry_msgs__msg__Vector3__Sequence * member =
    (const geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  return member->size;
}

const void * CustomObjectInfo__rosidl_typesupport_introspection_c__get_const_function__Vector3__position(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Vector3__Sequence * member =
    (const geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  return &member->data[index];
}

void * CustomObjectInfo__rosidl_typesupport_introspection_c__get_function__Vector3__position(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Vector3__Sequence * member =
    (geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  return &member->data[index];
}

bool CustomObjectInfo__rosidl_typesupport_introspection_c__resize_function__Vector3__position(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__Vector3__Sequence * member =
    (geometry_msgs__msg__Vector3__Sequence *)(untyped_member);
  geometry_msgs__msg__Vector3__Sequence__fini(member);
  return geometry_msgs__msg__Vector3__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember CustomObjectInfo__rosidl_typesupport_introspection_c__CustomObjectInfo_message_member_array[1] = {
  {
    "position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs__msg__CustomObjectInfo, position),  // bytes offset in struct
    NULL,  // default value
    CustomObjectInfo__rosidl_typesupport_introspection_c__size_function__Vector3__position,  // size() function pointer
    CustomObjectInfo__rosidl_typesupport_introspection_c__get_const_function__Vector3__position,  // get_const(index) function pointer
    CustomObjectInfo__rosidl_typesupport_introspection_c__get_function__Vector3__position,  // get(index) function pointer
    CustomObjectInfo__rosidl_typesupport_introspection_c__resize_function__Vector3__position  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers CustomObjectInfo__rosidl_typesupport_introspection_c__CustomObjectInfo_message_members = {
  "ssafy_msgs__msg",  // message namespace
  "CustomObjectInfo",  // message name
  1,  // number of fields
  sizeof(ssafy_msgs__msg__CustomObjectInfo),
  CustomObjectInfo__rosidl_typesupport_introspection_c__CustomObjectInfo_message_member_array,  // message members
  CustomObjectInfo__rosidl_typesupport_introspection_c__CustomObjectInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  CustomObjectInfo__rosidl_typesupport_introspection_c__CustomObjectInfo_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t CustomObjectInfo__rosidl_typesupport_introspection_c__CustomObjectInfo_message_type_support_handle = {
  0,
  &CustomObjectInfo__rosidl_typesupport_introspection_c__CustomObjectInfo_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ssafy_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ssafy_msgs, msg, CustomObjectInfo)() {
  CustomObjectInfo__rosidl_typesupport_introspection_c__CustomObjectInfo_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Vector3)();
  if (!CustomObjectInfo__rosidl_typesupport_introspection_c__CustomObjectInfo_message_type_support_handle.typesupport_identifier) {
    CustomObjectInfo__rosidl_typesupport_introspection_c__CustomObjectInfo_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &CustomObjectInfo__rosidl_typesupport_introspection_c__CustomObjectInfo_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
