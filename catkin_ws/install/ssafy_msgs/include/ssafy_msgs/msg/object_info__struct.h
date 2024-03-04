// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ssafy_msgs:msg\ObjectInfo.idl
// generated code does not contain a copyright notice

#ifndef SSAFY_MSGS__MSG__OBJECT_INFO__STRUCT_H_
#define SSAFY_MSGS__MSG__OBJECT_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'idx_obj'
// Member 'x'
// Member 'y'
#include "rosidl_generator_c/primitives_sequence.h"

// Struct defined in msg/ObjectInfo in the package ssafy_msgs.
typedef struct ssafy_msgs__msg__ObjectInfo
{
  int16_t num_obj;
  rosidl_generator_c__int16__Sequence idx_obj;
  rosidl_generator_c__float__Sequence x;
  rosidl_generator_c__float__Sequence y;
} ssafy_msgs__msg__ObjectInfo;

// Struct for a sequence of ssafy_msgs__msg__ObjectInfo.
typedef struct ssafy_msgs__msg__ObjectInfo__Sequence
{
  ssafy_msgs__msg__ObjectInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ssafy_msgs__msg__ObjectInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SSAFY_MSGS__MSG__OBJECT_INFO__STRUCT_H_
