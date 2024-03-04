// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ssafy_msgs:msg\TurtlebotStatus.idl
// generated code does not contain a copyright notice

#ifndef SSAFY_MSGS__MSG__TURTLEBOT_STATUS__STRUCT_H_
#define SSAFY_MSGS__MSG__TURTLEBOT_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'twist'
#include "geometry_msgs/msg/twist__struct.h"

// Struct defined in msg/TurtlebotStatus in the package ssafy_msgs.
typedef struct ssafy_msgs__msg__TurtlebotStatus
{
  geometry_msgs__msg__Twist twist;
  uint8_t power_supply_status;
  float battery_percentage;
  bool can_use_hand;
  bool can_put;
  bool can_lift;
} ssafy_msgs__msg__TurtlebotStatus;

// Struct for a sequence of ssafy_msgs__msg__TurtlebotStatus.
typedef struct ssafy_msgs__msg__TurtlebotStatus__Sequence
{
  ssafy_msgs__msg__TurtlebotStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ssafy_msgs__msg__TurtlebotStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SSAFY_MSGS__MSG__TURTLEBOT_STATUS__STRUCT_H_
