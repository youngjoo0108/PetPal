// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ssafy_msgs:msg\TurtlebotStatus.idl
// generated code does not contain a copyright notice

#ifndef SSAFY_MSGS__MSG__TURTLEBOT_STATUS__STRUCT_HPP_
#define SSAFY_MSGS__MSG__TURTLEBOT_STATUS__STRUCT_HPP_

#include <rosidl_generator_cpp/bounded_vector.hpp>
#include <rosidl_generator_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


// Include directives for member types
// Member 'twist'
#include "geometry_msgs/msg/twist__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__ssafy_msgs__msg__TurtlebotStatus __attribute__((deprecated))
#else
# define DEPRECATED__ssafy_msgs__msg__TurtlebotStatus __declspec(deprecated)
#endif

namespace ssafy_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TurtlebotStatus_
{
  using Type = TurtlebotStatus_<ContainerAllocator>;

  explicit TurtlebotStatus_(rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  : twist(_init)
  {
    if (rosidl_generator_cpp::MessageInitialization::ALL == _init ||
      rosidl_generator_cpp::MessageInitialization::ZERO == _init)
    {
      this->power_supply_status = 0;
      this->battery_percentage = 0.0f;
      this->can_use_hand = false;
      this->can_put = false;
      this->can_lift = false;
    }
  }

  explicit TurtlebotStatus_(const ContainerAllocator & _alloc, rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  : twist(_alloc, _init)
  {
    if (rosidl_generator_cpp::MessageInitialization::ALL == _init ||
      rosidl_generator_cpp::MessageInitialization::ZERO == _init)
    {
      this->power_supply_status = 0;
      this->battery_percentage = 0.0f;
      this->can_use_hand = false;
      this->can_put = false;
      this->can_lift = false;
    }
  }

  // field types and members
  using _twist_type =
    geometry_msgs::msg::Twist_<ContainerAllocator>;
  _twist_type twist;
  using _power_supply_status_type =
    uint8_t;
  _power_supply_status_type power_supply_status;
  using _battery_percentage_type =
    float;
  _battery_percentage_type battery_percentage;
  using _can_use_hand_type =
    bool;
  _can_use_hand_type can_use_hand;
  using _can_put_type =
    bool;
  _can_put_type can_put;
  using _can_lift_type =
    bool;
  _can_lift_type can_lift;

  // setters for named parameter idiom
  Type & set__twist(
    const geometry_msgs::msg::Twist_<ContainerAllocator> & _arg)
  {
    this->twist = _arg;
    return *this;
  }
  Type & set__power_supply_status(
    const uint8_t & _arg)
  {
    this->power_supply_status = _arg;
    return *this;
  }
  Type & set__battery_percentage(
    const float & _arg)
  {
    this->battery_percentage = _arg;
    return *this;
  }
  Type & set__can_use_hand(
    const bool & _arg)
  {
    this->can_use_hand = _arg;
    return *this;
  }
  Type & set__can_put(
    const bool & _arg)
  {
    this->can_put = _arg;
    return *this;
  }
  Type & set__can_lift(
    const bool & _arg)
  {
    this->can_lift = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ssafy_msgs::msg::TurtlebotStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const ssafy_msgs::msg::TurtlebotStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ssafy_msgs::msg::TurtlebotStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ssafy_msgs::msg::TurtlebotStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ssafy_msgs::msg::TurtlebotStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ssafy_msgs::msg::TurtlebotStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ssafy_msgs::msg::TurtlebotStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ssafy_msgs::msg::TurtlebotStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ssafy_msgs::msg::TurtlebotStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ssafy_msgs::msg::TurtlebotStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ssafy_msgs__msg__TurtlebotStatus
    std::shared_ptr<ssafy_msgs::msg::TurtlebotStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ssafy_msgs__msg__TurtlebotStatus
    std::shared_ptr<ssafy_msgs::msg::TurtlebotStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TurtlebotStatus_ & other) const
  {
    if (this->twist != other.twist) {
      return false;
    }
    if (this->power_supply_status != other.power_supply_status) {
      return false;
    }
    if (this->battery_percentage != other.battery_percentage) {
      return false;
    }
    if (this->can_use_hand != other.can_use_hand) {
      return false;
    }
    if (this->can_put != other.can_put) {
      return false;
    }
    if (this->can_lift != other.can_lift) {
      return false;
    }
    return true;
  }
  bool operator!=(const TurtlebotStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TurtlebotStatus_

// alias to use template instance with default allocator
using TurtlebotStatus =
  ssafy_msgs::msg::TurtlebotStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ssafy_msgs

#endif  // SSAFY_MSGS__MSG__TURTLEBOT_STATUS__STRUCT_HPP_
