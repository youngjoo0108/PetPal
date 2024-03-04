// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ssafy_msgs:msg\BBox.idl
// generated code does not contain a copyright notice
#include "ssafy_msgs/msg/b_box__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `idx_bbox`
// Member `x`
// Member `y`
// Member `w`
// Member `h`
#include "rosidl_generator_c/primitives_sequence_functions.h"

bool
ssafy_msgs__msg__BBox__init(ssafy_msgs__msg__BBox * msg)
{
  if (!msg) {
    return false;
  }
  // num_bbox
  // idx_bbox
  if (!rosidl_generator_c__int16__Sequence__init(&msg->idx_bbox, 0)) {
    ssafy_msgs__msg__BBox__fini(msg);
    return false;
  }
  // x
  if (!rosidl_generator_c__int16__Sequence__init(&msg->x, 0)) {
    ssafy_msgs__msg__BBox__fini(msg);
    return false;
  }
  // y
  if (!rosidl_generator_c__int16__Sequence__init(&msg->y, 0)) {
    ssafy_msgs__msg__BBox__fini(msg);
    return false;
  }
  // w
  if (!rosidl_generator_c__int16__Sequence__init(&msg->w, 0)) {
    ssafy_msgs__msg__BBox__fini(msg);
    return false;
  }
  // h
  if (!rosidl_generator_c__int16__Sequence__init(&msg->h, 0)) {
    ssafy_msgs__msg__BBox__fini(msg);
    return false;
  }
  return true;
}

void
ssafy_msgs__msg__BBox__fini(ssafy_msgs__msg__BBox * msg)
{
  if (!msg) {
    return;
  }
  // num_bbox
  // idx_bbox
  rosidl_generator_c__int16__Sequence__fini(&msg->idx_bbox);
  // x
  rosidl_generator_c__int16__Sequence__fini(&msg->x);
  // y
  rosidl_generator_c__int16__Sequence__fini(&msg->y);
  // w
  rosidl_generator_c__int16__Sequence__fini(&msg->w);
  // h
  rosidl_generator_c__int16__Sequence__fini(&msg->h);
}

ssafy_msgs__msg__BBox *
ssafy_msgs__msg__BBox__create()
{
  ssafy_msgs__msg__BBox * msg = (ssafy_msgs__msg__BBox *)malloc(sizeof(ssafy_msgs__msg__BBox));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ssafy_msgs__msg__BBox));
  bool success = ssafy_msgs__msg__BBox__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
ssafy_msgs__msg__BBox__destroy(ssafy_msgs__msg__BBox * msg)
{
  if (msg) {
    ssafy_msgs__msg__BBox__fini(msg);
  }
  free(msg);
}


bool
ssafy_msgs__msg__BBox__Sequence__init(ssafy_msgs__msg__BBox__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  ssafy_msgs__msg__BBox * data = NULL;
  if (size) {
    data = (ssafy_msgs__msg__BBox *)calloc(size, sizeof(ssafy_msgs__msg__BBox));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ssafy_msgs__msg__BBox__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ssafy_msgs__msg__BBox__fini(&data[i - 1]);
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
ssafy_msgs__msg__BBox__Sequence__fini(ssafy_msgs__msg__BBox__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      ssafy_msgs__msg__BBox__fini(&array->data[i]);
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

ssafy_msgs__msg__BBox__Sequence *
ssafy_msgs__msg__BBox__Sequence__create(size_t size)
{
  ssafy_msgs__msg__BBox__Sequence * array = (ssafy_msgs__msg__BBox__Sequence *)malloc(sizeof(ssafy_msgs__msg__BBox__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = ssafy_msgs__msg__BBox__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
ssafy_msgs__msg__BBox__Sequence__destroy(ssafy_msgs__msg__BBox__Sequence * array)
{
  if (array) {
    ssafy_msgs__msg__BBox__Sequence__fini(array);
  }
  free(array);
}
