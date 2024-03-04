// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from ssafy_msgs:msg\EnviromentStatus.idl
// generated code does not contain a copyright notice
#include "ssafy_msgs/msg/enviroment_status__rosidl_typesupport_fastrtps_cpp.hpp"
#include "ssafy_msgs/msg/enviroment_status__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace ssafy_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ssafy_msgs
cdr_serialize(
  const ssafy_msgs::msg::EnviromentStatus & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: month
  cdr << ros_message.month;
  // Member: day
  cdr << ros_message.day;
  // Member: hour
  cdr << ros_message.hour;
  // Member: minute
  cdr << ros_message.minute;
  // Member: temperature
  cdr << ros_message.temperature;
  // Member: weather
  cdr << ros_message.weather;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ssafy_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  ssafy_msgs::msg::EnviromentStatus & ros_message)
{
  // Member: month
  cdr >> ros_message.month;

  // Member: day
  cdr >> ros_message.day;

  // Member: hour
  cdr >> ros_message.hour;

  // Member: minute
  cdr >> ros_message.minute;

  // Member: temperature
  cdr >> ros_message.temperature;

  // Member: weather
  cdr >> ros_message.weather;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ssafy_msgs
get_serialized_size(
  const ssafy_msgs::msg::EnviromentStatus & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: month
  {
    size_t item_size = sizeof(ros_message.month);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: day
  {
    size_t item_size = sizeof(ros_message.day);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: hour
  {
    size_t item_size = sizeof(ros_message.hour);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: minute
  {
    size_t item_size = sizeof(ros_message.minute);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: temperature
  {
    size_t item_size = sizeof(ros_message.temperature);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: weather
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.weather.size() + 1);

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ssafy_msgs
max_serialized_size_EnviromentStatus(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: month
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: day
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: hour
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: minute
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: temperature
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: weather
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

static bool _EnviromentStatus__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const ssafy_msgs::msg::EnviromentStatus *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _EnviromentStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<ssafy_msgs::msg::EnviromentStatus *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _EnviromentStatus__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const ssafy_msgs::msg::EnviromentStatus *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _EnviromentStatus__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_EnviromentStatus(full_bounded, 0);
}

static message_type_support_callbacks_t _EnviromentStatus__callbacks = {
  "ssafy_msgs::msg",
  "EnviromentStatus",
  _EnviromentStatus__cdr_serialize,
  _EnviromentStatus__cdr_deserialize,
  _EnviromentStatus__get_serialized_size,
  _EnviromentStatus__max_serialized_size
};

static rosidl_message_type_support_t _EnviromentStatus__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_EnviromentStatus__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace ssafy_msgs

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_ssafy_msgs
const rosidl_message_type_support_t *
get_message_type_support_handle<ssafy_msgs::msg::EnviromentStatus>()
{
  return &ssafy_msgs::msg::typesupport_fastrtps_cpp::_EnviromentStatus__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, ssafy_msgs, msg, EnviromentStatus)() {
  return &ssafy_msgs::msg::typesupport_fastrtps_cpp::_EnviromentStatus__handle;
}

#ifdef __cplusplus
}
#endif
