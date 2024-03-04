

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from TurtlebotStatus_.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#ifndef dds_c_log_impl_h              
#include "dds_c/dds_c_log_impl.h"                                
#endif        

#ifndef cdr_type_h
#include "cdr/cdr_type.h"
#endif    

#ifndef osapi_heap_h
#include "osapi/osapi_heap.h" 
#endif
#else
#include "ndds_standalone_type.h"
#endif

#include "TurtlebotStatus_.h"

#include <new>

namespace ssafy_msgs {
    namespace msg {
        namespace dds_ {

            /* ========================================================================= */
            const char *TurtlebotStatus_TYPENAME = "ssafy_msgs::msg::dds_::TurtlebotStatus_";

            DDS_TypeCode* TurtlebotStatus__get_typecode()
            {
                static RTIBool is_initialized = RTI_FALSE;

                static DDS_TypeCode_Member TurtlebotStatus__g_tc_members[6]=
                {

                    {
                        (char *)"twist_",/* Member name */
                        {
                            0,/* Representation ID */          
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL/* Ignored */
                    }, 
                    {
                        (char *)"power_supply_status_",/* Member name */
                        {
                            1,/* Representation ID */          
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL/* Ignored */
                    }, 
                    {
                        (char *)"battery_percentage_",/* Member name */
                        {
                            2,/* Representation ID */          
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL/* Ignored */
                    }, 
                    {
                        (char *)"can_use_hand_",/* Member name */
                        {
                            3,/* Representation ID */          
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL/* Ignored */
                    }, 
                    {
                        (char *)"can_put_",/* Member name */
                        {
                            4,/* Representation ID */          
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL/* Ignored */
                    }, 
                    {
                        (char *)"can_lift_",/* Member name */
                        {
                            5,/* Representation ID */          
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL/* Ignored */
                    }
                };

                static DDS_TypeCode TurtlebotStatus__g_tc =
                {{
                        DDS_TK_STRUCT,/* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"ssafy_msgs::msg::dds_::TurtlebotStatus_", /* Name */
                        NULL, /* Ignored */      
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        6, /* Number of members */
                        TurtlebotStatus__g_tc_members, /* Members */
                        DDS_VM_NONE  /* Ignored */         
                    }}; /* Type code for TurtlebotStatus_*/

                if (is_initialized) {
                    return &TurtlebotStatus__g_tc;
                }

                TurtlebotStatus__g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)geometry_msgs::msg::dds_::Twist__get_typecode();

                TurtlebotStatus__g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_octet;

                TurtlebotStatus__g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;

                TurtlebotStatus__g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_boolean;

                TurtlebotStatus__g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_boolean;

                TurtlebotStatus__g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_boolean;

                is_initialized = RTI_TRUE;

                return &TurtlebotStatus__g_tc;
            }

            RTIBool TurtlebotStatus__initialize(
                TurtlebotStatus_* sample) {
                return ssafy_msgs::msg::dds_::TurtlebotStatus__initialize_ex(sample,RTI_TRUE,RTI_TRUE);
            }

            RTIBool TurtlebotStatus__initialize_ex(
                TurtlebotStatus_* sample,RTIBool allocatePointers, RTIBool allocateMemory)
            {

                struct DDS_TypeAllocationParams_t allocParams =
                DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

                allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
                allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

                return ssafy_msgs::msg::dds_::TurtlebotStatus__initialize_w_params(
                    sample,&allocParams);

            }

            RTIBool TurtlebotStatus__initialize_w_params(
                TurtlebotStatus_* sample, const struct DDS_TypeAllocationParams_t * allocParams)
            {

                if (sample == NULL) {
                    return RTI_FALSE;
                }
                if (allocParams == NULL) {
                    return RTI_FALSE;
                }

                if (!geometry_msgs::msg::dds_::Twist__initialize_w_params(&sample->twist_,
                allocParams)) {
                    return RTI_FALSE;
                }

                if (!RTICdrType_initOctet(&sample->power_supply_status_)) {
                    return RTI_FALSE;
                }

                if (!RTICdrType_initFloat(&sample->battery_percentage_)) {
                    return RTI_FALSE;
                }

                if (!RTICdrType_initBoolean(&sample->can_use_hand_)) {
                    return RTI_FALSE;
                }

                if (!RTICdrType_initBoolean(&sample->can_put_)) {
                    return RTI_FALSE;
                }

                if (!RTICdrType_initBoolean(&sample->can_lift_)) {
                    return RTI_FALSE;
                }

                return RTI_TRUE;
            }

            void TurtlebotStatus__finalize(
                TurtlebotStatus_* sample)
            {

                ssafy_msgs::msg::dds_::TurtlebotStatus__finalize_ex(sample,RTI_TRUE);
            }

            void TurtlebotStatus__finalize_ex(
                TurtlebotStatus_* sample,RTIBool deletePointers)
            {
                struct DDS_TypeDeallocationParams_t deallocParams =
                DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

                if (sample==NULL) {
                    return;
                } 

                deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

                ssafy_msgs::msg::dds_::TurtlebotStatus__finalize_w_params(
                    sample,&deallocParams);
            }

            void TurtlebotStatus__finalize_w_params(
                TurtlebotStatus_* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
            {

                if (sample==NULL) {
                    return;
                }

                if (deallocParams == NULL) {
                    return;
                }

                geometry_msgs::msg::dds_::Twist__finalize_w_params(&sample->twist_,deallocParams);

            }

            void TurtlebotStatus__finalize_optional_members(
                TurtlebotStatus_* sample, RTIBool deletePointers)
            {
                struct DDS_TypeDeallocationParams_t deallocParamsTmp =
                DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
                struct DDS_TypeDeallocationParams_t * deallocParams =
                &deallocParamsTmp;

                if (sample==NULL) {
                    return;
                } 
                if (deallocParams) {} /* To avoid warnings */

                deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
                deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

                geometry_msgs::msg::dds_::Twist__finalize_optional_members(&sample->twist_, deallocParams->delete_pointers);
            }

            RTIBool TurtlebotStatus__copy(
                TurtlebotStatus_* dst,
                const TurtlebotStatus_* src)
            {
                try {

                    if (dst == NULL || src == NULL) {
                        return RTI_FALSE;
                    }

                    if (!geometry_msgs::msg::dds_::Twist__copy(
                        &dst->twist_,(const geometry_msgs::msg::dds_::Twist_*)&src->twist_)) {
                        return RTI_FALSE;
                    } 
                    if (!RTICdrType_copyOctet (
                        &dst->power_supply_status_, &src->power_supply_status_)) { 
                        return RTI_FALSE;
                    }
                    if (!RTICdrType_copyFloat (
                        &dst->battery_percentage_, &src->battery_percentage_)) { 
                        return RTI_FALSE;
                    }
                    if (!RTICdrType_copyBoolean (
                        &dst->can_use_hand_, &src->can_use_hand_)) { 
                        return RTI_FALSE;
                    }
                    if (!RTICdrType_copyBoolean (
                        &dst->can_put_, &src->can_put_)) { 
                        return RTI_FALSE;
                    }
                    if (!RTICdrType_copyBoolean (
                        &dst->can_lift_, &src->can_lift_)) { 
                        return RTI_FALSE;
                    }

                    return RTI_TRUE;

                } catch (std::bad_alloc&) {
                    return RTI_FALSE;
                }
            }

            /**
            * <<IMPLEMENTATION>>
            *
            * Defines:  TSeq, T
            *
            * Configure and implement 'TurtlebotStatus_' sequence class.
            */
            #define T TurtlebotStatus_
            #define TSeq TurtlebotStatus_Seq

            #define T_initialize_w_params ssafy_msgs::msg::dds_::TurtlebotStatus__initialize_w_params

            #define T_finalize_w_params   ssafy_msgs::msg::dds_::TurtlebotStatus__finalize_w_params
            #define T_copy       ssafy_msgs::msg::dds_::TurtlebotStatus__copy

            #ifndef NDDS_STANDALONE_TYPE
            #include "dds_c/generic/dds_c_sequence_TSeq.gen"
            #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
            #else
            #include "dds_c_sequence_TSeq.gen"
            #include "dds_cpp_sequence_TSeq.gen"
            #endif

            #undef T_copy
            #undef T_finalize_w_params

            #undef T_initialize_w_params

            #undef TSeq
            #undef T
        } /* namespace dds_  */
    } /* namespace msg  */
} /* namespace ssafy_msgs  */

