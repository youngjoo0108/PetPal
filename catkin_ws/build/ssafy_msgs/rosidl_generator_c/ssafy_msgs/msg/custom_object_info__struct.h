// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ssafy_msgs:msg\CustomObjectInfo.idl
// generated code does not contain a copyright notice

#ifndef SSAFY_MSGS__MSG__CUSTOM_OBJECT_INFO__STRUCT_H_
#define SSAFY_MSGS__MSG__CUSTOM_OBJECT_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/vector3__struct.h"

// Struct defined in msg/CustomObjectInfo in the package ssafy_msgs.
typedef struct ssafy_msgs__msg__CustomObjectInfo
{
  geometry_msgs__msg__Vector3__Sequence position;
} ssafy_msgs__msg__CustomObjectInfo;

// Struct for a sequence of ssafy_msgs__msg__CustomObjectInfo.
typedef struct ssafy_msgs__msg__CustomObjectInfo__Sequence
{
  ssafy_msgs__msg__CustomObjectInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ssafy_msgs__msg__CustomObjectInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SSAFY_MSGS__MSG__CUSTOM_OBJECT_INFO__STRUCT_H_
