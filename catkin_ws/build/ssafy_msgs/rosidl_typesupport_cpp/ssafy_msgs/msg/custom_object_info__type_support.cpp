// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from ssafy_msgs:msg\CustomObjectInfo.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_generator_c/message_type_support_struct.h"
#include "ssafy_msgs/msg/custom_object_info__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/type_support_map.h"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace ssafy_msgs
{

namespace msg
{

namespace rosidl_typesupport_cpp
{

typedef struct _CustomObjectInfo_type_support_ids_t
{
  const char * typesupport_identifier[4];
} _CustomObjectInfo_type_support_ids_t;

static const _CustomObjectInfo_type_support_ids_t _CustomObjectInfo_message_typesupport_ids = {
  {
    "rosidl_typesupport_connext_cpp",  // ::rosidl_typesupport_connext_cpp::typesupport_identifier,
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
    "rosidl_typesupport_opensplice_cpp",  // ::rosidl_typesupport_opensplice_cpp::typesupport_identifier,
  }
};

typedef struct _CustomObjectInfo_type_support_symbol_names_t
{
  const char * symbol_name[4];
} _CustomObjectInfo_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _CustomObjectInfo_type_support_symbol_names_t _CustomObjectInfo_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_connext_cpp, ssafy_msgs, msg, CustomObjectInfo)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, ssafy_msgs, msg, CustomObjectInfo)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, ssafy_msgs, msg, CustomObjectInfo)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_opensplice_cpp, ssafy_msgs, msg, CustomObjectInfo)),
  }
};

typedef struct _CustomObjectInfo_type_support_data_t
{
  void * data[4];
} _CustomObjectInfo_type_support_data_t;

static _CustomObjectInfo_type_support_data_t _CustomObjectInfo_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _CustomObjectInfo_message_typesupport_map = {
  4,
  "ssafy_msgs",
  &_CustomObjectInfo_message_typesupport_ids.typesupport_identifier[0],
  &_CustomObjectInfo_message_typesupport_symbol_names.symbol_name[0],
  &_CustomObjectInfo_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t CustomObjectInfo_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_CustomObjectInfo_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace msg

}  // namespace ssafy_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<ssafy_msgs::msg::CustomObjectInfo>()
{
  return &::ssafy_msgs::msg::rosidl_typesupport_cpp::CustomObjectInfo_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, ssafy_msgs, msg, CustomObjectInfo)() {
  return get_message_type_support_handle<ssafy_msgs::msg::CustomObjectInfo>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp
