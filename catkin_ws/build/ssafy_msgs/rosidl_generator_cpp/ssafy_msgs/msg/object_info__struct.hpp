// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ssafy_msgs:msg\ObjectInfo.idl
// generated code does not contain a copyright notice

#ifndef SSAFY_MSGS__MSG__OBJECT_INFO__STRUCT_HPP_
#define SSAFY_MSGS__MSG__OBJECT_INFO__STRUCT_HPP_

#include <rosidl_generator_cpp/bounded_vector.hpp>
#include <rosidl_generator_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__ssafy_msgs__msg__ObjectInfo __attribute__((deprecated))
#else
# define DEPRECATED__ssafy_msgs__msg__ObjectInfo __declspec(deprecated)
#endif

namespace ssafy_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ObjectInfo_
{
  using Type = ObjectInfo_<ContainerAllocator>;

  explicit ObjectInfo_(rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  {
    if (rosidl_generator_cpp::MessageInitialization::ALL == _init ||
      rosidl_generator_cpp::MessageInitialization::ZERO == _init)
    {
      this->num_obj = 0;
    }
  }

  explicit ObjectInfo_(const ContainerAllocator & _alloc, rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_generator_cpp::MessageInitialization::ALL == _init ||
      rosidl_generator_cpp::MessageInitialization::ZERO == _init)
    {
      this->num_obj = 0;
    }
  }

  // field types and members
  using _num_obj_type =
    int16_t;
  _num_obj_type num_obj;
  using _idx_obj_type =
    std::vector<int16_t, typename ContainerAllocator::template rebind<int16_t>::other>;
  _idx_obj_type idx_obj;
  using _x_type =
    std::vector<float, typename ContainerAllocator::template rebind<float>::other>;
  _x_type x;
  using _y_type =
    std::vector<float, typename ContainerAllocator::template rebind<float>::other>;
  _y_type y;

  // setters for named parameter idiom
  Type & set__num_obj(
    const int16_t & _arg)
  {
    this->num_obj = _arg;
    return *this;
  }
  Type & set__idx_obj(
    const std::vector<int16_t, typename ContainerAllocator::template rebind<int16_t>::other> & _arg)
  {
    this->idx_obj = _arg;
    return *this;
  }
  Type & set__x(
    const std::vector<float, typename ContainerAllocator::template rebind<float>::other> & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const std::vector<float, typename ContainerAllocator::template rebind<float>::other> & _arg)
  {
    this->y = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ssafy_msgs::msg::ObjectInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const ssafy_msgs::msg::ObjectInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ssafy_msgs::msg::ObjectInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ssafy_msgs::msg::ObjectInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ssafy_msgs::msg::ObjectInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ssafy_msgs::msg::ObjectInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ssafy_msgs::msg::ObjectInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ssafy_msgs::msg::ObjectInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ssafy_msgs::msg::ObjectInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ssafy_msgs::msg::ObjectInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ssafy_msgs__msg__ObjectInfo
    std::shared_ptr<ssafy_msgs::msg::ObjectInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ssafy_msgs__msg__ObjectInfo
    std::shared_ptr<ssafy_msgs::msg::ObjectInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ObjectInfo_ & other) const
  {
    if (this->num_obj != other.num_obj) {
      return false;
    }
    if (this->idx_obj != other.idx_obj) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    return true;
  }
  bool operator!=(const ObjectInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ObjectInfo_

// alias to use template instance with default allocator
using ObjectInfo =
  ssafy_msgs::msg::ObjectInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ssafy_msgs

#endif  // SSAFY_MSGS__MSG__OBJECT_INFO__STRUCT_HPP_
