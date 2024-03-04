// generated from rosidl_typesupport_connext_c/resource/idl__dds_connext__type_support_c.cpp.em
// with input from ssafy_msgs:msg\CustomObjectInfo.idl
// generated code does not contain a copyright notice

#include <cassert>
#include <limits>

#include "ssafy_msgs/msg/custom_object_info__rosidl_typesupport_connext_c.h"
#include "rcutils/types/uint8_array.h"
#include "rosidl_typesupport_connext_c/identifier.h"
#include "rosidl_typesupport_connext_c/wstring_conversion.hpp"
#include "rosidl_typesupport_connext_cpp/message_type_support.h"
#include "ssafy_msgs/msg/rosidl_typesupport_connext_c__visibility_control.h"
#include "ssafy_msgs/msg/custom_object_info__struct.h"
#include "ssafy_msgs/msg/custom_object_info__functions.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif

#include "ssafy_msgs/msg/dds_connext/CustomObjectInfo_Support.h"
#include "ssafy_msgs/msg/dds_connext/CustomObjectInfo_Plugin.h"

#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions
#if defined(__cplusplus)
extern "C"
{
#endif

// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/vector3__struct.h"
// Member 'position'
#include "geometry_msgs/msg/vector3__functions.h"

// forward declare type support functions
// Member 'position'
ROSIDL_TYPESUPPORT_CONNEXT_C_IMPORT_ssafy_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_connext_c,
  geometry_msgs, msg,
  Vector3)();

static DDS_TypeCode *
_CustomObjectInfo__get_type_code()
{
  return ssafy_msgs::msg::dds_::CustomObjectInfo_TypeSupport::get_typecode();
}

static bool
_CustomObjectInfo__convert_ros_to_dds(const void * untyped_ros_message, void * untyped_dds_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  if (!untyped_dds_message) {
    fprintf(stderr, "dds message handle is null\n");
    return false;
  }
  const ssafy_msgs__msg__CustomObjectInfo * ros_message =
    static_cast<const ssafy_msgs__msg__CustomObjectInfo *>(untyped_ros_message);
  ssafy_msgs::msg::dds_::CustomObjectInfo_ * dds_message =
    static_cast<ssafy_msgs::msg::dds_::CustomObjectInfo_ *>(untyped_dds_message);
  // Member name: position
  {
    const message_type_support_callbacks_t * geometry_msgs__msg__Vector3__callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_connext_c, geometry_msgs, msg, Vector3
      )()->data);
    size_t size = ros_message->position.size;
    if (size > (std::numeric_limits<DDS_Long>::max)()) {
      fprintf(stderr, "array size exceeds maximum DDS sequence size\n");
      return false;
    }
    DDS_Long length = static_cast<DDS_Long>(size);
    if (length > dds_message->position_.maximum()) {
      if (!dds_message->position_.maximum(length)) {
        fprintf(stderr, "failed to set maximum of sequence\n");
        return false;
      }
    }
    if (!dds_message->position_.length(length)) {
      fprintf(stderr, "failed to set length of sequence\n");
      return false;
    }
    for (DDS_Long i = 0; i < static_cast<DDS_Long>(size); ++i) {
      auto & ros_i = ros_message->position.data[i];
      if (!geometry_msgs__msg__Vector3__callbacks->convert_ros_to_dds(
          &ros_i, &dds_message->position_[i]))
      {
        return false;
      }
    }
  }
  return true;
}

static bool
_CustomObjectInfo__convert_dds_to_ros(const void * untyped_dds_message, void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  if (!untyped_dds_message) {
    fprintf(stderr, "dds message handle is null\n");
    return false;
  }
  const ssafy_msgs::msg::dds_::CustomObjectInfo_ * dds_message =
    static_cast<const ssafy_msgs::msg::dds_::CustomObjectInfo_ *>(untyped_dds_message);
  ssafy_msgs__msg__CustomObjectInfo * ros_message =
    static_cast<ssafy_msgs__msg__CustomObjectInfo *>(untyped_ros_message);
  // Member name: position
  {
    DDS_Long size = dds_message->position_.length();
    if (ros_message->position.data) {
      geometry_msgs__msg__Vector3__Sequence__fini(&ros_message->position);
    }
    if (!geometry_msgs__msg__Vector3__Sequence__init(&ros_message->position, size)) {
      return "failed to create array for field 'position'";
    }
    for (DDS_Long i = 0; i < size; i++) {
      auto & ros_i = ros_message->position.data[i];
      const rosidl_message_type_support_t * ts =
        ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_connext_c,
        geometry_msgs, msg,
        Vector3)();
      const message_type_support_callbacks_t * callbacks =
        static_cast<const message_type_support_callbacks_t *>(ts->data);
      callbacks->convert_dds_to_ros(&dds_message->position_[i], &ros_i);
    }
  }
  return true;
}


