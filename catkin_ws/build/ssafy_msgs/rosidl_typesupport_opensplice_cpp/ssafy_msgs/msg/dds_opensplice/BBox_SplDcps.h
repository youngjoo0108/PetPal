#ifndef BBOX_SPLTYPES_H
#define BBOX_SPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "ccpp_BBox_.h"
#include "ssafy_msgs/msg/rosidl_typesupport_opensplice_cpp__visibility_control.h"

extern c_metaObject __BBox__ssafy_msgs__load (c_base base);

extern c_metaObject __BBox__ssafy_msgs_msg__load (c_base base);

extern c_metaObject __BBox__ssafy_msgs_msg_dds___load (c_base base);

extern const char *ssafy_msgs_msg_dds__BBox__metaDescriptor[];
extern const int ssafy_msgs_msg_dds__BBox__metaDescriptorArrLength;
extern const int ssafy_msgs_msg_dds__BBox__metaDescriptorLength;
extern c_metaObject __ssafy_msgs_msg_dds__BBox___load (c_base base);
struct _ssafy_msgs_msg_dds__BBox_ ;
extern ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_ssafy_msgs v_copyin_result __ssafy_msgs_msg_dds__BBox___copyIn(c_base base, const struct ssafy_msgs::msg::dds_::BBox_ *from, struct _ssafy_msgs_msg_dds__BBox_ *to);
extern ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_ssafy_msgs void __ssafy_msgs_msg_dds__BBox___copyOut(const void *_from, void *_to);
struct _ssafy_msgs_msg_dds__BBox_ {
    c_short num_bbox_;
    c_sequence idx_bbox_;
    c_sequence x_;
    c_sequence y_;
    c_sequence w_;
    c_sequence h_;
};

#undef OS_API
#endif
