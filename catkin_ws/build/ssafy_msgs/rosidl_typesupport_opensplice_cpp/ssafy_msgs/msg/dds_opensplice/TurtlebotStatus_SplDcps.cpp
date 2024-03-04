#include "TurtlebotStatus_SplDcps.h"
#include "ccpp_TurtlebotStatus_.h"

#include <v_copyIn.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

v_copyin_result
__ssafy_msgs_msg_dds__TurtlebotStatus___copyIn(
    c_base base,
    const struct ::ssafy_msgs::msg::dds_::TurtlebotStatus_ *from,
    struct _ssafy_msgs_msg_dds__TurtlebotStatus_ *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

    if(V_COPYIN_RESULT_IS_OK(result)){
        extern v_copyin_result __geometry_msgs_msg_dds__Twist___copyIn(c_base, const ::geometry_msgs::msg::dds_::Twist_ *, _geometry_msgs_msg_dds__Twist_ *);
        result = __geometry_msgs_msg_dds__Twist___copyIn(base, &from->twist_, &to->twist_);
    }
    to->power_supply_status_ = (c_octet)from->power_supply_status_;
    to->battery_percentage_ = (c_float)from->battery_percentage_;
    to->can_use_hand_ = (c_bool)from->can_use_hand_;
    to->can_put_ = (c_bool)from->can_put_;
    to->can_lift_ = (c_bool)from->can_lift_;
    return result;
}

void
__ssafy_msgs_msg_dds__TurtlebotStatus___copyOut(
    const void *_from,
    void *_to)
{
    const struct _ssafy_msgs_msg_dds__TurtlebotStatus_ *from = (const struct _ssafy_msgs_msg_dds__TurtlebotStatus_ *)_from;
    struct ::ssafy_msgs::msg::dds_::TurtlebotStatus_ *to = (struct ::ssafy_msgs::msg::dds_::TurtlebotStatus_ *)_to;
    {
        extern void __geometry_msgs_msg_dds__Twist___copyOut(const void *, void *);
        __geometry_msgs_msg_dds__Twist___copyOut((const void *)&from->twist_, (void *)&to->twist_);
    }
    to->power_supply_status_ = (::DDS::Octet)from->power_supply_status_;
    to->battery_percentage_ = (::DDS::Float)from->battery_percentage_;
    to->can_use_hand_ = (::DDS::Boolean)(from->can_use_hand_ != 0);
    to->can_put_ = (::DDS::Boolean)(from->can_put_ != 0);
    to->can_lift_ = (::DDS::Boolean)(from->can_lift_ != 0);
}

