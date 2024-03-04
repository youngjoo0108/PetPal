// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ssafy_msgs:msg\EnviromentStatus.idl
// generated code does not contain a copyright notice

#ifndef SSAFY_MSGS__MSG__ENVIROMENT_STATUS__STRUCT_H_
#define SSAFY_MSGS__MSG__ENVIROMENT_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'weather'
#include "rosidl_generator_c/string.h"

// Struct defined in msg/EnviromentStatus in the package ssafy_msgs.
typedef struct ssafy_msgs__msg__EnviromentStatus
{
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t temperature;
  rosidl_generator_c__String weather;
} ssafy_msgs__msg__EnviromentStatus;

// Struct for a sequence of ssafy_msgs__msg__EnviromentStatus.
typedef struct ssafy_msgs__msg__EnviromentStatus__Sequence
{
  ssafy_msgs__msg__EnviromentStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ssafy_msgs__msg__EnviromentStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SSAFY_MSGS__MSG__ENVIROMENT_STATUS__STRUCT_H_
