// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ssafy_msgs:msg\CustomObjectInfo.idl
// generated code does not contain a copyright notice

#ifndef SSAFY_MSGS__MSG__CUSTOM_OBJECT_INFO__TRAITS_HPP_
#define SSAFY_MSGS__MSG__CUSTOM_OBJECT_INFO__TRAITS_HPP_

#include "ssafy_msgs/msg/custom_object_info__struct.hpp"
#include <rosidl_generator_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<ssafy_msgs::msg::CustomObjectInfo>()
{
  return "ssafy_msgs::msg::CustomObjectInfo";
}

template<>
struct has_fixed_size<ssafy_msgs::msg::CustomObjectInfo>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<ssafy_msgs::msg::CustomObjectInfo>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<ssafy_msgs::msg::CustomObjectInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SSAFY_MSGS__MSG__CUSTOM_OBJECT_INFO__TRAITS_HPP_
