// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ssafy_msgs:msg\TurtlebotStatus.idl
// generated code does not contain a copyright notice
#include "ssafy_msgs/msg/turtlebot_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `twist`
#include "geometry_msgs/msg/twist__functions.h"

bool
ssafy_msgs__msg__TurtlebotStatus__init(ssafy_msgs__msg__TurtlebotStatus * msg)
{
  if (!msg) {
    return false;
  }
  // twist
  if (!geometry_msgs__msg__Twist__init(&msg->twist)) {
    ssafy_msgs__msg__TurtlebotStatus__fini(msg);
    return false;
  }
  // power_supply_status
  // battery_percentage
  // can_use_hand
  // can_put
  // can_lift
  return true;
}

void
ssafy_msgs__msg__TurtlebotStatus__fini(ssafy_msgs__msg__TurtlebotStatus * msg)
{
  if (!msg) {
    return;
  }
  // twist
  geometry_msgs__msg__Twist__fini(&msg->twist);
  // power_supply_status
  // battery_percentage
  // can_use_hand
  // can_put
  // can_lift
}

ssafy_msgs__msg__TurtlebotStatus *
ssafy_msgs__msg__TurtlebotStatus__create()
{
  ssafy_msgs__msg__TurtlebotStatus * msg = (ssafy_msgs__msg__TurtlebotStatus *)malloc(sizeof(ssafy_msgs__msg__TurtlebotStatus));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ssafy_msgs__msg__TurtlebotStatus));
  bool success = ssafy_msgs__msg__TurtlebotStatus__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
ssafy_msgs__msg__TurtlebotStatus__destroy(ssafy_msgs__msg__TurtlebotStatus * msg)
{
  if (msg) {
    ssafy_msgs__msg__TurtlebotStatus__fini(msg);
  }
  free(msg);
}


bool
ssafy_msgs__msg__TurtlebotStatus__Sequence__init(ssafy_msgs__msg__TurtlebotStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  ssafy_msgs__msg__TurtlebotStatus * data = NULL;
  if (size) {
    data = (ssafy_msgs__msg__TurtlebotStatus *)calloc(size, sizeof(ssafy_msgs__msg__TurtlebotStatus));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ssafy_msgs__msg__TurtlebotStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ssafy_msgs__msg__TurtlebotStatus__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
ssafy_msgs__msg__TurtlebotStatus__Sequence__fini(ssafy_msgs__msg__TurtlebotStatus__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      ssafy_msgs__msg__TurtlebotStatus__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

ssafy_msgs__msg__TurtlebotStatus__Sequence *
ssafy_msgs__msg__TurtlebotStatus__Sequence__create(size_t size)
{
  ssafy_msgs__msg__TurtlebotStatus__Sequence * array = (ssafy_msgs__msg__TurtlebotStatus__Sequence *)malloc(sizeof(ssafy_msgs__msg__TurtlebotStatus__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = ssafy_msgs__msg__TurtlebotStatus__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
ssafy_msgs__msg__TurtlebotStatus__Sequence__destroy(ssafy_msgs__msg__TurtlebotStatus__Sequence * array)
{
  if (array) {
    ssafy_msgs__msg__TurtlebotStatus__Sequence__fini(array);
  }
  free(array);
}
