// generated from rosidl_typesupport_connext_c/resource/idl__dds_connext__type_support_c.cpp.em
// with input from ssafy_msgs:msg\Num.idl
// generated code does not contain a copyright notice

#include <cassert>
#include <limits>

#include "ssafy_msgs/msg/num__rosidl_typesupport_connext_c.h"
#include "rcutils/types/uint8_array.h"
#include "rosidl_typesupport_connext_c/identifier.h"
#include "rosidl_typesupport_connext_c/wstring_conversion.hpp"
#include "rosidl_typesupport_connext_cpp/message_type_support.h"
#include "ssafy_msgs/msg/rosidl_typesupport_connext_c__visibility_control.h"
#include "ssafy_msgs/msg/num__struct.h"
#include "ssafy_msgs/msg/num__functions.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif

#include "ssafy_msgs/msg/dds_connext/Num_Support.h"
#include "ssafy_msgs/msg/dds_connext/Num_Plugin.h"

#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions
#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions

static DDS_TypeCode *
_Num__get_type_code()
{
  return ssafy_msgs::msg::dds_::Num_TypeSupport::get_typecode();
}

static bool
_Num__convert_ros_to_dds(const void * untyped_ros_message, void * untyped_dds_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  if (!untyped_dds_message) {
    fprintf(stderr, "dds message handle is null\n");
    return false;
  }
  const ssafy_msgs__msg__Num * ros_message =
    static_cast<const ssafy_msgs__msg__Num *>(untyped_ros_message);
  ssafy_msgs::msg::dds_::Num_ * dds_message =
    static_cast<ssafy_msgs::msg::dds_::Num_ *>(untyped_dds_message);
  // Member name: num
  {
    dds_message->num_ = ros_message->num;
  }
  // Member name: air
  {
    dds_message->air_ = ros_message->air;
  }
  // Member name: door
  {
    dds_message->door_ = ros_message->door;
  }
  return true;
}

static bool
_Num__convert_dds_to_ros(const void * untyped_dds_message, void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  if (!untyped_dds_message) {
    fprintf(stderr, "dds message handle is null\n");
    return false;
  }
  const ssafy_msgs::msg::dds_::Num_ * dds_message =
    static_cast<const ssafy_msgs::msg::dds_::Num_ *>(untyped_dds_message);
  ssafy_msgs__msg__Num * ros_message =
    static_cast<ssafy_msgs__msg__Num *>(untyped_ros_message);
  // Member name: num
  {
    ros_message->num = dds_message->num_;
  }
  // Member name: air
  {
    ros_message->air = dds_message->air_ == static_cast<DDS_Boolean>(true);
  }
  // Member name: door
  {
    ros_message->door = dds_message->door_ == static_cast<DDS_Boolean>(true);
  }
  return true;
}


static bool
_Num__to_cdr_stream(
  const void * untyped_ros_message,
  rcutils_uint8_array_t * cdr_stream)
{
  if (!untyped_ros_message) {
    return false;
  }
  if (!cdr_stream) {
    return false;
  }
  const ssafy_msgs__msg__Num * ros_message =
    static_cast<const ssafy_msgs__msg__Num *>(untyped_ros_message);
  ssafy_msgs::msg::dds_::Num_ dds_message;
  if (!_Num__convert_ros_to_dds(ros_message, &dds_message)) {
    return false;
  }

  // call the serialize function for the first time to get the expected length of the message
  unsigned int expected_length;
  if (ssafy_msgs::msg::dds_::Num_Plugin_serialize_to_cdr_buffer(
      NULL, &expected_length, &dds_message) != RTI_TRUE)
  {
    fprintf(stderr, "failed to call ssafy_msgs::msg::dds_::Num_Plugin_serialize_to_cdr_buffer()\n");
    return false;
  }
  cdr_stream->buffer_length = expected_length;
  if (cdr_stream->buffer_length > (std::numeric_limits<unsigned int>::max)()) {
    fprintf(stderr, "cdr_stream->buffer_length, unexpectedly larger than max unsigned int\n");
    return false;
  }
  if (cdr_stream->buffer_capacity < cdr_stream->buffer_length) {
    cdr_stream->allocator.deallocate(cdr_stream->buffer, cdr_stream->allocator.state);
    cdr_stream->buffer = static_cast<uint8_t *>(cdr_stream->allocator.allocate(cdr_stream->buffer_length, cdr_stream->allocator.state));
  }
  // call the function again and fill the buffer this time
  unsigned int buffer_length_uint = static_cast<unsigned int>(cdr_stream->buffer_length);
  if (ssafy_msgs::msg::dds_::Num_Plugin_serialize_to_cdr_buffer(
      reinterpret_cast<char *>(cdr_stream->buffer),
      &buffer_length_uint,
      &dds_message) != RTI_TRUE)
  {
    return false;
  }

  return true;
}

static bool
_Num__to_message(
  const rcutils_uint8_array_t * cdr_stream,
  void * untyped_ros_message)
{
  if (!cdr_stream) {
    return false;
  }
  if (!untyped_ros_message) {
    return false;
  }

  ssafy_msgs::msg::dds_::Num_ * dds_message =
    ssafy_msgs::msg::dds_::Num_TypeSupport::create_data();
  if (cdr_stream->buffer_length > (std::numeric_limits<unsigned int>::max)()) {
    fprintf(stderr, "cdr_stream->buffer_length, unexpectedly larger than max unsigned int\n");
    return false;
  }
  if (ssafy_msgs::msg::dds_::Num_Plugin_deserialize_from_cdr_buffer(
      dds_message,
      reinterpret_cast<char *>(cdr_stream->buffer),
      static_cast<unsigned int>(cdr_stream->buffer_length)) != RTI_TRUE)
  {
    fprintf(stderr, "deserialize from cdr buffer failed\n");
    return false;
  }
  bool success = _Num__convert_dds_to_ros(dds_message, untyped_ros_message);
  if (ssafy_msgs::msg::dds_::Num_TypeSupport::delete_data(dds_message) != DDS_RETCODE_OK) {
    return false;
  }
  return success;
}

static message_type_support_callbacks_t _Num__callbacks = {
  "ssafy_msgs::msg",  // message_namespace
  "Num",  // message_name
  _Num__get_type_code,  // get_type_code
  _Num__convert_ros_to_dds,  // convert_ros_to_dds
  _Num__convert_dds_to_ros,  // convert_dds_to_ros
  _Num__to_cdr_stream,  // to_cdr_stream
  _Num__to_message  // to_message
};

static rosidl_message_type_support_t _Num__type_support = {
  rosidl_typesupport_connext_c__identifier,
  &_Num__callbacks,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_connext_c,
  ssafy_msgs, msg,
  Num)()
{
  return &_Num__type_support;
}

#if defined(__cplusplus)
}
#endif
