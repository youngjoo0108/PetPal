// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ssafy_msgs:msg\BBox.idl
// generated code does not contain a copyright notice

#ifndef SSAFY_MSGS__MSG__B_BOX__STRUCT_HPP_
#define SSAFY_MSGS__MSG__B_BOX__STRUCT_HPP_

#include <rosidl_generator_cpp/bounded_vector.hpp>
#include <rosidl_generator_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__ssafy_msgs__msg__BBox __attribute__((deprecated))
#else
# define DEPRECATED__ssafy_msgs__msg__BBox __declspec(deprecated)
#endif

namespace ssafy_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct BBox_
{
  using Type = BBox_<ContainerAllocator>;

  explicit BBox_(rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  {
    if (rosidl_generator_cpp::MessageInitialization::ALL == _init ||
      rosidl_generator_cpp::MessageInitialization::ZERO == _init)
    {
      this->num_bbox = 0;
    }
  }

  explicit BBox_(const ContainerAllocator & _alloc, rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_generator_cpp::MessageInitialization::ALL == _init ||
      rosidl_generator_cpp::MessageInitialization::ZERO == _init)
    {
      this->num_bbox = 0;
    }
  }

  // field types and members
  using _num_bbox_type =
    int16_t;
  _num_bbox_type num_bbox;
  using _idx_bbox_type =
    std::vector<int16_t, typename ContainerAllocator::template rebind<int16_t>::other>;
  _idx_bbox_type idx_bbox;
  using _x_type =
    std::vector<int16_t, typename ContainerAllocator::template rebind<int16_t>::other>;
  _x_type x;
  using _y_type =
    std::vector<int16_t, typename ContainerAllocator::template rebind<int16_t>::other>;
  _y_type y;
  using _w_type =
    std::vector<int16_t, typename ContainerAllocator::template rebind<int16_t>::other>;
  _w_type w;
  using _h_type =
    std::vector<int16_t, typename ContainerAllocator::template rebind<int16_t>::other>;
  _h_type h;

  // setters for named parameter idiom
  Type & set__num_bbox(
    const int16_t & _arg)
  {
    this->num_bbox = _arg;
    return *this;
  }
  Type & set__idx_bbox(
    const std::vector<int16_t, typename ContainerAllocator::template rebind<int16_t>::other> & _arg)
  {
    this->idx_bbox = _arg;
    return *this;
  }
  Type & set__x(
    const std::vector<int16_t, typename ContainerAllocator::template rebind<int16_t>::other> & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const std::vector<int16_t, typename ContainerAllocator::template rebind<int16_t>::other> & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__w(
    const std::vector<int16_t, typename ContainerAllocator::template rebind<int16_t>::other> & _arg)
  {
    this->w = _arg;
    return *this;
  }
  Type & set__h(
    const std::vector<int16_t, typename ContainerAllocator::template rebind<int16_t>::other> & _arg)
  {
    this->h = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ssafy_msgs::msg::BBox_<ContainerAllocator> *;
  using ConstRawPtr =
    const ssafy_msgs::msg::BBox_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ssafy_msgs::msg::BBox_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ssafy_msgs::msg::BBox_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ssafy_msgs::msg::BBox_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ssafy_msgs::msg::BBox_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ssafy_msgs::msg::BBox_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ssafy_msgs::msg::BBox_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ssafy_msgs::msg::BBox_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ssafy_msgs::msg::BBox_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ssafy_msgs__msg__BBox
    std::shared_ptr<ssafy_msgs::msg::BBox_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ssafy_msgs__msg__BBox
    std::shared_ptr<ssafy_msgs::msg::BBox_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const BBox_ & other) const
  {
    if (this->num_bbox != other.num_bbox) {
      return false;
    }
    if (this->idx_bbox != other.idx_bbox) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->w != other.w) {
      return false;
    }
    if (this->h != other.h) {
      return false;
    }
    return true;
  }
  bool operator!=(const BBox_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct BBox_

// alias to use template instance with default allocator
using BBox =
  ssafy_msgs::msg::BBox_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ssafy_msgs

#endif  // SSAFY_MSGS__MSG__B_BOX__STRUCT_HPP_
