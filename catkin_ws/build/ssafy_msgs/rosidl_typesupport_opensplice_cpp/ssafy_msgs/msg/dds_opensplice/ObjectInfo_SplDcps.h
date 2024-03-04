#ifndef OBJECTINFO_SPLTYPES_H
#define OBJECTINFO_SPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "ccpp_ObjectInfo_.h"
#include "ssafy_msgs/msg/rosidl_typesupport_opensplice_cpp__visibility_control.h"

extern c_metaObject __ObjectInfo__ssafy_msgs__load (c_base base);

extern c_metaObject __ObjectInfo__ssafy_msgs_msg__load (c_base base);

extern c_metaObject __ObjectInfo__ssafy_msgs_msg_dds___load (c_base base);

extern const char *ssafy_msgs_msg_dds__ObjectInfo__metaDescriptor[];
extern const int ssafy_msgs_msg_dds__ObjectInfo__metaDescriptorArrLength;
extern const int ssafy_msgs_msg_dds__ObjectInfo__metaDescriptorLength;
extern c_metaObject __ssafy_msgs_msg_dds__ObjectInfo___load (c_base base);
struct _ssafy_msgs_msg_dds__ObjectInfo_ ;
extern ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_ssafy_msgs v_copyin_result __ssafy_msgs_msg_dds__ObjectInfo___copyIn(c_base base, const struct ssafy_msgs::msg::dds_::ObjectInfo_ *from, struct _ssafy_msgs_msg_dds__ObjectInfo_ *to);
extern ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_ssafy_msgs void __ssafy_msgs_msg_dds__ObjectInfo___copyOut(const void *_from, void *_to);
struct _ssafy_msgs_msg_dds__ObjectInfo_ {
    c_short num_obj_;
    c_sequence idx_obj_;
    c_sequence x_;
    c_sequence y_;
};

#undef OS_API
#endif
