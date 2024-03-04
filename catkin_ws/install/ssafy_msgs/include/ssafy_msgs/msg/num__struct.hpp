// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ssafy_msgs:msg\Num.idl
// generated code does not contain a copyright notice

#ifndef SSAFY_MSGS__MSG__NUM__STRUCT_HPP_
#define SSAFY_MSGS__MSG__NUM__STRUCT_HPP_

#include <rosidl_generator_cpp/bounded_vector.hpp>
#include <rosidl_generator_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__ssafy_msgs__msg__Num __attribute__((deprecated))
#else
# define DEPRECATED__ssafy_msgs__msg__Num __declspec(deprecated)
#endif

namespace ssafy_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Num_
{
  using Type = Num_<ContainerAllocator>;

  explicit Num_(rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  {
    if (rosidl_generator_cpp::MessageInitialization::ALL == _init ||
      rosidl_generator_cpp::MessageInitialization::ZERO == _init)
    {
      this->num = 0ll;
      this->air = false;
      this->door = false;
    }
  }

  explicit Num_(const ContainerAllocator & _alloc, rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_generator_cpp::MessageInitialization::ALL == _init ||
      rosidl_generator_cpp::MessageInitialization::ZERO == _init)
    {
      this->num = 0ll;
      this->air = false;
      this->door = false;
    }
  }

  // field types and members
  using _num_type =
    int64_t;
  _num_type num;
  using _air_type =
    bool;
  _air_type air;
  using _door_type =
    bool;
  _door_type door;

  // setters for named parameter idiom
  Type & set__num(
    const int64_t & _arg)
  {
    this->num = _arg;
    return *this;
  }
  Type & set__air(
    const bool & _arg)
  {
    this->air = _arg;
    return *this;
  }
  Type & set__door(
    const bool & _arg)
  {
    this->door = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ssafy_msgs::msg::Num_<ContainerAllocator> *;
  using ConstRawPtr =
    const ssafy_msgs::msg::Num_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ssafy_msgs::msg::Num_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ssafy_msgs::msg::Num_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ssafy_msgs::msg::Num_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ssafy_msgs::msg::Num_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ssafy_msgs::msg::Num_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ssafy_msgs::msg::Num_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ssafy_msgs::msg::Num_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ssafy_msgs::msg::Num_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ssafy_msgs__msg__Num
    std::shared_ptr<ssafy_msgs::msg::Num_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ssafy_msgs__msg__Num
    std::shared_ptr<ssafy_msgs::msg::Num_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Num_ & other) const
  {
    if (this->num != other.num) {
      return false;
    }
    if (this->air != other.air) {
      return false;
    }
    if (this->door != other.door) {
      return false;
    }
    return true;
  }
  bool operator!=(const Num_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Num_

// alias to use template instance with default allocator
using Num =
  ssafy_msgs::msg::Num_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ssafy_msgs

#endif  // SSAFY_MSGS__MSG__NUM__STRUCT_HPP_
