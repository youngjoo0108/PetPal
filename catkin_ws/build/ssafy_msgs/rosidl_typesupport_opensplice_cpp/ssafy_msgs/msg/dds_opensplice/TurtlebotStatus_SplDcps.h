#ifndef TURTLEBOTSTATUS_SPLTYPES_H
#define TURTLEBOTSTATUS_SPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "ccpp_TurtlebotStatus_.h"
#include "geometry_msgs/msg/dds_opensplice/Twist_SplDcps.h"

#include "ssafy_msgs/msg/rosidl_typesupport_opensplice_cpp__visibility_control.h"

extern c_metaObject __TurtlebotStatus__ssafy_msgs__load (c_base base);

extern c_metaObject __TurtlebotStatus__ssafy_msgs_msg__load (c_base base);

extern c_metaObject __TurtlebotStatus__ssafy_msgs_msg_dds___load (c_base base);

extern const char *ssafy_msgs_msg_dds__TurtlebotStatus__metaDescriptor[];
extern const int ssafy_msgs_msg_dds__TurtlebotStatus__metaDescriptorArrLength;
extern const int ssafy_msgs_msg_dds__TurtlebotStatus__metaDescriptorLength;
extern c_metaObject __ssafy_msgs_msg_dds__TurtlebotStatus___load (c_base base);
struct _ssafy_msgs_msg_dds__TurtlebotStatus_ ;
extern ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_ssafy_msgs v_copyin_result __ssafy_msgs_msg_dds__TurtlebotStatus___copyIn(c_base base, const struct ssafy_msgs::msg::dds_::TurtlebotStatus_ *from, struct _ssafy_msgs_msg_dds__TurtlebotStatus_ *to);
extern ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_ssafy_msgs void __ssafy_msgs_msg_dds__TurtlebotStatus___copyOut(const void *_from, void *_to);
struct _ssafy_msgs_msg_dds__TurtlebotStatus_ {
    struct _geometry_msgs_msg_dds__Twist_ twist_;
    c_octet power_supply_status_;
    c_float battery_percentage_;
    c_bool can_use_hand_;
    c_bool can_put_;
    c_bool can_lift_;
};

#undef OS_API
#endif
