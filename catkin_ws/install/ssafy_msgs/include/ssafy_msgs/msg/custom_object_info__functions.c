// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ssafy_msgs:msg\CustomObjectInfo.idl
// generated code does not contain a copyright notice
#include "ssafy_msgs/msg/custom_object_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `position`
#include "geometry_msgs/msg/vector3__functions.h"

bool
ssafy_msgs__msg__CustomObjectInfo__init(ssafy_msgs__msg__CustomObjectInfo * msg)
{
  if (!msg) {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Vector3__Sequence__init(&msg->position, 0)) {
    ssafy_msgs__msg__CustomObjectInfo__fini(msg);
    return false;
  }
  return true;
}

void
ssafy_msgs__msg__CustomObjectInfo__fini(ssafy_msgs__msg__CustomObjectInfo * msg)
{
  if (!msg) {
    return;
  }
  // position
  geometry_msgs__msg__Vector3__Sequence__fini(&msg->position);
}

ssafy_msgs__msg__CustomObjectInfo *
ssafy_msgs__msg__CustomObjectInfo__create()
{
  ssafy_msgs__msg__CustomObjectInfo * msg = (ssafy_msgs__msg__CustomObjectInfo *)malloc(sizeof(ssafy_msgs__msg__CustomObjectInfo));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ssafy_msgs__msg__CustomObjectInfo));
  bool success = ssafy_msgs__msg__CustomObjectInfo__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
ssafy_msgs__msg__CustomObjectInfo__destroy(ssafy_msgs__msg__CustomObjectInfo * msg)
{
  if (msg) {
    ssafy_msgs__msg__CustomObjectInfo__fini(msg);
  }
  free(msg);
}


bool
ssafy_msgs__msg__CustomObjectInfo__Sequence__init(ssafy_msgs__msg__CustomObjectInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  ssafy_msgs__msg__CustomObjectInfo * data = NULL;
  if (size) {
    data = (ssafy_msgs__msg__CustomObjectInfo *)calloc(size, sizeof(ssafy_msgs__msg__CustomObjectInfo));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ssafy_msgs__msg__CustomObjectInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ssafy_msgs__msg__CustomObjectInfo__fini(&data[i - 1]);
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
ssafy_msgs__msg__CustomObjectInfo__Sequence__fini(ssafy_msgs__msg__CustomObjectInfo__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      ssafy_msgs__msg__CustomObjectInfo__fini(&array->data[i]);
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

ssafy_msgs__msg__CustomObjectInfo__Sequence *
ssafy_msgs__msg__CustomObjectInfo__Sequence__create(size_t size)
{
  ssafy_msgs__msg__CustomObjectInfo__Sequence * array = (ssafy_msgs__msg__CustomObjectInfo__Sequence *)malloc(sizeof(ssafy_msgs__msg__CustomObjectInfo__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = ssafy_msgs__msg__CustomObjectInfo__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
ssafy_msgs__msg__CustomObjectInfo__Sequence__destroy(ssafy_msgs__msg__CustomObjectInfo__Sequence * array)
{
  if (array) {
    ssafy_msgs__msg__CustomObjectInfo__Sequence__fini(array);
  }
  free(array);
}
