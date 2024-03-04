// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ssafy_msgs:msg\BBox.idl
// generated code does not contain a copyright notice

#ifndef SSAFY_MSGS__MSG__B_BOX__STRUCT_H_
#define SSAFY_MSGS__MSG__B_BOX__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'idx_bbox'
// Member 'x'
// Member 'y'
// Member 'w'
// Member 'h'
#include "rosidl_generator_c/primitives_sequence.h"

// Struct defined in msg/BBox in the package ssafy_msgs.
typedef struct ssafy_msgs__msg__BBox
{
  int16_t num_bbox;
  rosidl_generator_c__int16__Sequence idx_bbox;
  rosidl_generator_c__int16__Sequence x;
  rosidl_generator_c__int16__Sequence y;
  rosidl_generator_c__int16__Sequence w;
  rosidl_generator_c__int16__Sequence h;
} ssafy_msgs__msg__BBox;

// Struct for a sequence of ssafy_msgs__msg__BBox.
typedef struct ssafy_msgs__msg__BBox__Sequence
{
  ssafy_msgs__msg__BBox * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ssafy_msgs__msg__BBox__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SSAFY_MSGS__MSG__B_BOX__STRUCT_H_
