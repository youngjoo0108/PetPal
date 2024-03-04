// generated from rosidl_typesupport_connext_c/resource/idl__dds_connext__type_support_c.cpp.em
// with input from ssafy_msgs:msg\BBox.idl
// generated code does not contain a copyright notice

#include <cassert>
#include <limits>

#include "ssafy_msgs/msg/b_box__rosidl_typesupport_connext_c.h"
#include "rcutils/types/uint8_array.h"
#include "rosidl_typesupport_connext_c/identifier.h"
#include "rosidl_typesupport_connext_c/wstring_conversion.hpp"
#include "rosidl_typesupport_connext_cpp/message_type_support.h"
#include "ssafy_msgs/msg/rosidl_typesupport_connext_c__visibility_control.h"
#include "ssafy_msgs/msg/b_box__struct.h"
#include "ssafy_msgs/msg/b_box__functions.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif

#include "ssafy_msgs/msg/dds_connext/BBox_Support.h"
#include "ssafy_msgs/msg/dds_connext/BBox_Plugin.h"

#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions
#if defined(__cplusplus)
extern "C"
{
#endif

// Include directives for member types
// Member 'idx_bbox'
// Member 'x'
// Member 'y'
// Member 'w'
// Member 'h'
#include "rosidl_generator_c/primitives_sequence.h"
// Member 'idx_bbox'
// Member 'x'
// Member 'y'
// Member 'w'
// Member 'h'
#include "rosidl_generator_c/primitives_sequence_functions.h"

// forward declare type support functions

static DDS_TypeCode *
_BBox__get_type_code()
{
  return ssafy_msgs::msg::dds_::BBox_TypeSupport::get_typecode();
}

static bool
_BBox__convert_ros_to_dds(const void * untyped_ros_message, void * untyped_dds_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  if (!untyped_dds_message) {
    fprintf(stderr, "dds message handle is null\n");
    return false;
  }
  const ssafy_msgs__msg__BBox * ros_message =
    static_cast<const ssafy_msgs__msg__BBox *>(untyped_ros_message);
  ssafy_msgs::msg::dds_::BBox_ * dds_message =
    static_cast<ssafy_msgs::msg::dds_::BBox_ *>(untyped_dds_message);
  // Member name: num_bbox
  {
    dds_message->num_bbox_ = ros_message->num_bbox;
  }
  // Member name: idx_bbox
  {
    size_t size = ros_message->idx_bbox.size;
    if (size > (std::numeric_limits<DDS_Long>::max)()) {
      fprintf(stderr, "array size exceeds maximum DDS sequence size\n");
      return false;
    }
    DDS_Long length = static_cast<DDS_Long>(size);
    if (length > dds_message->idx_bbox_.maximum()) {
      if (!dds_message->idx_bbox_.maximum(length)) {
        fprintf(stderr, "failed to set maximum of sequence\n");
        return false;
      }
    }
    if (!dds_message->idx_bbox_.length(length)) {
      fprintf(stderr, "failed to set length of sequence\n");
      return false;
    }
    for (DDS_Long i = 0; i < static_cast<DDS_Long>(size); ++i) {
      auto & ros_i = ros_message->idx_bbox.data[i];
      dds_message->idx_bbox_[i] = ros_i;
    }
  }
  // Member name: x
  {
    size_t size = ros_message->x.size;
    if (size > (std::numeric_limits<DDS_Long>::max)()) {
      fprintf(stderr, "array size exceeds maximum DDS sequence size\n");
      return false;
    }
    DDS_Long length = static_cast<DDS_Long>(size);
    if (length > dds_message->x_.maximum()) {
      if (!dds_message->x_.maximum(length)) {
        fprintf(stderr, "failed to set maximum of sequence\n");
        return false;
      }
    }
    if (!dds_message->x_.length(length)) {
      fprintf(stderr, "failed to set length of sequence\n");
      return false;
    }
    for (DDS_Long i = 0; i < static_cast<DDS_Long>(size); ++i) {
      auto & ros_i = ros_message->x.data[i];
      dds_message->x_[i] = ros_i;
    }
  }
  // Member name: y
  {
    size_t size = ros_message->y.size;
    if (size > (std::numeric_limits<DDS_Long>::max)()) {
      fprintf(stderr, "array size exceeds maximum DDS sequence size\n");
      return false;
    }
    DDS_Long length = static_cast<DDS_Long>(size);
    if (length > dds_message->y_.maximum()) {
      if (!dds_message->y_.maximum(length)) {
        fprintf(stderr, "failed to set maximum of sequence\n");
        return false;
      }
    }
    if (!dds_message->y_.length(length)) {
      fprintf(stderr, "failed to set length of sequence\n");
      return false;
    }
    for (DDS_Long i = 0; i < static_cast<DDS_Long>(size); ++i) {
      auto & ros_i = ros_message->y.data[i];
      dds_message->y_[i] = ros_i;
    }
  }
  // Member name: w
  {
    size_t size = ros_message->w.size;
    if (size > (std::numeric_limits<DDS_Long>::max)()) {
      fprintf(stderr, "array size exceeds maximum DDS sequence size\n");
      return false;
    }
    DDS_Long length = static_cast<DDS_Long>(size);
    if (length > dds_message->w_.maximum()) {
      if (!dds_message->w_.maximum(length)) {
        fprintf(stderr, "failed to set maximum of sequence\n");
        return false;
      }
    }
    if (!dds_message->w_.length(length)) {
      fprintf(stderr, "failed to set length of sequence\n");
      return false;
    }
    for (DDS_Long i = 0; i < static_cast<DDS_Long>(size); ++i) {
      auto & ros_i = ros_message->w.data[i];
      dds_message->w_[i] = ros_i;
    }
  }
  // Member name: h
  {
    size_t size = ros_message->h.size;
    if (size > (std::numeric_limits<DDS_Long>::max)()) {
      fprintf(stderr, "array size exceeds maximum DDS sequence size\n");
      return false;
    }
    DDS_Long length = static_cast<DDS_Long>(size);
    if (length > dds_message->h_.maximum()) {
      if (!dds_message->h_.maximum(length)) {
        fprintf(stderr, "failed to set maximum of sequence\n");
        return false;
      }
    }
    if (!dds_message->h_.length(length)) {
      fprintf(stderr, "failed to set length of sequence\n");
      return false;
    }
    for (DDS_Long i = 0; i < static_cast<DDS_Long>(size); ++i) {
      auto & ros_i = ros_message->h.data[i];
      dds_message->h_[i] = ros_i;
    }
  }
  return true;
}

static bool
_BBox__convert_dds_to_ros(const void * untyped_dds_message, void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  if (!untyped_dds_message) {
    fprintf(stderr, "dds message handle is null\n");
    return false;
  }
  const ssafy_msgs::msg::dds_::BBox_ * dds_message =
    static_cast<const ssafy_msgs::msg::dds_::BBox_ *>(untyped_dds_message);
  ssafy_msgs__msg__BBox * ros_message =
    static_cast<ssafy_msgs__msg__BBox *>(untyped_ros_message);
  // Member name: num_bbox
  {
    ros_message->num_bbox = dds_message->num_bbox_;
  }
  // Member name: idx_bbox
  {
    DDS_Long size = dds_message->idx_bbox_.length();
    if (ros_message->idx_bbox.data) {
      rosidl_generator_c__int16__Sequence__fini(&ros_message->idx_bbox);
    }
    if (!rosidl_generator_c__int16__Sequence__init(&ros_message->idx_bbox, size)) {
      return "failed to create array for field 'idx_bbox'";
    }
    for (DDS_Long i = 0; i < size; i++) {
      auto & ros_i = ros_message->idx_bbox.data[i];
      ros_i = dds_message->idx_bbox_[i];
    }
  }
  // Member name: x
  {
    DDS_Long size = dds_message->x_.length();
    if (ros_message->x.data) {
      rosidl_generator_c__int16__Sequence__fini(&ros_message->x);
    }
    if (!rosidl_generator_c__int16__Sequence__init(&ros_message->x, size)) {
      return "failed to create array for field 'x'";
    }
    for (DDS_Long i = 0; i < size; i++) {
      auto & ros_i = ros_message->x.data[i];
      ros_i = dds_message->x_[i];
    }
  }
  // Member name: y
  {
    DDS_Long size = dds_message->y_.length();
    if (ros_message->y.data) {
      rosidl_generator_c__int16__Sequence__fini(&ros_message->y);
    }
    if (!rosidl_generator_c__int16__Sequence__init(&ros_message->y, size)) {
      return "failed to create array for field 'y'";
    }
    for (DDS_Long i = 0; i < size; i++) {
      auto & ros_i = ros_message->y.data[i];
      ros_i = dds_message->y_[i];
    }
  }
  // Member name: w
  {
    DDS_Long size = dds_message->w_.length();
    if (ros_message->w.data) {
      rosidl_generator_c__int16__Sequence__fini(&ros_message->w);
    }
    if (!rosidl_generator_c__int16__Sequence__init(&ros_message->w, size)) {
      return "failed to create array for field 'w'";
    }
    for (DDS_Long i = 0; i < size; i++) {
      auto & ros_i = ros_message->w.data[i];
      ros_i = dds_message->w_[i];
    }
  }
  // Member name: h
  {
    DDS_Long size = dds_message->h_.length();
    if (ros_message->h.data) {
      rosidl_generator_c__int16__Sequence__fini(&ros_message->h);
    }
    if (!rosidl_generator_c__int16__Sequence__init(&ros_message->h, size)) {
      return "failed to create array for field 'h'";
    }
    for (DDS_Long i = 0; i < size; i++) {
      auto & ros_i = ros_message->h.data[i];
      ros_i = dds_message->h_[i];
    }
  }
  return true;
}


static bool
_BBox__to_cdr_stream(
  const void * untyped_ros_message,
  rcutils_uint8_array_t * cdr_stream)
{
  if (!untyped_ros_message) {
    return false;
  }
  if (!cdr_stream) {
    return false;
  }
  const ssafy_msgs__msg__BBox * ros_message =
    static_cast<const ssafy_msgs__msg__BBox *>(untyped_ros_message);
  ssafy_msgs::msg::dds_::BBox_ dds_message;
  if (!_BBox__convert_ros_to_dds(ros_message, &dds_message)) {
    return false;
  }

  // call the serialize function for the first time to get the expected length of the message
  unsigned int expected_length;
  if (ssafy_msgs::msg::dds_::BBox_Plugin_serialize_to_cdr_buffer(
      NULL, &expected_length, &dds_message) != RTI_TRUE)
  {
    fprintf(stderr, "failed to call ssafy_msgs::msg::dds_::BBox_Plugin_serialize_to_cdr_buffer()\n");
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
  if (ssafy_msgs::msg::dds_::BBox_Plugin_serialize_to_cdr_buffer(
      reinterpret_cast<char *>(cdr_stream->buffer),
      &buffer_length_uint,
      &dds_message) != RTI_TRUE)
  {
    return false;
  }

  return true;
}

static bool
_BBox__to_message(
  const rcutils_uint8_array_t * cdr_stream,
  void * untyped_ros_message)
{
  if (!cdr_stream) {
    return false;
  }
  if (!untyped_ros_message) {
    return false;
  }

  ssafy_msgs::msg::dds_::BBox_ * dds_message =
    ssafy_msgs::msg::dds_::BBox_TypeSupport::create_data();
  if (cdr_stream->buffer_length > (std::numeric_limits<unsigned int>::max)()) {
    fprintf(stderr, "cdr_stream->buffer_length, unexpectedly larger than max unsigned int\n");
    return false;
  }
  if (ssafy_msgs::msg::dds_::BBox_Plugin_deserialize_from_cdr_buffer(
      dds_message,
      reinterpret_cast<char *>(cdr_stream->buffer),
      static_cast<unsigned int>(cdr_stream->buffer_length)) != RTI_TRUE)
  {
    fprintf(stderr, "deserialize from cdr buffer failed\n");
    return false;
  }
  bool success = _BBox__convert_dds_to_ros(dds_message, untyped_ros_message);
  if (ssafy_msgs::msg::dds_::BBox_TypeSupport::delete_data(dds_message) != DDS_RETCODE_OK) {
    return false;
  }
  return success;
}

static message_type_support_callbacks_t _BBox__callbacks = {
  "ssafy_msgs::msg",  // message_namespace
  "BBox",  // message_name
  _BBox__get_type_code,  // get_type_code
  _BBox__convert_ros_to_dds,  // convert_ros_to_dds
  _BBox__convert_dds_to_ros,  // convert_dds_to_ros
  _BBox__to_cdr_stream,  // to_cdr_stream
  _BBox__to_message  // to_message
};

static rosidl_message_type_support_t _BBox__type_support = {
  rosidl_typesupport_connext_c__identifier,
  &_BBox__callbacks,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_connext_c,
  ssafy_msgs, msg,
  BBox)()
{
  return &_BBox__type_support;
}

#if defined(__cplusplus)
}
#endif
