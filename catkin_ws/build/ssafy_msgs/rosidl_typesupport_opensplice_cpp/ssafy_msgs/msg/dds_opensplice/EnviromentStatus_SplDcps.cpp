#include "EnviromentStatus_SplDcps.h"
#include "ccpp_EnviromentStatus_.h"

#include <v_copyIn.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

v_copyin_result
__ssafy_msgs_msg_dds__EnviromentStatus___copyIn(
    c_base base,
    const struct ::ssafy_msgs::msg::dds_::EnviromentStatus_ *from,
    struct _ssafy_msgs_msg_dds__EnviromentStatus_ *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

    to->month_ = (c_octet)from->month_;
    to->day_ = (c_octet)from->day_;
    to->hour_ = (c_octet)from->hour_;
    to->minute_ = (c_octet)from->minute_;
    to->temperature_ = (c_octet)from->temperature_;
#ifdef OSPL_BOUNDS_CHECK
    if(from->weather_){
        to->weather_ = c_stringNew_s(base, from->weather_);
        if(to->weather_ == NULL) {
            result = V_COPYIN_RESULT_OUT_OF_MEMORY;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'ssafy_msgs::msg::dds_::EnviromentStatus_.weather_' of type 'c_string' is NULL.");
        result = V_COPYIN_RESULT_INVALID;
    }
#else
    to->weather_ = c_stringNew_s(base, from->weather_);
    if(to->weather_ == NULL) {
        result = V_COPYIN_RESULT_OUT_OF_MEMORY;
    }
#endif
    return result;
}

void
__ssafy_msgs_msg_dds__EnviromentStatus___copyOut(
    const void *_from,
    void *_to)
{
    const struct _ssafy_msgs_msg_dds__EnviromentStatus_ *from = (const struct _ssafy_msgs_msg_dds__EnviromentStatus_ *)_from;
    struct ::ssafy_msgs::msg::dds_::EnviromentStatus_ *to = (struct ::ssafy_msgs::msg::dds_::EnviromentStatus_ *)_to;
    to->month_ = (::DDS::Octet)from->month_;
    to->day_ = (::DDS::Octet)from->day_;
    to->hour_ = (::DDS::Octet)from->hour_;
    to->minute_ = (::DDS::Octet)from->minute_;
    to->temperature_ = (::DDS::Octet)from->temperature_;
    to->weather_ = DDS::string_dup(from->weather_ ? from->weather_ : "");
}

