// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from ssafy_msgs:msg\BBox.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_generator_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "ssafy_msgs/msg/b_box__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace ssafy_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void BBox_init_function(
  void * message_memory, rosidl_generator_cpp::MessageInitialization _init)
{
  new (message_memory) ssafy_msgs::msg::BBox(_init);
}

void BBox_fini_function(void * message_memory)
{
  auto typed_message = static_cast<ssafy_msgs::msg::BBox *>(message_memory);
  typed_message->~BBox();
}

size_t size_function__BBox__idx_bbox(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<int16_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__BBox__idx_bbox(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<int16_t> *>(untyped_member);
  return &member[index];
}

void * get_function__BBox__idx_bbox(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<int16_t> *>(untyped_member);
  return &member[index];
}

void resize_function__BBox__idx_bbox(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<int16_t> *>(untyped_member);
  member->resize(size);
}

size_t size_function__BBox__x(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<int16_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__BBox__x(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<int16_t> *>(untyped_member);
  return &member[index];
}

void * get_function__BBox__x(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<int16_t> *>(untyped_member);
  return &member[index];
}

void resize_function__BBox__x(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<int16_t> *>(untyped_member);
  member->resize(size);
}

size_t size_function__BBox__y(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<int16_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__BBox__y(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<int16_t> *>(untyped_member);
  return &member[index];
}

void * get_function__BBox__y(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<int16_t> *>(untyped_member);
  return &member[index];
}

void resize_function__BBox__y(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<int16_t> *>(untyped_member);
  member->resize(size);
}

size_t size_function__BBox__w(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<int16_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__BBox__w(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<int16_t> *>(untyped_member);
  return &member[index];
}

void * get_function__BBox__w(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<int16_t> *>(untyped_member);
  return &member[index];
}

void resize_function__BBox__w(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<int16_t> *>(untyped_member);
  member->resize(size);
}

size_t size_function__BBox__h(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<int16_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__BBox__h(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<int16_t> *>(untyped_member);
  return &member[index];
}

void * get_function__BBox__h(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<int16_t> *>(untyped_member);
  return &member[index];
}

void resize_function__BBox__h(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<int16_t> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember BBox_message_member_array[6] = {
  {
    "num_bbox",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs::msg::BBox, num_bbox),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "idx_bbox",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs::msg::BBox, idx_bbox),  // bytes offset in struct
    nullptr,  // default value
    size_function__BBox__idx_bbox,  // size() function pointer
    get_const_function__BBox__idx_bbox,  // get_const(index) function pointer
    get_function__BBox__idx_bbox,  // get(index) function pointer
    resize_function__BBox__idx_bbox  // resize(index) function pointer
  },
  {
    "x",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs::msg::BBox, x),  // bytes offset in struct
    nullptr,  // default value
    size_function__BBox__x,  // size() function pointer
    get_const_function__BBox__x,  // get_const(index) function pointer
    get_function__BBox__x,  // get(index) function pointer
    resize_function__BBox__x  // resize(index) function pointer
  },
  {
    "y",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs::msg::BBox, y),  // bytes offset in struct
    nullptr,  // default value
    size_function__BBox__y,  // size() function pointer
    get_const_function__BBox__y,  // get_const(index) function pointer
    get_function__BBox__y,  // get(index) function pointer
    resize_function__BBox__y  // resize(index) function pointer
  },
  {
    "w",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs::msg::BBox, w),  // bytes offset in struct
    nullptr,  // default value
    size_function__BBox__w,  // size() function pointer
    get_const_function__BBox__w,  // get_const(index) function pointer
    get_function__BBox__w,  // get(index) function pointer
    resize_function__BBox__w  // resize(index) function pointer
  },
  {
    "h",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs::msg::BBox, h),  // bytes offset in struct
    nullptr,  // default value
    size_function__BBox__h,  // size() function pointer
    get_const_function__BBox__h,  // get_const(index) function pointer
    get_function__BBox__h,  // get(index) function pointer
    resize_function__BBox__h  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers BBox_message_members = {
  "ssafy_msgs::msg",  // message namespace
  "BBox",  // message name
  6,  // number of fields
  sizeof(ssafy_msgs::msg::BBox),
  BBox_message_member_array,  // message members
  BBox_init_function,  // function to initialize message memory (memory has to be allocated)
  BBox_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t BBox_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &BBox_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace ssafy_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<ssafy_msgs::msg::BBox>()
{
  return &::ssafy_msgs::msg::rosidl_typesupport_introspection_cpp::BBox_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, ssafy_msgs, msg, BBox)() {
  return &::ssafy_msgs::msg::rosidl_typesupport_introspection_cpp::BBox_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
