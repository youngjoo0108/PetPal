// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ssafy_msgs:msg\HandControl.idl
// generated code does not contain a copyright notice

#ifndef SSAFY_MSGS__MSG__HAND_CONTROL__STRUCT_H_
#define SSAFY_MSGS__MSG__HAND_CONTROL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/HandControl in the package ssafy_msgs.
typedef struct ssafy_msgs__msg__HandControl
{
  uint8_t control_mode;
  float put_distance;
  float put_height;
} ssafy_msgs__msg__HandControl;

// Struct for a sequence of ssafy_msgs__msg__HandControl.
typedef struct ssafy_msgs__msg__HandControl__Sequence
{
  ssafy_msgs__msg__HandControl * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ssafy_msgs__msg__HandControl__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SSAFY_MSGS__MSG__HAND_CONTROL__STRUCT_H_
