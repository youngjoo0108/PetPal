// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ssafy_msgs:msg\HandControl.idl
// generated code does not contain a copyright notice

#ifndef SSAFY_MSGS__MSG__HAND_CONTROL__TRAITS_HPP_
#define SSAFY_MSGS__MSG__HAND_CONTROL__TRAITS_HPP_

#include "ssafy_msgs/msg/hand_control__struct.hpp"
#include <rosidl_generator_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<ssafy_msgs::msg::HandControl>()
{
  return "ssafy_msgs::msg::HandControl";
}

template<>
struct has_fixed_size<ssafy_msgs::msg::HandControl>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<ssafy_msgs::msg::HandControl>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<ssafy_msgs::msg::HandControl>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SSAFY_MSGS__MSG__HAND_CONTROL__TRAITS_HPP_
