// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from ssafy_msgs:msg\ObjectInfo.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_generator_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "ssafy_msgs/msg/object_info__struct.hpp"
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

void ObjectInfo_init_function(
  void * message_memory, rosidl_generator_cpp::MessageInitialization _init)
{
  new (message_memory) ssafy_msgs::msg::ObjectInfo(_init);
}

void ObjectInfo_fini_function(void * message_memory)
{
  auto typed_message = static_cast<ssafy_msgs::msg::ObjectInfo *>(message_memory);
  typed_message->~ObjectInfo();
}

size_t size_function__ObjectInfo__idx_obj(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<int16_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ObjectInfo__idx_obj(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<int16_t> *>(untyped_member);
  return &member[index];
}

void * get_function__ObjectInfo__idx_obj(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<int16_t> *>(untyped_member);
  return &member[index];
}

void resize_function__ObjectInfo__idx_obj(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<int16_t> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ObjectInfo__x(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ObjectInfo__x(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__ObjectInfo__x(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void resize_function__ObjectInfo__x(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ObjectInfo__y(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ObjectInfo__y(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__ObjectInfo__y(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void resize_function__ObjectInfo__y(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ObjectInfo_message_member_array[4] = {
  {
    "num_obj",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs::msg::ObjectInfo, num_obj),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "idx_obj",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs::msg::ObjectInfo, idx_obj),  // bytes offset in struct
    nullptr,  // default value
    size_function__ObjectInfo__idx_obj,  // size() function pointer
    get_const_function__ObjectInfo__idx_obj,  // get_const(index) function pointer
    get_function__ObjectInfo__idx_obj,  // get(index) function pointer
    resize_function__ObjectInfo__idx_obj  // resize(index) function pointer
  },
  {
    "x",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs::msg::ObjectInfo, x),  // bytes offset in struct
    nullptr,  // default value
    size_function__ObjectInfo__x,  // size() function pointer
    get_const_function__ObjectInfo__x,  // get_const(index) function pointer
    get_function__ObjectInfo__x,  // get(index) function pointer
    resize_function__ObjectInfo__x  // resize(index) function pointer
  },
  {
    "y",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ssafy_msgs::msg::ObjectInfo, y),  // bytes offset in struct
    nullptr,  // default value
    size_function__ObjectInfo__y,  // size() function pointer
    get_const_function__ObjectInfo__y,  // get_const(index) function pointer
    get_function__ObjectInfo__y,  // get(index) function pointer
    resize_function__ObjectInfo__y  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ObjectInfo_message_members = {
  "ssafy_msgs::msg",  // message namespace
  "ObjectInfo",  // message name
  4,  // number of fields
  sizeof(ssafy_msgs::msg::ObjectInfo),
  ObjectInfo_message_member_array,  // message members
  ObjectInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  ObjectInfo_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ObjectInfo_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ObjectInfo_message_members,
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
get_message_type_support_handle<ssafy_msgs::msg::ObjectInfo>()
{
  return &::ssafy_msgs::msg::rosidl_typesupport_introspection_cpp::ObjectInfo_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, ssafy_msgs, msg, ObjectInfo)() {
  return &::ssafy_msgs::msg::rosidl_typesupport_introspection_cpp::ObjectInfo_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
