// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ssafy_msgs:msg\HandControl.idl
// generated code does not contain a copyright notice
#include "ssafy_msgs/msg/hand_control__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool
ssafy_msgs__msg__HandControl__init(ssafy_msgs__msg__HandControl * msg)
{
  if (!msg) {
    return false;
  }
  // control_mode
  // put_distance
  // put_height
  return true;
}

void
ssafy_msgs__msg__HandControl__fini(ssafy_msgs__msg__HandControl * msg)
{
  if (!msg) {
    return;
  }
  // control_mode
  // put_distance
  // put_height
}

ssafy_msgs__msg__HandControl *
ssafy_msgs__msg__HandControl__create()
{
  ssafy_msgs__msg__HandControl * msg = (ssafy_msgs__msg__HandControl *)malloc(sizeof(ssafy_msgs__msg__HandControl));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ssafy_msgs__msg__HandControl));
  bool success = ssafy_msgs__msg__HandControl__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
ssafy_msgs__msg__HandControl__destroy(ssafy_msgs__msg__HandControl * msg)
{
  if (msg) {
    ssafy_msgs__msg__HandControl__fini(msg);
  }
  free(msg);
}


bool
ssafy_msgs__msg__HandControl__Sequence__init(ssafy_msgs__msg__HandControl__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  ssafy_msgs__msg__HandControl * data = NULL;
  if (size) {
    data = (ssafy_msgs__msg__HandControl *)calloc(size, sizeof(ssafy_msgs__msg__HandControl));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ssafy_msgs__msg__HandControl__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ssafy_msgs__msg__HandControl__fini(&data[i - 1]);
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
ssafy_msgs__msg__HandControl__Sequence__fini(ssafy_msgs__msg__HandControl__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      ssafy_msgs__msg__HandControl__fini(&array->data[i]);
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

ssafy_msgs__msg__HandControl__Sequence *
ssafy_msgs__msg__HandControl__Sequence__create(size_t size)
{
  ssafy_msgs__msg__HandControl__Sequence * array = (ssafy_msgs__msg__HandControl__Sequence *)malloc(sizeof(ssafy_msgs__msg__HandControl__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = ssafy_msgs__msg__HandControl__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
ssafy_msgs__msg__HandControl__Sequence__destroy(ssafy_msgs__msg__HandControl__Sequence * array)
{
  if (array) {
    ssafy_msgs__msg__HandControl__Sequence__fini(array);
  }
  free(array);
}
