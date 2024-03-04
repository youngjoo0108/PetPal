

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ObjectInfo_.idl using "rtiddsgen".
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

#include "ObjectInfo_.h"

#include <new>

namespace ssafy_msgs {
    namespace msg {
        namespace dds_ {

            /* ========================================================================= */
            const char *ObjectInfo_TYPENAME = "ssafy_msgs::msg::dds_::ObjectInfo_";

            DDS_TypeCode* ObjectInfo__get_typecode()
            {
                static RTIBool is_initialized = RTI_FALSE;

                static DDS_TypeCode ObjectInfo__g_tc_idx_obj__sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE(RTI_INT32_MAX,NULL);
                static DDS_TypeCode ObjectInfo__g_tc_x__sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE(RTI_INT32_MAX,NULL);
                static DDS_TypeCode ObjectInfo__g_tc_y__sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE(RTI_INT32_MAX,NULL);
                static DDS_TypeCode_Member ObjectInfo__g_tc_members[4]=
                {

                    {
                        (char *)"num_obj_",/* Member name */
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
                        (char *)"idx_obj_",/* Member name */
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
                        (char *)"x_",/* Member name */
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
                        (char *)"y_",/* Member name */
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
                    }
                };

                static DDS_TypeCode ObjectInfo__g_tc =
                {{
                        DDS_TK_STRUCT,/* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"ssafy_msgs::msg::dds_::ObjectInfo_", /* Name */
                        NULL, /* Ignored */      
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        4, /* Number of members */
                        ObjectInfo__g_tc_members, /* Members */
                        DDS_VM_NONE  /* Ignored */         
                    }}; /* Type code for ObjectInfo_*/

                if (is_initialized) {
                    return &ObjectInfo__g_tc;
                }

                ObjectInfo__g_tc_idx_obj__sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short;

                ObjectInfo__g_tc_x__sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;

                ObjectInfo__g_tc_y__sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_float;

                ObjectInfo__g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_short;

                ObjectInfo__g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)& ObjectInfo__g_tc_idx_obj__sequence;
                ObjectInfo__g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)& ObjectInfo__g_tc_x__sequence;
                ObjectInfo__g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)& ObjectInfo__g_tc_y__sequence;

                is_initialized = RTI_TRUE;

                return &ObjectInfo__g_tc;
            }

            RTIBool ObjectInfo__initialize(
                ObjectInfo_* sample) {
                return ssafy_msgs::msg::dds_::ObjectInfo__initialize_ex(sample,RTI_TRUE,RTI_TRUE);
            }

            RTIBool ObjectInfo__initialize_ex(
                ObjectInfo_* sample,RTIBool allocatePointers, RTIBool allocateMemory)
            {

                struct DDS_TypeAllocationParams_t allocParams =
                DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

                allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
                allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

                return ssafy_msgs::msg::dds_::ObjectInfo__initialize_w_params(
                    sample,&allocParams);

            }

            RTIBool ObjectInfo__initialize_w_params(
                ObjectInfo_* sample, const struct DDS_TypeAllocationParams_t * allocParams)
            {

                void* buffer = NULL;
                if (buffer) {} /* To avoid warnings */

                if (sample == NULL) {
                    return RTI_FALSE;
                }
                if (allocParams == NULL) {
                    return RTI_FALSE;
                }

                if (!RTICdrType_initShort(&sample->num_obj_)) {
                    return RTI_FALSE;
                }

                if (allocParams->allocate_memory) {
                    DDS_ShortSeq_initialize(&sample->idx_obj_  );
                    DDS_ShortSeq_set_absolute_maximum(&sample->idx_obj_ , RTI_INT32_MAX);
                    if (!DDS_ShortSeq_set_maximum(&sample->idx_obj_ , (0))) {
                        return RTI_FALSE;
                    }
                } else { 
                    DDS_ShortSeq_set_length(&sample->idx_obj_, 0);
                }
                if (allocParams->allocate_memory) {
                    DDS_FloatSeq_initialize(&sample->x_  );
                    DDS_FloatSeq_set_absolute_maximum(&sample->x_ , RTI_INT32_MAX);
                    if (!DDS_FloatSeq_set_maximum(&sample->x_ , (0))) {
                        return RTI_FALSE;
                    }
                } else { 
                    DDS_FloatSeq_set_length(&sample->x_, 0);
                }
                if (allocParams->allocate_memory) {
                    DDS_FloatSeq_initialize(&sample->y_  );
                    DDS_FloatSeq_set_absolute_maximum(&sample->y_ , RTI_INT32_MAX);
                    if (!DDS_FloatSeq_set_maximum(&sample->y_ , (0))) {
                        return RTI_FALSE;
                    }
                } else { 
                    DDS_FloatSeq_set_length(&sample->y_, 0);
                }
                return RTI_TRUE;
            }

            void ObjectInfo__finalize(
                ObjectInfo_* sample)
            {

                ssafy_msgs::msg::dds_::ObjectInfo__finalize_ex(sample,RTI_TRUE);
            }

            void ObjectInfo__finalize_ex(
                ObjectInfo_* sample,RTIBool deletePointers)
            {
                struct DDS_TypeDeallocationParams_t deallocParams =
                DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

                if (sample==NULL) {
                    return;
                } 

                deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

                ssafy_msgs::msg::dds_::ObjectInfo__finalize_w_params(
                    sample,&deallocParams);
            }

            void ObjectInfo__finalize_w_params(
                ObjectInfo_* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
            {

                if (sample==NULL) {
                    return;
                }

                if (deallocParams == NULL) {
                    return;
                }

                DDS_ShortSeq_finalize(&sample->idx_obj_);

                DDS_FloatSeq_finalize(&sample->x_);

                DDS_FloatSeq_finalize(&sample->y_);

            }

            void ObjectInfo__finalize_optional_members(
                ObjectInfo_* sample, RTIBool deletePointers)
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

            }

            RTIBool ObjectInfo__copy(
                ObjectInfo_* dst,
                const ObjectInfo_* src)
            {
                try {

                    if (dst == NULL || src == NULL) {
                        return RTI_FALSE;
                    }

                    if (!RTICdrType_copyShort (
                        &dst->num_obj_, &src->num_obj_)) { 
                        return RTI_FALSE;
                    }
                    if (!DDS_ShortSeq_copy(&dst->idx_obj_ ,
                    &src->idx_obj_ )) {
                        return RTI_FALSE;
                    }
                    if (!DDS_FloatSeq_copy(&dst->x_ ,
                    &src->x_ )) {
                        return RTI_FALSE;
                    }
                    if (!DDS_FloatSeq_copy(&dst->y_ ,
                    &src->y_ )) {
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
            * Configure and implement 'ObjectInfo_' sequence class.
            */
            #define T ObjectInfo_
            #define TSeq ObjectInfo_Seq

            #define T_initialize_w_params ssafy_msgs::msg::dds_::ObjectInfo__initialize_w_params

            #define T_finalize_w_params   ssafy_msgs::msg::dds_::ObjectInfo__finalize_w_params
            #define T_copy       ssafy_msgs::msg::dds_::ObjectInfo__copy

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

