// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from ssafy_msgs:msg\BBox.idl
// generated code does not contain a copyright notice
#include "ssafy_msgs/msg/b_box__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "ssafy_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "ssafy_msgs/msg/b_box__struct.h"
#include "ssafy_msgs/msg/b_box__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_generator_c/primitives_sequence.h"  // h, idx_bbox, w, x, y
#include "rosidl_generator_c/primitives_sequence_functions.h"  // h, idx_bbox, w, x, y

// forward declare type support functions


using _BBox__ros_msg_type = ssafy_msgs__msg__BBox;

static bool _BBox__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _BBox__ros_msg_type * ros_message = static_cast<const _BBox__ros_msg_type *>(untyped_ros_message);
  // Field name: num_bbox
  {
    cdr << ros_message->num_bbox;
  }

  // Field name: idx_bbox
  {
    size_t size = ros_message->idx_bbox.size;
    auto array_ptr = ros_message->idx_bbox.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: x
  {
    size_t size = ros_message->x.size;
    auto array_ptr = ros_message->x.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: y
  {
    size_t size = ros_message->y.size;
    auto array_ptr = ros_message->y.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: w
  {
    size_t size = ros_message->w.size;
    auto array_ptr = ros_message->w.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: h
  {
    size_t size = ros_message->h.size;
    auto array_ptr = ros_message->h.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  return true;
}

static bool _BBox__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _BBox__ros_msg_type * ros_message = static_cast<_BBox__ros_msg_type *>(untyped_ros_message);
  // Field name: num_bbox
  {
    cdr >> ros_message->num_bbox;
  }

  // Field name: idx_bbox
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->idx_bbox.data) {
      rosidl_generator_c__int16__Sequence__fini(&ros_message->idx_bbox);
    }
    if (!rosidl_generator_c__int16__Sequence__init(&ros_message->idx_bbox, size)) {
      return "failed to create array for field 'idx_bbox'";
    }
    auto array_ptr = ros_message->idx_bbox.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: x
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->x.data) {
      rosidl_generator_c__int16__Sequence__fini(&ros_message->x);
    }
    if (!rosidl_generator_c__int16__Sequence__init(&ros_message->x, size)) {
      return "failed to create array for field 'x'";
    }
    auto array_ptr = ros_message->x.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: y
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->y.data) {
      rosidl_generator_c__int16__Sequence__fini(&ros_message->y);
    }
    if (!rosidl_generator_c__int16__Sequence__init(&ros_message->y, size)) {
      return "failed to create array for field 'y'";
    }
    auto array_ptr = ros_message->y.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: w
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->w.data) {
      rosidl_generator_c__int16__Sequence__fini(&ros_message->w);
    }
    if (!rosidl_generator_c__int16__Sequence__init(&ros_message->w, size)) {
      return "failed to create array for field 'w'";
    }
    auto array_ptr = ros_message->w.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: h
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->h.data) {
      rosidl_generator_c__int16__Sequence__fini(&ros_message->h);
    }
    if (!rosidl_generator_c__int16__Sequence__init(&ros_message->h, size)) {
      return "failed to create array for field 'h'";
    }
    auto array_ptr = ros_message->h.data;
    cdr.deserializeArray(array_ptr, size);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ssafy_msgs
size_t get_serialized_size_ssafy_msgs__msg__BBox(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _BBox__ros_msg_type * ros_message = static_cast<const _BBox__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name num_bbox
  {
    size_t item_size = sizeof(ros_message->num_bbox);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name idx_bbox
  {
    size_t array_size = ros_message->idx_bbox.size;
    auto array_ptr = ros_message->idx_bbox.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name x
  {
    size_t array_size = ros_message->x.size;
    auto array_ptr = ros_message->x.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name y
  {
    size_t array_size = ros_message->y.size;
    auto array_ptr = ros_message->y.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name w
  {
    size_t array_size = ros_message->w.size;
    auto array_ptr = ros_message->w.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name h
  {
    size_t array_size = ros_message->h.size;
    auto array_ptr = ros_message->h.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _BBox__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_ssafy_msgs__msg__BBox(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ssafy_msgs
size_t max_serialized_size_ssafy_msgs__msg__BBox(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: num_bbox
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: idx_bbox
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: x
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: y
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: w
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: h
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  return current_alignment - initial_alignment;
}

static size_t _BBox__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_ssafy_msgs__msg__BBox(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_BBox = {
  "ssafy_msgs::msg",
  "BBox",
  _BBox__cdr_serialize,
  _BBox__cdr_deserialize,
  _BBox__get_serialized_size,
  _BBox__max_serialized_size
};

static rosidl_message_type_support_t _BBox__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_BBox,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, ssafy_msgs, msg, BBox)() {
  return &_BBox__type_support;
}

#if defined(__cplusplus)
}
#endif
