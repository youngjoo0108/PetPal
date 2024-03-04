// generated from rosidl_typesupport_connext_cpp/resource/idl__dds_connext__type_support.cpp.em
// with input from ssafy_msgs:msg\BBox.idl
// generated code does not contain a copyright notice

#include <limits>
#include <stdexcept>

#include "ssafy_msgs/msg/b_box__rosidl_typesupport_connext_cpp.hpp"
#include "rcutils/types/uint8_array.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_connext_cpp/identifier.hpp"
#include "rosidl_typesupport_connext_cpp/message_type_support.h"
#include "rosidl_typesupport_connext_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_connext_cpp/wstring_conversion.hpp"

// forward declaration of message dependencies and their conversion functions


namespace ssafy_msgs
{

namespace msg
{

namespace typesupport_connext_cpp
{


DDS_TypeCode *
get_type_code__BBox()
{
  return ssafy_msgs::msg::dds_::BBox_TypeSupport::get_typecode();
}

bool
convert_ros_message_to_dds(
  const ssafy_msgs::msg::BBox & ros_message,
  ssafy_msgs::msg::dds_::BBox_ & dds_message)
{
  // member.name num_bbox
  dds_message.num_bbox_ =
    ros_message.num_bbox;

  // member.name idx_bbox
  {
    size_t size = ros_message.idx_bbox.size();
    if (size > (std::numeric_limits<DDS_Long>::max)()) {
      throw std::runtime_error("array size exceeds maximum DDS sequence size");
    }
    DDS_Long length = static_cast<DDS_Long>(size);
    if (length > dds_message.idx_bbox_.maximum()) {
      if (!dds_message.idx_bbox_.maximum(length)) {
        throw std::runtime_error("failed to set maximum of sequence");
      }
    }
    if (!dds_message.idx_bbox_.length(length)) {
      throw std::runtime_error("failed to set length of sequence");
    }
    for (size_t i = 0; i < size; i++) {
      dds_message.idx_bbox_[static_cast<DDS_Long>(i)] =
        ros_message.idx_bbox[i];
    }
  }

  // member.name x
  {
    size_t size = ros_message.x.size();
    if (size > (std::numeric_limits<DDS_Long>::max)()) {
      throw std::runtime_error("array size exceeds maximum DDS sequence size");
    }
    DDS_Long length = static_cast<DDS_Long>(size);
    if (length > dds_message.x_.maximum()) {
      if (!dds_message.x_.maximum(length)) {
        throw std::runtime_error("failed to set maximum of sequence");
      }
    }
    if (!dds_message.x_.length(length)) {
      throw std::runtime_error("failed to set length of sequence");
    }
    for (size_t i = 0; i < size; i++) {
      dds_message.x_[static_cast<DDS_Long>(i)] =
        ros_message.x[i];
    }
  }

  // member.name y
  {
    size_t size = ros_message.y.size();
    if (size > (std::numeric_limits<DDS_Long>::max)()) {
      throw std::runtime_error("array size exceeds maximum DDS sequence size");
    }
    DDS_Long length = static_cast<DDS_Long>(size);
    if (length > dds_message.y_.maximum()) {
      if (!dds_message.y_.maximum(length)) {
        throw std::runtime_error("failed to set maximum of sequence");
      }
    }
    if (!dds_message.y_.length(length)) {
      throw std::runtime_error("failed to set length of sequence");
    }
    for (size_t i = 0; i < size; i++) {
      dds_message.y_[static_cast<DDS_Long>(i)] =
        ros_message.y[i];
    }
  }

  // member.name w
  {
    size_t size = ros_message.w.size();
    if (size > (std::numeric_limits<DDS_Long>::max)()) {
      throw std::runtime_error("array size exceeds maximum DDS sequence size");
    }
    DDS_Long length = static_cast<DDS_Long>(size);
    if (length > dds_message.w_.maximum()) {
      if (!dds_message.w_.maximum(length)) {
        throw std::runtime_error("failed to set maximum of sequence");
      }
    }
    if (!dds_message.w_.length(length)) {
      throw std::runtime_error("failed to set length of sequence");
    }
    for (size_t i = 0; i < size; i++) {
      dds_message.w_[static_cast<DDS_Long>(i)] =
        ros_message.w[i];
    }
  }

  // member.name h
  {
    size_t size = ros_message.h.size();
    if (size > (std::numeric_limits<DDS_Long>::max)()) {
      throw std::runtime_error("array size exceeds maximum DDS sequence size");
    }
    DDS_Long length = static_cast<DDS_Long>(size);
    if (length > dds_message.h_.maximum()) {
      if (!dds_message.h_.maximum(length)) {
        throw std::runtime_error("failed to set maximum of sequence");
      }
    }
    if (!dds_message.h_.length(length)) {
      throw std::runtime_error("failed to set length of sequence");
    }
    for (size_t i = 0; i < size; i++) {
      dds_message.h_[static_cast<DDS_Long>(i)] =
        ros_message.h[i];
    }
  }

  return true;
}

bool
convert_dds_message_to_ros(
  const ssafy_msgs::msg::dds_::BBox_ & dds_message,
  ssafy_msgs::msg::BBox & ros_message)
{
  // member.name num_bbox
  ros_message.num_bbox =
    dds_message.num_bbox_;

  // member.name idx_bbox
  {
    size_t size = dds_message.idx_bbox_.length();
    ros_message.idx_bbox.resize(size);
    for (size_t i = 0; i < size; i++) {
      ros_message.idx_bbox[i] =
        dds_message.idx_bbox_[static_cast<DDS_Long>(i)];
    }
  }

  // member.name x
  {
    size_t size = dds_message.x_.length();
    ros_message.x.resize(size);
    for (size_t i = 0; i < size; i++) {
      ros_message.x[i] =
        dds_message.x_[static_cast<DDS_Long>(i)];
    }
  }

  // member.name y
  {
    size_t size = dds_message.y_.length();
    ros_message.y.resize(size);
    for (size_t i = 0; i < size; i++) {
      ros_message.y[i] =
        dds_message.y_[static_cast<DDS_Long>(i)];
    }
  }

  // member.name w
  {
    size_t size = dds_message.w_.length();
    ros_message.w.resize(size);
    for (size_t i = 0; i < size; i++) {
      ros_message.w[i] =
        dds_message.w_[static_cast<DDS_Long>(i)];
    }
  }

  // member.name h
  {
    size_t size = dds_message.h_.length();
    ros_message.h.resize(size);
    for (size_t i = 0; i < size; i++) {
      ros_message.h[i] =
        dds_message.h_[static_cast<DDS_Long>(i)];
    }
  }

  return true;
}

bool
to_cdr_stream__BBox(
  const void * untyped_ros_message,
  rcutils_uint8_array_t * cdr_stream)
{
  if (!cdr_stream) {
    return false;
  }
  if (!untyped_ros_message) {
    return false;
  }

  // cast the untyped to the known ros message
  const ssafy_msgs::msg::BBox & ros_message =
    *(const ssafy_msgs::msg::BBox *)untyped_ros_message;

  // create a respective connext dds type
  ssafy_msgs::msg::dds_::BBox_ * dds_message = ssafy_msgs::msg::dds_::BBox_TypeSupport::create_data();
  if (!dds_message) {
    return false;
  }

  // convert ros to dds
  if (!convert_ros_message_to_dds(ros_message, *dds_message)) {
    return false;
  }

  // call the serialize function for the first time to get the expected length of the message
  unsigned int expected_length;
  if (ssafy_msgs::msg::dds_::BBox_Plugin_serialize_to_cdr_buffer(
      NULL,
      &expected_length,
      dds_message) != RTI_TRUE)
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
      dds_message) != RTI_TRUE)
  {
    return false;
  }
  if (ssafy_msgs::msg::dds_::BBox_TypeSupport::delete_data(dds_message) != DDS_RETCODE_OK) {
    return false;
  }
  return true;
}

bool
to_message__BBox(
  const rcutils_uint8_array_t * cdr_stream,
  void * untyped_ros_message)
{
  if (!cdr_stream) {
    return false;
  }
  if (!cdr_stream->buffer) {
    fprintf(stderr, "cdr stream doesn't contain data\n");
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

  ssafy_msgs::msg::BBox & ros_message =
    *(ssafy_msgs::msg::BBox *)untyped_ros_message;
  bool success = convert_dds_message_to_ros(*dds_message, ros_message);
  if (ssafy_msgs::msg::dds_::BBox_TypeSupport::delete_data(dds_message) != DDS_RETCODE_OK) {
    return false;
  }
  return success;
}

static message_type_support_callbacks_t _BBox__callbacks = {
  "ssafy_msgs::msg",
  "BBox",
  &get_type_code__BBox,
  nullptr,
  nullptr,
  &to_cdr_stream__BBox,
  &to_message__BBox
};

static rosidl_message_type_support_t _BBox__handle = {
  rosidl_typesupport_connext_cpp::typesupport_identifier,
  &_BBox__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_connext_cpp

}  // namespace msg

}  // namespace ssafy_msgs


namespace rosidl_typesupport_connext_cpp
{

template<>
ROSIDL_TYPESUPPORT_CONNEXT_CPP_EXPORT_ssafy_msgs
const rosidl_message_type_support_t *
get_message_type_support_handle<ssafy_msgs::msg::BBox>()
{
  return &ssafy_msgs::msg::typesupport_connext_cpp::_BBox__handle;
}

}  // namespace rosidl_typesupport_connext_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_connext_cpp,
  ssafy_msgs, msg,
  BBox)()
{
  return &ssafy_msgs::msg::typesupport_connext_cpp::_BBox__handle;
}

#ifdef __cplusplus
}
#endif
