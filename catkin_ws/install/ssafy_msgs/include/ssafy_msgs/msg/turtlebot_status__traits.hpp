// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ssafy_msgs:msg\TurtlebotStatus.idl
// generated code does not contain a copyright notice

#ifndef SSAFY_MSGS__MSG__TURTLEBOT_STATUS__TRAITS_HPP_
#define SSAFY_MSGS__MSG__TURTLEBOT_STATUS__TRAITS_HPP_

#include "ssafy_msgs/msg/turtlebot_status__struct.hpp"
#include <rosidl_generator_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

// Include directives for member types
// Member 'twist'
#include "geometry_msgs/msg/twist__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<ssafy_msgs::msg::TurtlebotStatus>()
{
  return "ssafy_msgs::msg::TurtlebotStatus";
}

template<>
struct has_fixed_size<ssafy_msgs::msg::TurtlebotStatus>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Twist>::value> {};

template<>
struct has_bounded_size<ssafy_msgs::msg::TurtlebotStatus>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Twist>::value> {};

template<>
struct is_message<ssafy_msgs::msg::TurtlebotStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SSAFY_MSGS__MSG__TURTLEBOT_STATUS__TRAITS_HPP_
