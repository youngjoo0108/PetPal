

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from CustomObjectInfo_.idl using "rtiddsgen".
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

#include "CustomObjectInfo_.h"

#include <new>

namespace ssafy_msgs {
    namespace msg {
        namespace dds_ {

            /* ========================================================================= */
            const char *CustomObjectInfo_TYPENAME = "ssafy_msgs::msg::dds_::CustomObjectInfo_";

            DDS_TypeCode* CustomObjectInfo__get_typecode()
            {
                static RTIBool is_initialized = RTI_FALSE;

                static DDS_TypeCode CustomObjectInfo__g_tc_position__sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE(RTI_INT32_MAX,NULL);
                static DDS_TypeCode_Member CustomObjectInfo__g_tc_members[1]=
                {

                    {
                        (char *)"position_",/* Member name */
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
                    }
                };

                static DDS_TypeCode CustomObjectInfo__g_tc =
                {{
                        DDS_TK_STRUCT,/* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"ssafy_msgs::msg::dds_::CustomObjectInfo_", /* Name */
                        NULL, /* Ignored */      
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        1, /* Number of members */
                        CustomObjectInfo__g_tc_members, /* Members */
                        DDS_VM_NONE  /* Ignored */         
                    }}; /* Type code for CustomObjectInfo_*/

                if (is_initialized) {
                    return &CustomObjectInfo__g_tc;
                }

                CustomObjectInfo__g_tc_position__sequence._data._typeCode = (RTICdrTypeCode *)geometry_msgs::msg::dds_::Vector3__get_typecode();

                CustomObjectInfo__g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)& CustomObjectInfo__g_tc_position__sequence;

                is_initialized = RTI_TRUE;

                return &CustomObjectInfo__g_tc;
            }

            RTIBool CustomObjectInfo__initialize(
                CustomObjectInfo_* sample) {
                return ssafy_msgs::msg::dds_::CustomObjectInfo__initialize_ex(sample,RTI_TRUE,RTI_TRUE);
            }

            RTIBool CustomObjectInfo__initialize_ex(
                CustomObjectInfo_* sample,RTIBool allocatePointers, RTIBool allocateMemory)
            {

                struct DDS_TypeAllocationParams_t allocParams =
                DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

                allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
                allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

                return ssafy_msgs::msg::dds_::CustomObjectInfo__initialize_w_params(
                    sample,&allocParams);

            }

            RTIBool CustomObjectInfo__initialize_w_params(
                CustomObjectInfo_* sample, const struct DDS_TypeAllocationParams_t * allocParams)
            {

                void* buffer = NULL;
                if (buffer) {} /* To avoid warnings */

                if (sample == NULL) {
                    return RTI_FALSE;
                }
                if (allocParams == NULL) {
                    return RTI_FALSE;
                }

                if (allocParams->allocate_memory) {
                    geometry_msgs::msg::dds_::Vector3_Seq_initialize(&sample->position_ );
                    geometry_msgs::msg::dds_::Vector3_Seq_set_element_allocation_params(&sample->position_ ,allocParams);
                    geometry_msgs::msg::dds_::Vector3_Seq_set_absolute_maximum(&sample->position_ , RTI_INT32_MAX);
                    if (!geometry_msgs::msg::dds_::Vector3_Seq_set_maximum(&sample->position_, (0))) {
                        return RTI_FALSE;
                    }
                } else { 
                    geometry_msgs::msg::dds_::Vector3_Seq_set_length(&sample->position_, 0);
                }
                return RTI_TRUE;
            }

            void CustomObjectInfo__finalize(
                CustomObjectInfo_* sample)
            {

                ssafy_msgs::msg::dds_::CustomObjectInfo__finalize_ex(sample,RTI_TRUE);
            }

            void CustomObjectInfo__finalize_ex(
                CustomObjectInfo_* sample,RTIBool deletePointers)
            {
                struct DDS_TypeDeallocationParams_t deallocParams =
                DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

                if (sample==NULL) {
                    return;
                } 

                deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

                ssafy_msgs::msg::dds_::CustomObjectInfo__finalize_w_params(
                    sample,&deallocParams);
            }

            void CustomObjectInfo__finalize_w_params(
                CustomObjectInfo_* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
            {

                if (sample==NULL) {
                    return;
                }

                if (deallocParams == NULL) {
                    return;
                }

                geometry_msgs::msg::dds_::Vector3_Seq_set_element_deallocation_params(
                    &sample->position_,deallocParams);
                geometry_msgs::msg::dds_::Vector3_Seq_finalize(&sample->position_);

            }

            void CustomObjectInfo__finalize_optional_members(
                CustomObjectInfo_* sample, RTIBool deletePointers)
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

                {
                    DDS_UnsignedLong i, length;
                    length = geometry_msgs::msg::dds_::Vector3_Seq_get_length(
                        &sample->position_);

                    for (i = 0; i < length; i++) {
                        geometry_msgs::msg::dds_::Vector3__finalize_optional_members(
                            geometry_msgs::msg::dds_::Vector3_Seq_get_reference(
                                &sample->position_, i), deallocParams->delete_pointers);
                    }
                }  

            }

            RTIBool CustomObjectInfo__copy(
                CustomObjectInfo_* dst,
                const CustomObjectInfo_* src)
            {
                try {

                    if (dst == NULL || src == NULL) {
                        return RTI_FALSE;
                    }

                    if (!geometry_msgs::msg::dds_::Vector3_Seq_copy(&dst->position_ ,
                    &src->position_ )) {
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
            * Configure and implement 'CustomObjectInfo_' sequence class.
            */
            #define T CustomObjectInfo_
            #define TSeq CustomObjectInfo_Seq

            #define T_initialize_w_params ssafy_msgs::msg::dds_::CustomObjectInfo__initialize_w_params

            #define T_finalize_w_params   ssafy_msgs::msg::dds_::CustomObjectInfo__finalize_w_params
            #define T_copy       ssafy_msgs::msg::dds_::CustomObjectInfo__copy

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

