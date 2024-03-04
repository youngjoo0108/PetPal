// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ssafy_msgs:msg\CustomObjectInfo.idl
// generated code does not contain a copyright notice

#ifndef SSAFY_MSGS__MSG__CUSTOM_OBJECT_INFO__STRUCT_HPP_
#define SSAFY_MSGS__MSG__CUSTOM_OBJECT_INFO__STRUCT_HPP_

#include <rosidl_generator_cpp/bounded_vector.hpp>
#include <rosidl_generator_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/vector3__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__ssafy_msgs__msg__CustomObjectInfo __attribute__((deprecated))
#else
# define DEPRECATED__ssafy_msgs__msg__CustomObjectInfo __declspec(deprecated)
#endif

namespace ssafy_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CustomObjectInfo_
{
  using Type = CustomObjectInfo_<ContainerAllocator>;

  explicit CustomObjectInfo_(rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit CustomObjectInfo_(const ContainerAllocator & _alloc, rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _position_type =
    std::vector<geometry_msgs::msg::Vector3_<ContainerAllocator>, typename ContainerAllocator::template rebind<geometry_msgs::msg::Vector3_<ContainerAllocator>>::other>;
  _position_type position;

  // setters for named parameter idiom
  Type & set__position(
    const std::vector<geometry_msgs::msg::Vector3_<ContainerAllocator>, typename ContainerAllocator::template rebind<geometry_msgs::msg::Vector3_<ContainerAllocator>>::other> & _arg)
  {
    this->position = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ssafy_msgs::msg::CustomObjectInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const ssafy_msgs::msg::CustomObjectInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ssafy_msgs::msg::CustomObjectInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ssafy_msgs::msg::CustomObjectInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ssafy_msgs::msg::CustomObjectInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ssafy_msgs::msg::CustomObjectInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ssafy_msgs::msg::CustomObjectInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ssafy_msgs::msg::CustomObjectInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ssafy_msgs::msg::CustomObjectInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ssafy_msgs::msg::CustomObjectInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ssafy_msgs__msg__CustomObjectInfo
    std::shared_ptr<ssafy_msgs::msg::CustomObjectInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ssafy_msgs__msg__CustomObjectInfo
    std::shared_ptr<ssafy_msgs::msg::CustomObjectInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CustomObjectInfo_ & other) const
  {
    if (this->position != other.position) {
      return false;
    }
    return true;
  }
  bool operator!=(const CustomObjectInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CustomObjectInfo_

// alias to use template instance with default allocator
using CustomObjectInfo =
  ssafy_msgs::msg::CustomObjectInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ssafy_msgs

#endif  // SSAFY_MSGS__MSG__CUSTOM_OBJECT_INFO__STRUCT_HPP_
