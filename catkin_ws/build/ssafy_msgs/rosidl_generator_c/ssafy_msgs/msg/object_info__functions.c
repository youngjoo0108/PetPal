// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ssafy_msgs:msg\ObjectInfo.idl
// generated code does not contain a copyright notice
#include "ssafy_msgs/msg/object_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `idx_obj`
// Member `x`
// Member `y`
#include "rosidl_generator_c/primitives_sequence_functions.h"

bool
ssafy_msgs__msg__ObjectInfo__init(ssafy_msgs__msg__ObjectInfo * msg)
{
  if (!msg) {
    return false;
  }
  // num_obj
  // idx_obj
  if (!rosidl_generator_c__int16__Sequence__init(&msg->idx_obj, 0)) {
    ssafy_msgs__msg__ObjectInfo__fini(msg);
    return false;
  }
  // x
  if (!rosidl_generator_c__float__Sequence__init(&msg->x, 0)) {
    ssafy_msgs__msg__ObjectInfo__fini(msg);
    return false;
  }
  // y
  if (!rosidl_generator_c__float__Sequence__init(&msg->y, 0)) {
    ssafy_msgs__msg__ObjectInfo__fini(msg);
    return false;
  }
  return true;
}

void
ssafy_msgs__msg__ObjectInfo__fini(ssafy_msgs__msg__ObjectInfo * msg)
{
  if (!msg) {
    return;
  }
  // num_obj
  // idx_obj
  rosidl_generator_c__int16__Sequence__fini(&msg->idx_obj);
  // x
  rosidl_generator_c__float__Sequence__fini(&msg->x);
  // y
  rosidl_generator_c__float__Sequence__fini(&msg->y);
}

ssafy_msgs__msg__ObjectInfo *
ssafy_msgs__msg__ObjectInfo__create()
{
  ssafy_msgs__msg__ObjectInfo * msg = (ssafy_msgs__msg__ObjectInfo *)malloc(sizeof(ssafy_msgs__msg__ObjectInfo));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ssafy_msgs__msg__ObjectInfo));
  bool success = ssafy_msgs__msg__ObjectInfo__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
ssafy_msgs__msg__ObjectInfo__destroy(ssafy_msgs__msg__ObjectInfo * msg)
{
  if (msg) {
    ssafy_msgs__msg__ObjectInfo__fini(msg);
  }
  free(msg);
}


bool
ssafy_msgs__msg__ObjectInfo__Sequence__init(ssafy_msgs__msg__ObjectInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  ssafy_msgs__msg__ObjectInfo * data = NULL;
  if (size) {
    data = (ssafy_msgs__msg__ObjectInfo *)calloc(size, sizeof(ssafy_msgs__msg__ObjectInfo));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ssafy_msgs__msg__ObjectInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ssafy_msgs__msg__ObjectInfo__fini(&data[i - 1]);
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
ssafy_msgs__msg__ObjectInfo__Sequence__fini(ssafy_msgs__msg__ObjectInfo__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      ssafy_msgs__msg__ObjectInfo__fini(&array->data[i]);
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

ssafy_msgs__msg__ObjectInfo__Sequence *
ssafy_msgs__msg__ObjectInfo__Sequence__create(size_t size)
{
  ssafy_msgs__msg__ObjectInfo__Sequence * array = (ssafy_msgs__msg__ObjectInfo__Sequence *)malloc(sizeof(ssafy_msgs__msg__ObjectInfo__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = ssafy_msgs__msg__ObjectInfo__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
ssafy_msgs__msg__ObjectInfo__Sequence__destroy(ssafy_msgs__msg__ObjectInfo__Sequence * array)
{
  if (array) {
    ssafy_msgs__msg__ObjectInfo__Sequence__fini(array);
  }
  free(array);
}
