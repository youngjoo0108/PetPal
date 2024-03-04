// generated from rosidl_typesupport_connext_cpp/resource/idl__rosidl_typesupport_connext_cpp.hpp.em
// with input from ssafy_msgs:msg\TurtlebotStatus.idl
// generated code does not contain a copyright notice


#ifndef SSAFY_MSGS__MSG__TURTLEBOT_STATUS__ROSIDL_TYPESUPPORT_CONNEXT_CPP_HPP_
#define SSAFY_MSGS__MSG__TURTLEBOT_STATUS__ROSIDL_TYPESUPPORT_CONNEXT_CPP_HPP_

#include "rosidl_generator_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "ssafy_msgs/msg/rosidl_typesupport_connext_cpp__visibility_control.h"
#include "ssafy_msgs/msg/turtlebot_status__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif

#include "ssafy_msgs/msg/dds_connext/TurtlebotStatus_Support.h"
#include "ssafy_msgs/msg/dds_connext/TurtlebotStatus_Plugin.h"
#include "ndds/ndds_cpp.h"

#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// forward declaration of internal CDR Stream
struct ConnextStaticCDRStream;

// forward declaration of DDS types
class DDSDomainParticipant;
class DDSDataWriter;
class DDSDataReader;


namespace ssafy_msgs
{

namespace msg
{
namespace typesupport_connext_cpp
{

DDS_TypeCode *
get_type_code__TurtlebotStatus();

bool
ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_ssafy_msgs
convert_ros_message_to_dds(
  const ssafy_msgs::msg::TurtlebotStatus & ros_message,
  ssafy_msgs::msg::dds_::TurtlebotStatus_ & dds_message);

bool
ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_ssafy_msgs
convert_dds_message_to_ros(
  const ssafy_msgs::msg::dds_::TurtlebotStatus_ & dds_message,
  ssafy_msgs::msg::TurtlebotStatus & ros_message);

bool
to_cdr_stream__TurtlebotStatus(
  const void * untyped_ros_message,
  ConnextStaticCDRStream * cdr_stream);

bool
to_message__TurtlebotStatus(
  const ConnextStaticCDRStream * cdr_stream,
  void * untyped_ros_message);

}  // namespace typesupport_connext_cpp

}  // namespace msg

}  // namespace ssafy_msgs


#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_ssafy_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_connext_cpp,
  ssafy_msgs, msg,
  TurtlebotStatus)();

#ifdef __cplusplus
}
#endif


#endif  // SSAFY_MSGS__MSG__TURTLEBOT_STATUS__ROSIDL_TYPESUPPORT_CONNEXT_CPP_HPP_
