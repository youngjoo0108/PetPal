// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from ssafy_msgs:msg\EnviromentStatus.idl
// generated code does not contain a copyright notice
#include "ssafy_msgs/msg/enviroment_status__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "ssafy_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "ssafy_msgs/msg/enviroment_status__struct.h"
#include "ssafy_msgs/msg/enviroment_status__functions.h"
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

#include "rosidl_generator_c/string.h"  // weather
#include "rosidl_generator_c/string_functions.h"  // weather

// forward declare type support functions


using _EnviromentStatus__ros_msg_type = ssafy_msgs__msg__EnviromentStatus;

static bool _EnviromentStatus__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _EnviromentStatus__ros_msg_type * ros_message = static_cast<const _EnviromentStatus__ros_msg_type *>(untyped_ros_message);
  // Field name: month
  {
    cdr << ros_message->month;
  }

  // Field name: day
  {
    cdr << ros_message->day;
  }

  // Field name: hour
  {
    cdr << ros_message->hour;
  }

  // Field name: minute
  {
    cdr << ros_message->minute;
  }

  // Field name: temperature
  {
    cdr << ros_message->temperature;
  }

  // Field name: weather
  {
    const rosidl_generator_c__String * str = &ros_message->weather;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  return true;
}

static bool _EnviromentStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _EnviromentStatus__ros_msg_type * ros_message = static_cast<_EnviromentStatus__ros_msg_type *>(untyped_ros_message);
  // Field name: month
  {
    cdr >> ros_message->month;
  }

  // Field name: day
  {
    cdr >> ros_message->day;
  }

  // Field name: hour
  {
    cdr >> ros_message->hour;
  }

  // Field name: minute
  {
    cdr >> ros_message->minute;
  }

  // Field name: temperature
  {
    cdr >> ros_message->temperature;
  }

  // Field name: weather
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->weather.data) {
      rosidl_generator_c__String__init(&ros_message->weather);
    }
    bool succeeded = rosidl_generator_c__String__assign(
      &ros_message->weather,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'weather'\n");
      return false;
    }
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ssafy_msgs
size_t get_serialized_size_ssafy_msgs__msg__EnviromentStatus(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _EnviromentStatus__ros_msg_type * ros_message = static_cast<const _EnviromentStatus__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name month
  {
    size_t item_size = sizeof(ros_message->month);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name day
  {
    size_t item_size = sizeof(ros_message->day);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name hour
  {
    size_t item_size = sizeof(ros_message->hour);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name minute
  {
    size_t item_size = sizeof(ros_message->minute);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name temperature
  {
    size_t item_size = sizeof(ros_message->temperature);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name weather
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->weather.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _EnviromentStatus__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_ssafy_msgs__msg__EnviromentStatus(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ssafy_msgs
size_t max_serialized_size_ssafy_msgs__msg__EnviromentStatus(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: month
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: day
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: hour
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: minute
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: temperature
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: weather
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  return current_alignment - initial_alignment;
}

static size_t _EnviromentStatus__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_ssafy_msgs__msg__EnviromentStatus(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_EnviromentStatus = {
  "ssafy_msgs::msg",
  "EnviromentStatus",
  _EnviromentStatus__cdr_serialize,
  _EnviromentStatus__cdr_deserialize,
  _EnviromentStatus__get_serialized_size,
  _EnviromentStatus__max_serialized_size
};

static rosidl_message_type_support_t _EnviromentStatus__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_EnviromentStatus,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, ssafy_msgs, msg, EnviromentStatus)() {
  return &_EnviromentStatus__type_support;
}

#if defined(__cplusplus)
}
#endif
