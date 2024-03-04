// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ssafy_msgs:msg\HandControl.idl
// generated code does not contain a copyright notice

#ifndef SSAFY_MSGS__MSG__HAND_CONTROL__STRUCT_HPP_
#define SSAFY_MSGS__MSG__HAND_CONTROL__STRUCT_HPP_

#include <rosidl_generator_cpp/bounded_vector.hpp>
#include <rosidl_generator_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__ssafy_msgs__msg__HandControl __attribute__((deprecated))
#else
# define DEPRECATED__ssafy_msgs__msg__HandControl __declspec(deprecated)
#endif

namespace ssafy_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct HandControl_
{
  using Type = HandControl_<ContainerAllocator>;

  explicit HandControl_(rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  {
    if (rosidl_generator_cpp::MessageInitialization::ALL == _init ||
      rosidl_generator_cpp::MessageInitialization::ZERO == _init)
    {
      this->control_mode = 0;
      this->put_distance = 0.0f;
      this->put_height = 0.0f;
    }
  }

  explicit HandControl_(const ContainerAllocator & _alloc, rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_generator_cpp::MessageInitialization::ALL == _init ||
      rosidl_generator_cpp::MessageInitialization::ZERO == _init)
    {
      this->control_mode = 0;
      this->put_distance = 0.0f;
      this->put_height = 0.0f;
    }
  }

  // field types and members
  using _control_mode_type =
    uint8_t;
  _control_mode_type control_mode;
  using _put_distance_type =
    float;
  _put_distance_type put_distance;
  using _put_height_type =
    float;
  _put_height_type put_height;

  // setters for named parameter idiom
  Type & set__control_mode(
    const uint8_t & _arg)
  {
    this->control_mode = _arg;
    return *this;
  }
  Type & set__put_distance(
    const float & _arg)
  {
    this->put_distance = _arg;
    return *this;
  }
  Type & set__put_height(
    const float & _arg)
  {
    this->put_height = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ssafy_msgs::msg::HandControl_<ContainerAllocator> *;
  using ConstRawPtr =
    const ssafy_msgs::msg::HandControl_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ssafy_msgs::msg::HandControl_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ssafy_msgs::msg::HandControl_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ssafy_msgs::msg::HandControl_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ssafy_msgs::msg::HandControl_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ssafy_msgs::msg::HandControl_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ssafy_msgs::msg::HandControl_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ssafy_msgs::msg::HandControl_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ssafy_msgs::msg::HandControl_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ssafy_msgs__msg__HandControl
    std::shared_ptr<ssafy_msgs::msg::HandControl_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ssafy_msgs__msg__HandControl
    std::shared_ptr<ssafy_msgs::msg::HandControl_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const HandControl_ & other) const
  {
    if (this->control_mode != other.control_mode) {
      return false;
    }
    if (this->put_distance != other.put_distance) {
      return false;
    }
    if (this->put_height != other.put_height) {
      return false;
    }
    return true;
  }
  bool operator!=(const HandControl_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct HandControl_

// alias to use template instance with default allocator
using HandControl =
  ssafy_msgs::msg::HandControl_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ssafy_msgs

#endif  // SSAFY_MSGS__MSG__HAND_CONTROL__STRUCT_HPP_
