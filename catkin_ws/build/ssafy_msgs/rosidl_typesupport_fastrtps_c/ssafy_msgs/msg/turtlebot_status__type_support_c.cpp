// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from ssafy_msgs:msg\TurtlebotStatus.idl
// generated code does not contain a copyright notice
#include "ssafy_msgs/msg/turtlebot_status__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "ssafy_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "ssafy_msgs/msg/turtlebot_status__struct.h"
#include "ssafy_msgs/msg/turtlebot_status__functions.h"
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

#include "geometry_msgs/msg/twist__functions.h"  // twist

// forward declare type support functions
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_ssafy_msgs
size_t get_serialized_size_geometry_msgs__msg__Twist(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_ssafy_msgs
size_t max_serialized_size_geometry_msgs__msg__Twist(
  bool & full_bounded,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_ssafy_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, geometry_msgs, msg, Twist)();


using _TurtlebotStatus__ros_msg_type = ssafy_msgs__msg__TurtlebotStatus;

static bool _TurtlebotStatus__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _TurtlebotStatus__ros_msg_type * ros_message = static_cast<const _TurtlebotStatus__ros_msg_type *>(untyped_ros_message);
  // Field name: twist
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, geometry_msgs, msg, Twist
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->twist, cdr))
    {
      return false;
    }
  }

  // Field name: power_supply_status
  {
    cdr << ros_message->power_supply_status;
  }

  // Field name: battery_percentage
  {
    cdr << ros_message->battery_percentage;
  }

  // Field name: can_use_hand
  {
    cdr << (ros_message->can_use_hand ? true : false);
  }

  // Field name: can_put
  {
    cdr << (ros_message->can_put ? true : false);
  }

  // Field name: can_lift
  {
    cdr << (ros_message->can_lift ? true : false);
  }

  return true;
}

static bool _TurtlebotStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _TurtlebotStatus__ros_msg_type * ros_message = static_cast<_TurtlebotStatus__ros_msg_type *>(untyped_ros_message);
  // Field name: twist
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, geometry_msgs, msg, Twist
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->twist))
    {
      return false;
    }
  }

  // Field name: power_supply_status
  {
    cdr >> ros_message->power_supply_status;
  }

  // Field name: battery_percentage
  {
    cdr >> ros_message->battery_percentage;
  }

  // Field name: can_use_hand
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->can_use_hand = tmp ? true : false;
  }

  // Field name: can_put
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->can_put = tmp ? true : false;
  }

  // Field name: can_lift
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->can_lift = tmp ? true : false;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ssafy_msgs
size_t get_serialized_size_ssafy_msgs__msg__TurtlebotStatus(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _TurtlebotStatus__ros_msg_type * ros_message = static_cast<const _TurtlebotStatus__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name twist

  current_alignment += get_serialized_size_geometry_msgs__msg__Twist(
    &(ros_message->twist), current_alignment);
  // field.name power_supply_status
  {
    size_t item_size = sizeof(ros_message->power_supply_status);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name battery_percentage
  {
    size_t item_size = sizeof(ros_message->battery_percentage);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name can_use_hand
  {
    size_t item_size = sizeof(ros_message->can_use_hand);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name can_put
  {
    size_t item_size = sizeof(ros_message->can_put);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name can_lift
  {
    size_t item_size = sizeof(ros_message->can_lift);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _TurtlebotStatus__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_ssafy_msgs__msg__TurtlebotStatus(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ssafy_msgs
size_t max_serialized_size_ssafy_msgs__msg__TurtlebotStatus(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: twist
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_geometry_msgs__msg__Twist(
        full_bounded, current_alignment);
    }
  }
  // member: power_supply_status
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: battery_percentage
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: can_use_hand
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: can_put
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: can_lift
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static size_t _TurtlebotStatus__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_ssafy_msgs__msg__TurtlebotStatus(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_TurtlebotStatus = {
  "ssafy_msgs::msg",
  "TurtlebotStatus",
  _TurtlebotStatus__cdr_serialize,
  _TurtlebotStatus__cdr_deserialize,
  _TurtlebotStatus__get_serialized_size,
  _TurtlebotStatus__max_serialized_size
};

static rosidl_message_type_support_t _TurtlebotStatus__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_TurtlebotStatus,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, ssafy_msgs, msg, TurtlebotStatus)() {
  return &_TurtlebotStatus__type_support;
}

#if defined(__cplusplus)
}
#endif
