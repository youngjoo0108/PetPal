#include "HandControl_SplDcps.h"
#include "ccpp_HandControl_.h"

#include <v_copyIn.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

v_copyin_result
__ssafy_msgs_msg_dds__HandControl___copyIn(
    c_base base,
    const struct ::ssafy_msgs::msg::dds_::HandControl_ *from,
    struct _ssafy_msgs_msg_dds__HandControl_ *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

    to->control_mode_ = (c_octet)from->control_mode_;
    to->put_distance_ = (c_float)from->put_distance_;
    to->put_height_ = (c_float)from->put_height_;
    return result;
}

void
__ssafy_msgs_msg_dds__HandControl___copyOut(
    const void *_from,
    void *_to)
{
    const struct _ssafy_msgs_msg_dds__HandControl_ *from = (const struct _ssafy_msgs_msg_dds__HandControl_ *)_from;
    struct ::ssafy_msgs::msg::dds_::HandControl_ *to = (struct ::ssafy_msgs::msg::dds_::HandControl_ *)_to;
    to->control_mode_ = (::DDS::Octet)from->control_mode_;
    to->put_distance_ = (::DDS::Float)from->put_distance_;
    to->put_height_ = (::DDS::Float)from->put_height_;
}

