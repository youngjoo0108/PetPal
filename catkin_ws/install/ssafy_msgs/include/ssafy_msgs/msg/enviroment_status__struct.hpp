// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ssafy_msgs:msg\EnviromentStatus.idl
// generated code does not contain a copyright notice

#ifndef SSAFY_MSGS__MSG__ENVIROMENT_STATUS__STRUCT_HPP_
#define SSAFY_MSGS__MSG__ENVIROMENT_STATUS__STRUCT_HPP_

#include <rosidl_generator_cpp/bounded_vector.hpp>
#include <rosidl_generator_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__ssafy_msgs__msg__EnviromentStatus __attribute__((deprecated))
#else
# define DEPRECATED__ssafy_msgs__msg__EnviromentStatus __declspec(deprecated)
#endif

namespace ssafy_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct EnviromentStatus_
{
  using Type = EnviromentStatus_<ContainerAllocator>;

  explicit EnviromentStatus_(rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  {
    if (rosidl_generator_cpp::MessageInitialization::ALL == _init ||
      rosidl_generator_cpp::MessageInitialization::ZERO == _init)
    {
      this->month = 0;
      this->day = 0;
      this->hour = 0;
      this->minute = 0;
      this->temperature = 0;
      this->weather = "";
    }
  }

  explicit EnviromentStatus_(const ContainerAllocator & _alloc, rosidl_generator_cpp::MessageInitialization _init = rosidl_generator_cpp::MessageInitialization::ALL)
  : weather(_alloc)
  {
    if (rosidl_generator_cpp::MessageInitialization::ALL == _init ||
      rosidl_generator_cpp::MessageInitialization::ZERO == _init)
    {
      this->month = 0;
      this->day = 0;
      this->hour = 0;
      this->minute = 0;
      this->temperature = 0;
      this->weather = "";
    }
  }

  // field types and members
  using _month_type =
    uint8_t;
  _month_type month;
  using _day_type =
    uint8_t;
  _day_type day;
  using _hour_type =
    uint8_t;
  _hour_type hour;
  using _minute_type =
    uint8_t;
  _minute_type minute;
  using _temperature_type =
    uint8_t;
  _temperature_type temperature;
  using _weather_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _weather_type weather;

  // setters for named parameter idiom
  Type & set__month(
    const uint8_t & _arg)
  {
    this->month = _arg;
    return *this;
  }
  Type & set__day(
    const uint8_t & _arg)
  {
    this->day = _arg;
    return *this;
  }
  Type & set__hour(
    const uint8_t & _arg)
  {
    this->hour = _arg;
    return *this;
  }
  Type & set__minute(
    const uint8_t & _arg)
  {
    this->minute = _arg;
    return *this;
  }
  Type & set__temperature(
    const uint8_t & _arg)
  {
    this->temperature = _arg;
    return *this;
  }
  Type & set__weather(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->weather = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ssafy_msgs::msg::EnviromentStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const ssafy_msgs::msg::EnviromentStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ssafy_msgs::msg::EnviromentStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ssafy_msgs::msg::EnviromentStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ssafy_msgs::msg::EnviromentStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ssafy_msgs::msg::EnviromentStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ssafy_msgs::msg::EnviromentStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ssafy_msgs::msg::EnviromentStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ssafy_msgs::msg::EnviromentStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ssafy_msgs::msg::EnviromentStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ssafy_msgs__msg__EnviromentStatus
    std::shared_ptr<ssafy_msgs::msg::EnviromentStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ssafy_msgs__msg__EnviromentStatus
    std::shared_ptr<ssafy_msgs::msg::EnviromentStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EnviromentStatus_ & other) const
  {
    if (this->month != other.month) {
      return false;
    }
    if (this->day != other.day) {
      return false;
    }
    if (this->hour != other.hour) {
      return false;
    }
    if (this->minute != other.minute) {
      return false;
    }
    if (this->temperature != other.temperature) {
      return false;
    }
    if (this->weather != other.weather) {
      return false;
    }
    return true;
  }
  bool operator!=(const EnviromentStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EnviromentStatus_

// alias to use template instance with default allocator
using EnviromentStatus =
  ssafy_msgs::msg::EnviromentStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ssafy_msgs

#endif  // SSAFY_MSGS__MSG__ENVIROMENT_STATUS__STRUCT_HPP_
