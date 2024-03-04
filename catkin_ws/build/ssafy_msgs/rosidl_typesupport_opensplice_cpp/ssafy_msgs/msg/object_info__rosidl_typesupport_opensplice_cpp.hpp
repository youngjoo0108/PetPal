// generated from rosidl_typesupport_opensplice_cpp/resource/idl__rosidl_typesupport_cpp.hpp.em
// generated code does not contain a copyright notice
#ifndef SSAFY_MSGS__MSG__OBJECT_INFO__ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_HPP_
#define SSAFY_MSGS__MSG__OBJECT_INFO__ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_HPP_
// generated from
// rosidl_typesupport_opensplice_cpp/resource/msg__rosidl_typesupport_opensplice_cpp.hpp.em
// generated code does not contain a copyright notice

#include "ssafy_msgs/msg/object_info__struct.hpp"
#include "ssafy_msgs/msg/dds_opensplice/ccpp_ObjectInfo_.h"
#include "rosidl_generator_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "ssafy_msgs/msg/rosidl_typesupport_opensplice_cpp__visibility_control.h"

namespace DDS
{
class DomainParticipant;
class DataReader;
class DataWriter;
}  // namespace DDS

namespace ssafy_msgs
{
namespace msg
{
namespace typesupport_opensplice_cpp
{

ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_ssafy_msgs
extern void register_type__ObjectInfo(
  DDS::DomainParticipant * participant,
  const char * type_name);

ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_ssafy_msgs
extern void convert_ros_message_to_dds(
  const ssafy_msgs::msg::ObjectInfo & ros_message,
  ssafy_msgs::msg::dds_::ObjectInfo_ & dds_message);

ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_ssafy_msgs
extern void publish__ObjectInfo(
  DDS::DataWriter * topic_writer,
  const void * untyped_ros_message);

ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_ssafy_msgs
extern void convert_dds_message_to_ros(
  const ssafy_msgs::msg::dds_::ObjectInfo_ & dds_message,
  ssafy_msgs::msg::ObjectInfo & ros_message);

ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_ssafy_msgs
extern bool take__ObjectInfo(
  DDS::DataReader * topic_reader,
  bool ignore_local_publications,
  void * untyped_ros_message,
  bool * taken);

ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_EXPORT_ssafy_msgs
const char *
serialize__ObjectInfo(
  const void * untyped_ros_message,
  void * serialized_data);

ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_EXPORT_ssafy_msgs
const char *
deserialize__ObjectInfo(
  const uint8_t * buffer,
  unsigned length,
  void * untyped_ros_message);

}  // namespace typesupport_opensplice_cpp

}  // namespace msg
}  // namespace ssafy_msgs

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_ssafy_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_opensplice_cpp,
  ssafy_msgs, msg,
  ObjectInfo)();

#ifdef __cplusplus
}
#endif
#endif  // SSAFY_MSGS__MSG__OBJECT_INFO__ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_HPP_
