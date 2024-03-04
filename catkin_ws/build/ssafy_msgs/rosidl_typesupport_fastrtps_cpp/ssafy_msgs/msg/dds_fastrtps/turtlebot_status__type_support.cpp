// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from ssafy_msgs:msg\TurtlebotStatus.idl
// generated code does not contain a copyright notice
#include "ssafy_msgs/msg/turtlebot_status__rosidl_typesupport_fastrtps_cpp.hpp"
#include "ssafy_msgs/msg/turtlebot_status__struct.hpp"

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
namespace geometry_msgs
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const geometry_msgs::msg::Twist &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  geometry_msgs::msg::Twist &);
size_t get_serialized_size(
  const geometry_msgs::msg::Twist &,
  size_t current_alignment);
size_t
max_serialized_size_Twist(
  bool & full_bounded,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace geometry_msgs


namespace ssafy_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ssafy_msgs
cdr_serialize(
  const ssafy_msgs::msg::TurtlebotStatus & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: twist
  geometry_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.twist,
    cdr);
  // Member: power_supply_status
  cdr << ros_message.power_supply_status;
  // Member: battery_percentage
  cdr << ros_message.battery_percentage;
  // Member: can_use_hand
  cdr << (ros_message.can_use_hand ? true : false);
  // Member: can_put
  cdr << (ros_message.can_put ? true : false);
  // Member: can_lift
  cdr << (ros_message.can_lift ? true : false);
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ssafy_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  ssafy_msgs::msg::TurtlebotStatus & ros_message)
{
  // Member: twist
  geometry_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.twist);

  // Member: power_supply_status
  cdr >> ros_message.power_supply_status;

  // Member: battery_percentage
  cdr >> ros_message.battery_percentage;

  // Member: can_use_hand
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.can_use_hand = tmp ? true : false;
  }

  // Member: can_put
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.can_put = tmp ? true : false;
  }

  // Member: can_lift
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.can_lift = tmp ? true : false;
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ssafy_msgs
get_serialized_size(
  const ssafy_msgs::msg::TurtlebotStatus & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: twist

  current_alignment +=
    geometry_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.twist, current_alignment);
  // Member: power_supply_status
  {
    size_t item_size = sizeof(ros_message.power_supply_status);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: battery_percentage
  {
    size_t item_size = sizeof(ros_message.battery_percentage);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: can_use_hand
  {
    size_t item_size = sizeof(ros_message.can_use_hand);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: can_put
  {
    size_t item_size = sizeof(ros_message.can_put);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: can_lift
  {
    size_t item_size = sizeof(ros_message.can_lift);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ssafy_msgs
max_serialized_size_TurtlebotStatus(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: twist
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        geometry_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_Twist(
        full_bounded, current_alignment);
    }
  }

  // Member: power_supply_status
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: battery_percentage
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: can_use_hand
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: can_put
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: can_lift
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static bool _TurtlebotStatus__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const ssafy_msgs::msg::TurtlebotStatus *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _TurtlebotStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<ssafy_msgs::msg::TurtlebotStatus *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _TurtlebotStatus__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const ssafy_msgs::msg::TurtlebotStatus *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _TurtlebotStatus__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_TurtlebotStatus(full_bounded, 0);
}

static message_type_support_callbacks_t _TurtlebotStatus__callbacks = {
  "ssafy_msgs::msg",
  "TurtlebotStatus",
  _TurtlebotStatus__cdr_serialize,
  _TurtlebotStatus__cdr_deserialize,
  _TurtlebotStatus__get_serialized_size,
  _TurtlebotStatus__max_serialized_size
};

static rosidl_message_type_support_t _TurtlebotStatus__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_TurtlebotStatus__callbacks,
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
get_message_type_support_handle<ssafy_msgs::msg::TurtlebotStatus>()
{
  return &ssafy_msgs::msg::typesupport_fastrtps_cpp::_TurtlebotStatus__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, ssafy_msgs, msg, TurtlebotStatus)() {
  return &ssafy_msgs::msg::typesupport_fastrtps_cpp::_TurtlebotStatus__handle;
}

#ifdef __cplusplus
}
#endif