static bool
_CustomObjectInfo__to_cdr_stream(
  const void * untyped_ros_message,
  rcutils_uint8_array_t * cdr_stream)
{
  if (!untyped_ros_message) {
    return false;
  }
  if (!cdr_stream) {
    return false;
  }
  const ssafy_msgs__msg__CustomObjectInfo * ros_message =
    static_cast<const ssafy_msgs__msg__CustomObjectInfo *>(untyped_ros_message);
  ssafy_msgs::msg::dds_::CustomObjectInfo_ dds_message;
  if (!_CustomObjectInfo__convert_ros_to_dds(ros_message, &dds_message)) {
    return false;
  }

  // call the serialize function for the first time to get the expected length of the message
  unsigned int expected_length;
  if (ssafy_msgs::msg::dds_::CustomObjectInfo_Plugin_serialize_to_cdr_buffer(
      NULL, &expected_length, &dds_message) != RTI_TRUE)
  {
    fprintf(stderr, "failed to call ssafy_msgs::msg::dds_::CustomObjectInfo_Plugin_serialize_to_cdr_buffer()\n");
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
  if (ssafy_msgs::msg::dds_::CustomObjectInfo_Plugin_serialize_to_cdr_buffer(
      reinterpret_cast<char *>(cdr_stream->buffer),
      &buffer_length_uint,
      &dds_message) != RTI_TRUE)
  {
    return false;
  }

  return true;
}

static bool
_CustomObjectInfo__to_message(
  const rcutils_uint8_array_t * cdr_stream,
  void * untyped_ros_message)
{
  if (!cdr_stream) {
    return false;
  }
  if (!untyped_ros_message) {
    return false;
  }

  ssafy_msgs::msg::dds_::CustomObjectInfo_ * dds_message =
    ssafy_msgs::msg::dds_::CustomObjectInfo_TypeSupport::create_data();
  if (cdr_stream->buffer_length > (std::numeric_limits<unsigned int>::max)()) {
    fprintf(stderr, "cdr_stream->buffer_length, unexpectedly larger than max unsigned int\n");
    return false;
  }
  if (ssafy_msgs::msg::dds_::CustomObjectInfo_Plugin_deserialize_from_cdr_buffer(
      dds_message,
      reinterpret_cast<char *>(cdr_stream->buffer),
      static_cast<unsigned int>(cdr_stream->buffer_length)) != RTI_TRUE)
  {
    fprintf(stderr, "deserialize from cdr buffer failed\n");
    return false;
  }
  bool success = _CustomObjectInfo__convert_dds_to_ros(dds_message, untyped_ros_message);
  if (ssafy_msgs::msg::dds_::CustomObjectInfo_TypeSupport::delete_data(dds_message) != DDS_RETCODE_OK) {
    return false;
  }
  return success;
}

static message_type_support_callbacks_t _CustomObjectInfo__callbacks = {
  "ssafy_msgs::msg",  // message_namespace
  "CustomObjectInfo",  // message_name
  _CustomObjectInfo__get_type_code,  // get_type_code
  _CustomObjectInfo__convert_ros_to_dds,  // convert_ros_to_dds
  _CustomObjectInfo__convert_dds_to_ros,  // convert_dds_to_ros
  _CustomObjectInfo__to_cdr_stream,  // to_cdr_stream
  _CustomObjectInfo__to_message  // to_message
};

static rosidl_message_type_support_t _CustomObjectInfo__type_support = {
  rosidl_typesupport_connext_c__identifier,
  &_CustomObjectInfo__callbacks,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_connext_c,
  ssafy_msgs, msg,
  CustomObjectInfo)()
{
  return &_CustomObjectInfo__type_support;
}

#if defined(__cplusplus)
}
#endif
