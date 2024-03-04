#include "Num_SplDcps.h"
#include "ccpp_Num_.h"

#include <v_copyIn.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

v_copyin_result
__ssafy_msgs_msg_dds__Num___copyIn(
    c_base base,
    const struct ::ssafy_msgs::msg::dds_::Num_ *from,
    struct _ssafy_msgs_msg_dds__Num_ *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

    to->num_ = (c_longlong)from->num_;
    to->air_ = (c_bool)from->air_;
    to->door_ = (c_bool)from->door_;
    return result;
}

void
__ssafy_msgs_msg_dds__Num___copyOut(
    const void *_from,
    void *_to)
{
    const struct _ssafy_msgs_msg_dds__Num_ *from = (const struct _ssafy_msgs_msg_dds__Num_ *)_from;
    struct ::ssafy_msgs::msg::dds_::Num_ *to = (struct ::ssafy_msgs::msg::dds_::Num_ *)_to;
    to->num_ = (::DDS::LongLong)from->num_;
    to->air_ = (::DDS::Boolean)(from->air_ != 0);
    to->door_ = (::DDS::Boolean)(from->door_ != 0);
}

