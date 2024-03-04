// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ssafy_msgs:msg\EnviromentStatus.idl
// generated code does not contain a copyright notice
#include "ssafy_msgs/msg/enviroment_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `weather`
#include "rosidl_generator_c/string_functions.h"

bool
ssafy_msgs__msg__EnviromentStatus__init(ssafy_msgs__msg__EnviromentStatus * msg)
{
  if (!msg) {
    return false;
  }
  // month
  // day
  // hour
  // minute
  // temperature
  // weather
  if (!rosidl_generator_c__String__init(&msg->weather)) {
    ssafy_msgs__msg__EnviromentStatus__fini(msg);
    return false;
  }
  return true;
}

void
ssafy_msgs__msg__EnviromentStatus__fini(ssafy_msgs__msg__EnviromentStatus * msg)
{
  if (!msg) {
    return;
  }
  // month
  // day
  // hour
  // minute
  // temperature
  // weather
  rosidl_generator_c__String__fini(&msg->weather);
}

ssafy_msgs__msg__EnviromentStatus *
ssafy_msgs__msg__EnviromentStatus__create()
{
  ssafy_msgs__msg__EnviromentStatus * msg = (ssafy_msgs__msg__EnviromentStatus *)malloc(sizeof(ssafy_msgs__msg__EnviromentStatus));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ssafy_msgs__msg__EnviromentStatus));
  bool success = ssafy_msgs__msg__EnviromentStatus__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
ssafy_msgs__msg__EnviromentStatus__destroy(ssafy_msgs__msg__EnviromentStatus * msg)
{
  if (msg) {
    ssafy_msgs__msg__EnviromentStatus__fini(msg);
  }
  free(msg);
}


bool
ssafy_msgs__msg__EnviromentStatus__Sequence__init(ssafy_msgs__msg__EnviromentStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  ssafy_msgs__msg__EnviromentStatus * data = NULL;
  if (size) {
    data = (ssafy_msgs__msg__EnviromentStatus *)calloc(size, sizeof(ssafy_msgs__msg__EnviromentStatus));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ssafy_msgs__msg__EnviromentStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ssafy_msgs__msg__EnviromentStatus__fini(&data[i - 1]);
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
ssafy_msgs__msg__EnviromentStatus__Sequence__fini(ssafy_msgs__msg__EnviromentStatus__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      ssafy_msgs__msg__EnviromentStatus__fini(&array->data[i]);
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

ssafy_msgs__msg__EnviromentStatus__Sequence *
ssafy_msgs__msg__EnviromentStatus__Sequence__create(size_t size)
{
  ssafy_msgs__msg__EnviromentStatus__Sequence * array = (ssafy_msgs__msg__EnviromentStatus__Sequence *)malloc(sizeof(ssafy_msgs__msg__EnviromentStatus__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = ssafy_msgs__msg__EnviromentStatus__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
ssafy_msgs__msg__EnviromentStatus__Sequence__destroy(ssafy_msgs__msg__EnviromentStatus__Sequence * array)
{
  if (array) {
    ssafy_msgs__msg__EnviromentStatus__Sequence__fini(array);
  }
  free(array);
}
